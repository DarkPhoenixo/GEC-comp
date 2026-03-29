import socket
import struct

METHOD_PARITY = 1
METHOD_BLOCK_PARITY = 2
METHOD_CRC8 = 3
METHOD_CRC16 = 4
METHOD_CRC32 = 5
METHOD_CHECKSUM = 6
METHOD_HAMMING = 7

def bytes_to_string(b):
    return b.decode('utf-8', errors='ignore')

def decode_parity(data):
    if len(data) % 2 != 0:
        return "Error: invalid length for parity"
    result = bytearray()
    for i in range(0, len(data), 2):
        byte = data[i]
        parity = data[i+1]
        if bin(byte).count('1') % 2 != parity:
            return "Parity error"
        result.append(byte)
    return bytes(result)

def decode_checksum(data):
    if not data:
        return "Error: no data"
    checksum = data[-1]
    calc = sum(data[:-1]) % 256
    if calc != checksum:
        return "Checksum error"
    return data[:-1]

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

def decode_crc(data, width, poly):
    crc_len = (width + 7) // 8
    if len(data) < crc_len:
        return "Error: data too short"
    crc_bytes = data[-crc_len:]
    data_part = data[:-crc_len]
    crc_val = int.from_bytes(crc_bytes, 'big')
    calc_crc = crc(data_part, poly, width)
    if calc_crc != crc_val:
        return "CRC error"
    return data_part

def decode_block_parity(data):
    if len(data) % 5 != 0:
        return "Error: invalid length for block parity"
    result = bytearray()
    for i in range(0, len(data), 5):
        block = data[i:i+5]
        data_block = block[:4]
        parity = block[4]
        calc = 0
        for b in data_block:
            calc ^= b
        if calc != parity:
            return "Block parity error"
        result.extend(data_block)
    while result and result[-1] == 0:
        result.pop()
    return bytes(result)

def decode_hamming_7_4(data):
    bits = ''.join(format(b, '08b') for b in data)
    decoded_bits = ''
    for i in range(0, len(bits), 7):
        code = bits[i:i+7]
        if len(code) < 7:
            break
        c = [int(x) for x in code]
        s1 = c[0] ^ c[2] ^ c[4] ^ c[6]
        s2 = c[1] ^ c[2] ^ c[5] ^ c[6]
        s4 = c[4] ^ c[5] ^ c[6]
        syndrome = s4 * 4 + s2 * 2 + s1
        if syndrome != 0:
            pos = syndrome - 1
            if pos < 7:
                c[pos] = 1 - c[pos]
        d1, d2, d4, d7 = c[0], c[1], c[3], c[6]
        decoded_bits += str(d1) + str(d2) + str(d4) + str(d7)
    result_bytes = bytearray()
    for i in range(0, len(decoded_bits), 8):
        byte_str = decoded_bits[i:i+8]
        if len(byte_str) == 8:
            result_bytes.append(int(byte_str, 2))
    return bytes(result_bytes)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12345))
server.listen(1)
print("Server listening on port 12345...")

conn, addr = server.accept()
data = conn.recv(4096)
method = struct.unpack('I', data[:4])[0]
encoded = data[4:]

if method == METHOD_PARITY:
    result = decode_parity(encoded)
elif method == METHOD_BLOCK_PARITY:
    result = decode_block_parity(encoded)
elif method == METHOD_CRC8:
    result = decode_crc(encoded, 8, 0x07)
elif method == METHOD_CRC16:
    result = decode_crc(encoded, 16, 0x8005)
elif method == METHOD_CRC32:
    result = decode_crc(encoded, 32, 0x04C11DB7)
elif method == METHOD_CHECKSUM:
    result = decode_checksum(encoded)
elif method == METHOD_HAMMING:
    result = decode_hamming_7_4(encoded)
else:
    result = "Unknown method"

if isinstance(result, bytes):
    print("Received string:", bytes_to_string(result))
else:
    print(result)

conn.close()
server.close()