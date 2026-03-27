import socket
import threading
import time
import random

def send_frame_ccf(sock, message):
    """Send frame using character count framing: count|message"""
    count = len(message)
    frame = f"{count}|{message}"
    sock.sendall(frame.encode('utf-8'))

def recv_ack_ccf(sock):
    """Receive ACK using character count framing"""
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

def sender(sock, frames, window_size=4):
    """Go-Back-N sender with character count framing"""
    base = 0
    next_seq = 0
    ack_received = set()
    sent_frames = {}
    
    def receive_acks():
        sock.settimeout(0.5)
        while base < len(frames):
            try:
                ack = recv_ack_ccf(sock)
                if ack and ack.startswith("ACK"):
                    ack_num = int(ack[3:])
                    print(f"[CLIENT] Received ACK{ack_num}")
                    ack_received.add(ack_num)
            except socket.timeout:
                pass
            except Exception as e:
                print(f"[CLIENT] Error receiving ACK: {e}")
                break
    
    ack_thread = threading.Thread(target=receive_acks, daemon=True)
    ack_thread.start()
    
    while base < len(frames):
        # Send frames within window
        while next_seq < len(frames) and next_seq < base + window_size:
            # Simulate frame loss
            frame_lost = random.random() < 0.15
            
            frame_data = f"Seq{next_seq}:{frames[next_seq]}"
            
            if not frame_lost:
                send_frame_ccf(sock, frame_data)
                print(f"[CLIENT] Sent frame {next_seq}: {frame_data}")
            else:
                print(f"[CLIENT] Frame {next_seq} LOST during transmission")
            
            sent_frames[next_seq] = not frame_lost
            next_seq += 1
            time.sleep(0.2)
        
        # Wait for ACKs
        time.sleep(1)
        
        # Update base based on received ACKs
        while base in ack_received and base < len(frames):
            base += 1
        
        # Timeout and retransmit if no progress
        if base == next_seq - window_size and base < len(frames):
            print(f"[CLIENT] Timeout! Retransmitting from frame {base}")
            next_seq = base
            time.sleep(0.5)
    
    print("[CLIENT] All frames sent successfully")

def get_frames_from_user():
    """Get frames from user input"""
    print("\n" + "="*50)
    print("GO-BACK-N ARQ WITH CHARACTER COUNT FRAMING")
    print("="*50)
    
    while True:
        try:
            num_frames = int(input("\nEnter number of frames to send: "))
            if num_frames <= 0:
                print("Number of frames must be positive!")
                continue
            break
        except ValueError:
            print("Please enter a valid number!")
    
    frames = []
    print(f"\nEnter {num_frames} frames (one per line):")
    for i in range(num_frames):
        frame = input(f"Frame {i}: ").strip()
        if not frame:
            print("Frame cannot be empty! Using default.")
            frame = f"DefaultFrame{i}"
        frames.append(frame)
    
    return frames

def main():
    frames = get_frames_from_user()
    
    print(f"\n[CLIENT] Frames to send: {frames}")
    print("[CLIENT] Connecting to server...")
    
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect(("localhost", 5000))
        print("[CLIENT] Connected to server\n")
        
        sender(sock, frames, window_size=4)
        
        sock.close()
        print("[CLIENT] Connection closed")
    except ConnectionRefusedError:
        print("[CLIENT] ERROR: Cannot connect to server. Make sure server is running!")
    except Exception as e:
        print(f"[CLIENT] ERROR: {e}")

if __name__ == "__main__":
    main()