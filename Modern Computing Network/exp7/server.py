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
        # simulate ACK loss (only for the correct/expected frame)
        if random.random() < 0.15:  # Reduced to 15%
            print("ACK LOST (simulated) for", seq)
            # IMPORTANT: do not advance expected_seq
            continue

        conn.send(f"ACK{seq}".encode())
        print(f"Sent ACK{seq}")
        expected_seq += 1
    else:
        # Out-of-order frame: re-send last ACK
        last_acked = expected_seq - 1
        if last_acked >= 0:
            print(f"Out-of-order frame {seq}. Resending ACK{last_acked}")
            conn.send(f"ACK{last_acked}".encode())

conn.close()