import socket
import time
import crypt

password = "shailesh"

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM,
                       socket.IPPROTO_UDP)  # UDP
#
# server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
# server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
# server.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
# server.settimeout(0.2)
client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

client.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

client.bind(("", 2020))
while True:
    data, addr = client.recvfrom(1024)
    ip_addr = addr[0]
    break


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# sock.bind(("0.0.0.0", 2022))
# sock.listen(1)

time.sleep(1)
# server.sendto(b"SUTO_UDP_HELLO_REPLY", (ip_addr, 2021))

print("Connecting For TCP...")
# connection, client_address = sock.accept()
sock.connect((ip_addr, 2021))
print("connected", ip_addr)
time.sleep(1)
try:
    sock.sendall(b"SUTO_C_GET_SALT")
    print("Sent SUTO_C_GET_SALT")
    linux_salt = sock.recv(1024)[10:]
    print(f"Received salt {linux_salt}")
    sock.sendall(b"SUTO_C_GET_RSALT")
    print("Sent SUTO_C_GET_RSALT")
    rsalt = sock.recv(1024)[11:]
    print(f"Received rsalt:{rsalt}")
    linuxpwhash = crypt.crypt(password, salt=linux_salt)
    print(f"linux hash is {linuxpwhash}")
    phash = crypt.crypt(linuxpwhash, salt=rsalt)
    sock.sendall(b"SUTO_C_F_HASH_"+phash)
    print(f"Sent final hash: {phash}")
    final_message = sock.recv(1024)
    if final_message == "SUTO_AUTH_SUCCESS":
        print("Success")
    elif final_message == "SUTO_AUTH_FAILED":
        print("Failed")
    else:
        print("Error")
finally:
    sock.close()
    # server.close()
    client.close()
