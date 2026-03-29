import socket
import struct

METHOD_PARITY = 1
METHOD_BLOCK_PARITY = 2
METHOD_CRC8 = 3
METHOD_CRC16 = 4
METHOD_CRC32 = 5
METHOD_CHECKSUM = 6
METHOD_HAMMING = 7

def string_to_bytes(s):
    return s.encode('utf-8')

def encode_parity(data):
    encoded = bytearray()
    for byte in data:
        parity = bin(byte).count('1') % 2
        encoded.append(byte)
        encoded.append(parity)
    return bytes(encoded)

def encode_checksum(data):
    checksum = sum(data) % 256
    return data + bytes([checksum])

def crc(data, poly, width):
    crc = 0
    for byte in data:
        crc ^= (byte << (width - 8))
        for _ in range(8):
            if crc & (1 << (width - 1)):
                crc = (crc << 1) ^ poly
            else:
                crc <<= 1
            crc &= (1 << width) - 1
    return crc

def encode_crc(data, width, poly):
    crc_val = crc(data, poly, width)
    crc_bytes = crc_val.to_bytes((width + 7) // 8, 'big')
    return data + crc_bytes

def encode_block_parity(data):
    padded = data + b'\x00' * ((4 - len(data) % 4) % 4)
    encoded = bytearray()
    for i in range(0, len(padded), 4):
        block = padded[i:i+4]
        parity = 0
        for b in block:
            parity ^= b
        encoded.extend(block)
        encoded.append(parity)
    return bytes(encoded)

def encode_hamming_7_4(data):
    bits = ''.join(format(b, '08b') for b in data)
    padded_bits = bits + '0' * ((4 - len(bits) % 4) % 4)
    encoded_bits = ''
    for i in range(0, len(padded_bits), 4):
        d = padded_bits[i:i+4]
        d1, d2, d3, d4 = int(d[0]), int(d[1]), int(d[2]), int(d[3])
        p1 = d1 ^ d2 ^ d4
        p2 = d1 ^ d3 ^ d4
        p4 = d2 ^ d3 ^ d4
        code = f"{d1}{p1}{d2}{p2}{d3}{p4}{d4}"
        encoded_bits += code
    encoded_bytes = bytearray()
    for i in range(0, len(encoded_bits), 8):
        byte_str = encoded_bits[i:i+8]
        byte_str += '0' * (8 - len(byte_str))
        encoded_bytes.append(int(byte_str, 2))
    return bytes(encoded_bytes)

while True:
    print("Select error detection method:")
    print("1. Parity bit")
    print("2. Block parity")
    print("3. CRC8")
    print("4. CRC16")
    print("5. CRC32")
    print("6. Checksum")
    print("7. Hamming code")
    try:
        choice = int(input("Enter choice (1-7): "))
        user_input = input("Enter string: ")
        data = string_to_bytes(user_input)
        if choice == 1:
            encoded = encode_parity(data)
            method = METHOD_PARITY
        elif choice == 2:
            encoded = encode_block_parity(data)
            method = METHOD_BLOCK_PARITY
        elif choice == 3:
            encoded = encode_crc(data, 8, 0x07)
            method = METHOD_CRC8
        elif choice == 4:
            encoded = encode_crc(data, 16, 0x8005)
            method = METHOD_CRC16
        elif choice == 5:
            encoded = encode_crc(data, 32, 0x04C11DB7)
            method = METHOD_CRC32
        elif choice == 6:
            encoded = encode_checksum(data)
            method = METHOD_CHECKSUM
        elif choice == 7:
            encoded = encode_hamming_7_4(data)
            method = METHOD_HAMMING
        else:
            print("Invalid choice.")
            continue
        message = struct.pack('I', method) + encoded
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(('localhost', 12345))
        client.send(message)
        client.close()
        print("Sent data.")
        break
    except ValueError:
        print("Invalid input.")