import socket

"""
GET /chat HTTP/1.1
Host: example.com:8000
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
Sec-WebSocket-Version: 13
"""

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 56789  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    msg = "GET /chat HTTP/1.1\r\n"
    msg += f"Host: {HOST}:{PORT}\r\n"
    msg += "Updgrade: websocket\r\n"
    msg += "Connection: Upgrade\r\n"
    msg += "Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
    msg += "Sec-WebSocket-Version: 13\r\n\r\n"
    s.send(msg.encode('utf-8'))

    print(s.recv(1024))

