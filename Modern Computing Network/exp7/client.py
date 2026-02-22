import socket
import tkinter as tk
import threading
import time
import random

client = socket.socket()
client.connect(("localhost", 5000))

root = tk.Tk()
root.title("Go-Back-N ARQ Timeline")

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
    ack_received = set()
    sent_frames = {}
    pending_acks = []  # Queue to store ACKs to draw
    
    def check_acks():
        """Background thread to continuously check for ACKs"""
        nonlocal base
        client.settimeout(0.1)
        
        while base < len(frames):
            try:
                ack = client.recv(1024).decode().strip()
                if ack.startswith("ACK"):
                    ack_num = int(ack[3:])
                    pending_acks.append(ack_num)
                    print(f"Received ACK{ack_num}")
            except socket.timeout:
                pass
            except:
                break
            time.sleep(0.05)
    
    # Start ACK receiver thread
    ack_thread = threading.Thread(target=check_acks, daemon=True)
    ack_thread.start()
    
    while base < len(frames):
        # Send frames within window
        while next_seq < len(frames) and next_seq < base + WINDOW_SIZE:
            current_y = y_pos
            
            if next_seq not in sent_frames:
                frame_lost = random.random() < 0.15
                sent_frames[next_seq] = not frame_lost
            else:
                frame_lost = not sent_frames[next_seq]

            root.after(0, lambda cy=current_y, fd=f"{next_seq}:{frames[next_seq]}", fl=frame_lost: draw_frame(cy, fd, fl))
            root.after(0, lambda cy=current_y: draw_timer(cy))
            time.sleep(0.3)

            y_pos += STEP

            if not frame_lost:
                client.send(f"{next_seq}:{frames[next_seq]}".encode())
                print(f"Sent frame {next_seq}")
            else:
                print(f"Frame {next_seq} lost during transmission")
            
            next_seq += 1
            time.sleep(0.1)  # Small delay between sends

        # Process any pending ACKs
        while pending_acks:
            ack_num = pending_acks.pop(0)
            ack_lost = random.random() < 0.15
            
            if not ack_lost:
                current_y = y_pos
                root.after(0, lambda cy=current_y, s=ack_num: draw_ack(cy, s))
                y_pos += STEP
                
                for i in range(base, ack_num + 1):
                    ack_received.add(i)
                
                old_base = base
                while base in ack_received and base < len(frames):
                    base += 1
                
                if base > old_base:
                    root.after(0, clear_timer)
                
                time.sleep(0.3)
                print(f"Processed ACK{ack_num}, base now {base}")
            else:
                print(f"ACK {ack_num} lost (simulated)")
        
        # Check for timeout
        if next_seq >= base + WINDOW_SIZE or next_seq >= len(frames):
            time.sleep(1)  # Wait a bit for ACKs
            
            if base < next_seq and not pending_acks:
                print(f"Timeout! Going back to frame {base}")
                for i in range(base, next_seq):
                    if i in sent_frames:
                        del sent_frames[i]
                next_seq = base
                root.after(0, clear_timer)

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