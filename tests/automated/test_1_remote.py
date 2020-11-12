import socket
import time
import crypt

TEST_PASS = "test_pass"

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM,
                       socket.IPPROTO_UDP)  # UDP
client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

client.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

client.bind(("", 2020))
while True:
    data, addr = client.recvfrom(1024)
    print("Auth Request from {}".format(data.decode()[5:-1]))
    username = data.decode()[5:].split("@")[0]
    ip_addr = addr[0]
    break


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

time.sleep(1)

print("Connecting For TCP...")
sock.connect((ip_addr, 2021))
print("connected", ip_addr)
time.sleep(1)
try:
    sock.sendall(b"SUTO_C_GET_SALTA")
    print("Sent SUTO_C_GET_SALTA")
    linux_salt_msg = sock.recv(102400)
    lsalt = linux_salt_msg[11:30].decode("utf-8")
    random_salt = linux_salt_msg[31:].decode("utf-8")
    print("SALT:-" + lsalt)
    print("RSALT:-" + random_salt)
    password = TEST_PASS
    linuxpwhash = crypt.crypt(password, salt=lsalt)
    print(f"linux hash is {linuxpwhash}")
    phash = crypt.crypt(linuxpwhash, salt=random_salt)
    sock.sendall(bytes("SUTO_CF_HASH_" + phash, "utf-8"))
    print(f"Sent final hash: {phash}")
    final_message = sock.recv(102400).decode("utf-8")
    if final_message == "SUTO_AUTH_1":
        print("Success")
    elif final_message == "SUTO_AUTH_0":
        print("Failed")
    else:
        print("Error")
finally:
    sock.close()
    client.close()
