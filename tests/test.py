import socket
import time

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM,
                       socket.IPPROTO_UDP)  # UDP

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
server.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
server.settimeout(0.2)
client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

client.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

client.bind(("", 2020))
while True:
    data, addr = client.recvfrom(1024)
    ip_addr = addr[0]
    break


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("0.0.0.0", 2022))
sock.listen(1)

time.sleep(1)
server.sendto(b"SUTO_UDP_HELLO_REPLY", (ip_addr, 2021))

print("Waiting For TCP...")
connection, client_address = sock.accept()
print("connected", client_address)
time.sleep(1)
sock.close()
server.close()
