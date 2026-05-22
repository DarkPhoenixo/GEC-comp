import socket

def run_server():
    s = socket.socket()
    s.bind(("0.0.0.0", 5000))
    s.listen(1)
    print("Server waiting...")

    conn, addr = s.accept()
    print("Client connected:", addr)

    while True:
        msg = conn.recv(1024).decode()
        if not msg:
            break
        print("Client:", msg)

        reply = input("Server: ")
        conn.send(reply.encode())

    conn.close()
    s.close()

run_server()