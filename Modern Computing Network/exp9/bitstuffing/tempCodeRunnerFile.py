import socket
import struct

def unstuff_bits(stuffed):
    unstuffed = ''
    count = 0
    i = 0
    while i < len(stuffed):
        bit = stuffed[i]
        unstuffed += bit
        if bit == '1':
            count += 1
            if count == 5:
                i += 1  # skip the stuffed 0
                count = 0
        else:
            count = 0
        i += 1
    return unstuffed

def bytes_to_bits(data, length):
    bits = ''
    for byte in data:
        bits += format(byte, '08b')
    return bits[:length]

def bits_to_string(bits):
    chars = []
    for i in range(0, len(bits), 8):
        byte_str = bits[i:i+8]
        chars.append(chr(int(byte_str, 2)))
    return ''.join(chars)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12345))
server.listen(1)
print("Server listening on port 12345...")

conn, addr = server.accept()
data = conn.recv(1024)
orig_len = struct.unpack('I', data[:4])[0]
bytes_data = data[4:]
stuffed_bits = bytes_to_bits(bytes_data, orig_len)
unstuffed_bits = unstuff_bits(stuffed_bits)
original_string = bits_to_string(unstuffed_bits)
print("Received unstuffed string:", original_string)
conn.close()
server.close()