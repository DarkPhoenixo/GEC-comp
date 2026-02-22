import socket
import tkinter as tk
import threading
import time
import random

client = socket.socket()
client.connect(("localhost", 5000))

root = tk.Tk()
root.title("Stop & Wait ARQ Timeline")

CANVAS_W = 800
CANVAS_H = 700
SENDER_X = 150
RECV_X = 650
START_Y = 80
STEP = 100 

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
    canvas.create_line(SENDER_X, y, RECV_X, y + 60,
                       fill=color, width=2, arrow=tk.LAST)
    canvas.create_rectangle(RECV_X - 15, y + 50, RECV_X + 15, y + 70,
                             fill=color, outline=color)
    text = f"{frame_data} (LOST)" if lost else str(frame_data)
    canvas.create_text(RECV_X, y + 60, text=text, fill="white",
                       font=("Arial", 9, "bold"))
    canvas.update()

def draw_timer(y):
    global timer_rect
    if timer_rect:
        canvas.delete(timer_rect)
    timer_rect = canvas.create_rectangle(SENDER_X - 20, y,
                                         SENDER_X - 8, y + 60,
                                         fill="yellow", outline="black")
    canvas.create_text(SENDER_X - 35, y + 30, text="TIMER",
                       font=("Arial", 7), angle=90)
    canvas.update()

def clear_timer():
    global timer_rect
    if timer_rect:
        canvas.delete(timer_rect)
        timer_rect = None

def draw_ack(y, s, lost=False):
    color = "green" if not lost else "purple"
    canvas.create_line(RECV_X, y + 60, SENDER_X, y + 100,
                       fill=color, width=2, arrow=tk.LAST)
    text = f"ACK{s} (LOST)" if lost else f"ACK{s}"
    canvas.create_text(SENDER_X + 30, y + 100,
                       text=text, fill=color,
                       font=("Arial", 9, "bold"))
    canvas.update()

def sender():
    global seq, y_pos

    for f in frames:
        while True:
            current_y = y_pos
            frame_lost = random.random() < 0.2  # 20% chance of loss
            ack_lost = random.random() < 0.2    # 20% chance of ACK loss

            root.after(0, lambda cy=current_y, fd=f, fl=frame_lost: draw_frame(cy, fd, fl))
            root.after(0, lambda cy=current_y: draw_timer(cy))
            time.sleep(0.5)

            if not frame_lost:
                client.send(f"{seq}:{f}".encode())
            else:
                print(f"Frame {seq} lost during transmission")
                continue

            client.settimeout(3)

            try:
                ack = client.recv(1024).decode()

                if not ack_lost:
                    root.after(0, lambda cy=current_y, s=seq: draw_ack(cy, s))
                else:
                    root.after(0, lambda cy=current_y, s=seq: draw_ack(cy, s, True))
                    print(f"ACK {seq} lost during transmission")
                    raise socket.timeout

                root.after(0, clear_timer)
                time.sleep(0.5)

                if ack == f"ACK{seq}" and not ack_lost:
                    seq = 1 - seq
                    y_pos += STEP + 40
                    break

            except socket.timeout:
                print(f"Timeout, resending frame {seq}...")
                root.after(0, clear_timer)
                time.sleep(0.3)

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