import socket
import tkinter as tk
import threading
import time
import random

client = socket.socket()
client.connect(("localhost", 5000))

root = tk.Tk()
root.title("Selective Repeat ARQ Timeline")

CANVAS_W = 800
CANVAS_H = 1200
SENDER_X = 150
RECV_X = 650
START_Y = 80
STEP = 60
WINDOW_SIZE = 4

canvas = tk.Canvas(root, width=CANVAS_W, height=CANVAS_H, bg="white")
canvas.pack()

# vertical lines
canvas.create_line(SENDER_X, START_Y, SENDER_X, CANVAS_H - 50, width=3)
canvas.create_line(RECV_X, START_Y, RECV_X, CANVAS_H - 50, width=3)

# arrows on vertical lines
canvas.create_line(SENDER_X, CANVAS_H - 50, SENDER_X, CANVAS_H - 30,
                   width=3, arrow=tk.LAST)

canvas.create_text(SENDER_X, START_Y - 20, text="Sender", font=("Arial", 12, "bold"))
canvas.create_text(RECV_X, START_Y - 20, text="Receiver", font=("Arial", 12, "bold"))

y_pos = START_Y
seq = 0
timer_rect = None
frames = []

def draw_frame(y, frame_data, lost=False):
    color = "red" if not lost else "gray"
    canvas.create_line(SENDER_X, y, RECV_X, y + 25,
                       fill=color, width=2, arrow=tk.LAST)
    canvas.create_rectangle(RECV_X - 12, y + 18, RECV_X + 12, y + 35,
                             fill=color, outline=color)
    text = f"{frame_data} (LOST)" if lost else str(frame_data)
    canvas.create_text(RECV_X, y + 26, text=text, fill="white",
                       font=("Arial", 7, "bold"))
    canvas.update()

def draw_timer(y):
    global timer_rect
    if timer_rect:
        canvas.delete(timer_rect)
    timer_rect = canvas.create_rectangle(SENDER_X - 18, y,
                                         SENDER_X - 8, y + 25,
                                         fill="yellow", outline="black")
    canvas.create_text(SENDER_X - 30, y + 12, text="TMR",
                       font=("Arial", 6), angle=90)
    canvas.update()

def clear_timer():
    global timer_rect
    if timer_rect:
        canvas.delete(timer_rect)
        timer_rect = None

def draw_ack(y, s):
    color = "green"
    canvas.create_line(RECV_X, y + 25, SENDER_X, y + 40,
                       fill=color, width=2, arrow=tk.LAST)
    canvas.create_text(SENDER_X + 25, y + 40,
                       text=f"ACK{s}", fill=color,
                       font=("Arial", 7, "bold"))
    canvas.update()

def sender():
    global seq, y_pos

    base = 0
    next_seq = 0
    ack_received = set()  # Track individually acknowledged frames
    sent_frames = {}
    pending_acks = []
    frame_timers = {}  # Individual timers for each frame
    lock = threading.Lock()
    
    def check_acks():
        """Background thread to continuously check for ACKs"""
        client.settimeout(0.1)
        
        while base < len(frames):
            try:
                ack = client.recv(1024).decode().strip()
                if ack.startswith("ACK"):
                    ack_num = int(ack[3:])
                    with lock:
                        pending_acks.append(ack_num)
                    print(f"Received ACK{ack_num}")
            except socket.timeout:
                pass
            except:
                break
            time.sleep(0.05)
    
    def check_timeouts():
        """Background thread to check for individual frame timeouts"""
        nonlocal next_seq
        while base < len(frames):
            time.sleep(0.2)
            current_time = time.time()
            
            with lock:
                for frame_num in range(base, min(base + WINDOW_SIZE, len(frames))):
                    if frame_num in frame_timers and frame_num not in ack_received:
                        if current_time - frame_timers[frame_num] > 2.0:  # 2 second timeout
                            print(f"Timeout for frame {frame_num}! Retransmitting...")
                            # Mark for retransmission
                            if frame_num in sent_frames:
                                del sent_frames[frame_num]
                            if frame_num in frame_timers:
                                del frame_timers[frame_num]
    
    # Start background threads
    ack_thread = threading.Thread(target=check_acks, daemon=True)
    timeout_thread = threading.Thread(target=check_timeouts, daemon=True)
    ack_thread.start()
    timeout_thread.start()
    
    while base < len(frames):
        # Send frames within window that haven't been sent or need retransmission
        for frame_num in range(base, min(base + WINDOW_SIZE, len(frames))):
            if frame_num not in sent_frames and frame_num not in ack_received:
                current_y = y_pos
                
                frame_lost = random.random() < 0.15
                sent_frames[frame_num] = not frame_lost

                root.after(0, lambda cy=current_y, fn=frame_num, fd=frames[frame_num], fl=frame_lost: 
                          draw_frame(cy, f"{fn}:{fd}", fl))
                root.after(0, lambda cy=current_y: draw_timer(cy))
                time.sleep(0.3)

                y_pos += STEP

                if not frame_lost:
                    with lock:
                        client.send(f"{frame_num}:{frames[frame_num]}".encode())
                        frame_timers[frame_num] = time.time()  # Start individual timer
                    print(f"Sent frame {frame_num}")
                else:
                    print(f"Frame {frame_num} lost during transmission")
                    with lock:
                        del sent_frames[frame_num]  # Mark for retransmission
                
                time.sleep(0.1)

        # Process any pending ACKs
        while pending_acks:
            with lock:
                ack_num = pending_acks.pop(0)
            
            ack_lost = random.random() < 0.15
            
            if not ack_lost:
                current_y = y_pos
                root.after(0, lambda cy=current_y, s=ack_num: draw_ack(cy, s))
                y_pos += STEP
                
                with lock:
                    ack_received.add(ack_num)
                    
                    # Slide window if base is acknowledged
                    while base in ack_received and base < len(frames):
                        base += 1
                
                root.after(0, clear_timer)
                time.sleep(0.3)
                print(f"Processed ACK{ack_num}, base now {base}")
            else:
                print(f"ACK {ack_num} lost (simulated)")
        
        time.sleep(0.2)

def input_frames():
    input_window = tk.Toplevel(root)
    input_window.title("Frame Input")
    
    tk.Label(input_window, text="Number of frames:").pack()
    num_entry = tk.Entry(input_window)
    num_entry.pack()
    
    tk.Label(input_window, text="Enter frames (one per line):").pack()
    text_widget = tk.Text(input_window, height=10, width=30)
    text_widget.pack()
    
    def submit():
        global frames
        try:
            num_frames = int(num_entry.get())
            frame_list = text_widget.get("1.0", tk.END).strip().split('\n')
            frames = frame_list[:num_frames]
            input_window.destroy()
            threading.Thread(target=sender, daemon=True).start()
        except ValueError:
            import tkinter.messagebox
            tkinter.messagebox.showerror("Error", "Invalid input")
    
    tk.Button(input_window, text="Start", command=submit).pack()

input_frames()
root.mainloop()