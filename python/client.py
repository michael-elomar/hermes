import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 56789  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    msg = b'Hello world'
    s.send(msg)
    print(len(msg))


