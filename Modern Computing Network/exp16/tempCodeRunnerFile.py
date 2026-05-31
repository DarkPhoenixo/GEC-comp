from socket import *
import os

# Server Port
serverPort = 8080

print("STEP 1 : Creating Web Server")

# Create TCP socket
serverSocket = socket(AF_INET, SOCK_STREAM)
print("TCP Socket Created Successfully")

# Reuse port
serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

# Bind socket
serverSocket.bind(("localhost", serverPort))
print(f"Socket Bound To Port : {serverPort}")

# Listen
serverSocket.listen(1)
print("Server Is Listening...")
print(f"Open Browser And Visit : http://localhost:{serverPort}")

# Get the folder where this Python file is located
base_dir = os.path.dirname(os.path.abspath(__file__))

while True:
    print("\n------------------------------")
    print("STEP 2 : Waiting For Client Request")
    print("------------------------------")

    # Accept client
    connectionSocket, addr = serverSocket.accept()
    print("\nClient Connected Successfully")
    print("Client Address :", addr)

    try:
        print("\nSTEP 3 : Receiving HTTP Request")

        # Receive request
        raw_message = connectionSocket.recv(4096)
        message = raw_message.decode("utf-8", errors="ignore")

        print("\nHTTP REQUEST RECEIVED :\n")
        print(message)

        # Extract filename safely
        request_parts = message.split()
        if len(request_parts) < 2:
            raise Exception("Invalid HTTP request")

        print("\nSTEP 4 : Extracting Requested File")

        filename = request_parts[1]
        filepath = filename[1:]  # remove leading '/'

        if filepath == "":
            filepath = "index.html"

        print("Requested Path :", filename)
        print("Actual File Name :", filepath)

        # Make full path relative to this script
        full_path = os.path.join(base_dir, filepath)

        print("\nSTEP 5 : Opening Requested File")
        print("Opening File :", full_path)

        # Open HTML file
        with open(full_path, "rb") as f:
            outputdata = f.read()

        print("File Opened Successfully")
        print("File Size :", len(outputdata), "bytes")

        print("\nSTEP 6 : Creating HTTP Response")

        # Proper HTTP response
        response = b"HTTP/1.1 200 OK\r\n"
        response += b"Content-Type: text/html; charset=utf-8\r\n"
        response += b"Content-Length: " + str(len(outputdata)).encode() + b"\r\n"
        response += b"Connection: close\r\n"
        response += b"\r\n"

        print("HTTP Header Created Successfully")

        print("\nSTEP 7 : Sending HTTP Header")
        connectionSocket.sendall(response)
        print("HTTP Header Sent")

        print("\nSTEP 8 : Sending HTML File Data")
        connectionSocket.sendall(outputdata)
        print("HTML File Sent Successfully")

    except FileNotFoundError:
        print("\n404 File Not Found")

        error_html = b"""
        <html>
        <head><title>404 Error</title></head>
        <body>
        <h1>404 Not Found</h1>
        </body>
        </html>
        """

        response = b"HTTP/1.1 404 Not Found\r\n"
        response += b"Content-Type: text/html; charset=utf-8\r\n"
        response += b"Content-Length: " + str(len(error_html)).encode() + b"\r\n"
        response += b"Connection: close\r\n"
        response += b"\r\n"

        connectionSocket.sendall(response)
        connectionSocket.sendall(error_html)
        print("404 Error Page Sent Successfully")

    except Exception as e:
        print("ERROR :", e)

    finally:
        print("\nSTEP 9 : Closing Connection")
        connectionSocket.close()
        print("Connection Closed Successfully")