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

    print("Received Frame", seq, "expected", expected_seq)

    if seq == expected_seq:
     
        if random.random() < 0.2:  # 20% chance
            print("ACK LOST (simulated) for", seq)
           
            continue

        conn.send(f"ACK{seq}".encode())
        expected_seq = 1 - expected_seq
    else:
      
        last_acked = 1 - expected_seq
        print(f"Duplicate frame {seq}. Resending ACK{last_acked}")
        conn.send(f"ACK{last_acked}".encode())

conn.close()