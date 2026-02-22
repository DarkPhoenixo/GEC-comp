import socket
import random

server = socket.socket()
server.bind(("localhost", 5000))
server.listen(1)

print("Server waiting...")
conn, addr = server.accept()

expected_seq = 0

while True:

    data = conn.recv(1024).decode()
    if not data:
        break

    seq, msg = data.split(":")
    seq = int(seq)

    print("Received Frame", seq)

    if seq == expected_seq:
        # simulate ACK loss
        if random.random() < 0.2:  # 20% chance of ACK loss
            print("ACK LOST!")
            continue
        
        conn.send(f"ACK{seq}".encode())
        expected_seq = 1 - expected_seq

conn.close()
