import socket

def run_client():
    s = socket.socket()
    s.connect(("127.0.0.1", 5000))
    print("Connected to server")

    while True:
        msg = input("Client: ")
        if msg.lower() == "exit":
            break
        s.send(msg.encode())

        reply = s.recv(1024).decode()
        print("Server:", reply)

    s.close()

run_client()