import socket
import threading

# Proxy Server Configuration
HOST = '127.0.0.1'
PORT = 8888
BUFFER_SIZE = 4096

# Function to handle each client connection
def handle_client(client_socket):

    try:
        # Receive request from browser/client
        request = client_socket.recv(BUFFER_SIZE)

        if not request:
            client_socket.close()
            return

        print("\n========== REQUEST RECEIVED ==========")
        print(request.decode(errors='ignore'))

        # Decode request
        request_text = request.decode(errors='ignore')

        # Extract first line of HTTP request
        first_line = request_text.split('\n')[0]

        # Example:
        # GET http://example.com/ HTTP/1.1
        parts = first_line.split()

        if len(parts) < 2:
            client_socket.close()
            return

        url = parts[1]


        host = ""

        if "://" in url:
            # Full URL exists
            host = url.split("://")[1].split('/')[0]
        else:
            # Use Host header
            for line in request_text.split('\n'):
                if line.lower().startswith("host:"):
                    host = line.split(":")[1].strip()
                    break

        print(f"\n[CONNECTING TO HOST]: {host}")

        # Remove port number if present
        if ":" in host:
            host = host.split(":")[0]

        # Create socket for original server
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect to original server
        server_socket.connect((host, 80))

        # Replace Proxy-Connection header
        modified_request = request.replace(
            b'Proxy-Connection:',
            b'Connection:'
        )

        # Send request to original server
        server_socket.sendall(modified_request)

        print("[REQUEST FORWARDED TO ORIGINAL SERVER]")

        # Receive response from original server
        while True:

            data = server_socket.recv(BUFFER_SIZE)

            if len(data) > 0:
                client_socket.send(data)
            else:
                break

        print("[RESPONSE SENT TO CLIENT]")

        # Close server socket
        server_socket.close()

    except Exception as e:
        print(f"[ERROR]: {e}")

    finally:
        client_socket.close()

# Main Proxy Server Function
def start_proxy():

    # Create proxy socket
    proxy_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Allow immediate reuse of address
    proxy_socket.setsockopt(
        socket.SOL_SOCKET,
        socket.SO_REUSEADDR,
        1
    )

    # Bind IP and Port
    proxy_socket.bind((HOST, PORT))

    # Start listening
    proxy_socket.listen(10)

    print(f"\n[PROXY SERVER RUNNING ON {HOST}:{PORT}]")

    while True:

        # Accept client connection
        client_socket, client_address = proxy_socket.accept()

        print(f"\n[NEW CONNECTION] {client_address}")

        # Create separate thread for each client
        client_thread = threading.Thread(
            target=handle_client,
            args=(client_socket,)
        )

        client_thread.start()

# Run Proxy Server
start_proxy()

 

