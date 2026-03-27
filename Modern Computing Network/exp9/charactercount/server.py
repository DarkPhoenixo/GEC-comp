import socket
import random
import threading
import time

def recv_frame_ccf(sock):
    """Receive frame using character count framing"""
    count_str = ''
    while True:
        char = sock.recv(1).decode('utf-8')
        if char == '|':
            break
        if not char:
            return None
        count_str += char
    
    count = int(count_str)
    data = b''
    while len(data) < count:
        chunk = sock.recv(count - len(data))
        if not chunk:
            break
        data += chunk
    
    return data.decode('utf-8')

def send_ack_ccf(sock, ack_num):
    """Send ACK using character count framing"""
    ack_msg = f"ACK{ack_num}"
    count = len(ack_msg)
    frame = f"{count}|{ack_msg}"
    sock.sendall(frame.encode('utf-8'))

def handle_client(conn, addr):
    """Handle Go-Back-N receiver with character count framing"""
    print(f"[SERVER] Client connected from {addr}")
    
    expected_seq = 0
    
    while True:
        try:
            frame_data = recv_frame_ccf(conn)
            
            if not frame_data:
                break
            
            # Parse frame: Seq{seq}:{msg}
            parts = frame_data.split(":")
            seq_part = parts[0]  # Seq0, Seq1, etc.
            seq = int(seq_part[3:])  # Extract number from SeqX
            msg = ":".join(parts[1:])  # Rejoin in case msg has colons
            
            print(f"[SERVER] Received frame {seq}: {msg} (Expected: {expected_seq})")
            
            # Simulate ACK loss
            ack_lost = random.random() < 0.15
            
            if seq == expected_seq:
                if ack_lost:
                    print(f"[SERVER] ACK{seq} LOST (simulated)")
                else:
                    send_ack_ccf(conn, seq)
                    print(f"[SERVER] Sent ACK{seq}")
                    expected_seq += 1
            else:
                # Out of order frame
                last_acked = expected_seq - 1
                if last_acked >= 0:
                    print(f"[SERVER] Out-of-order frame {seq}. Resending ACK{last_acked}")
                    send_ack_ccf(conn, last_acked)
                else:
                    print(f"[SERVER] Out-of-order frame {seq}. No ACK sent yet")
        
        except Exception as e:
            print(f"[SERVER] Error: {e}")
            break
    
    conn.close()
    print(f"[SERVER] Connection closed\n")

def main():
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_sock.bind(("localhost", 5000))
    server_sock.listen(1)
    
    print("="*50)
    print("GO-BACK-N ARQ SERVER (CHARACTER COUNT FRAMING)")
    print("="*50)
    print("[SERVER] Listening on localhost:5000")
    print("[SERVER] Waiting for client connection...\n")
    
    try:
        while True:
            conn, addr = server_sock.accept()
            handle_client(conn, addr)
    except KeyboardInterrupt:
        print("\n[SERVER] Shutting down...")
    finally:
        server_sock.close()

if __name__ == "__main__":
    main()