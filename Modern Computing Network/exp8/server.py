import socket
import random

server = socket.socket()
server.bind(("localhost", 5000))
server.listen(1)

print("Server waiting...")
conn, addr = server.accept()

WINDOW_SIZE = 4
received_frames = set()  
next_expected = 0 

while True:
    data = conn.recv(1024).decode()
    if not data:
        break

    seq, msg = data.split(":")
    seq = int(seq)

    print(f"Received Frame {seq}")

    
    if random.random() < 0.15:  # 15% chance
        print(f"ACK LOST (simulated) for frame {seq}")
        continue

    
    conn.send(f"ACK{seq}".encode())
    print(f"Sent ACK{seq}")
    
    
    received_frames.add(seq)
    
  
    while next_expected in received_frames:
        print(f"Delivering frame {next_expected} to upper layer")
        next_expected += 1

conn.close()