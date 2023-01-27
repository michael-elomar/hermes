import socket
class Relay:
    def __init__(self):
        self.port = 8080
        self.host = "192.168.1.11"
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR , 1)
        self.socket.bind((self.host, self.port))
        self.socket.listen()
        self.conn, self.addr = self.socket.accept()
    
    def write(self, msg):
        size = len(msg)
        self.conn.sendall(size.to_bytes(4, "little"))
        self.conn.sendall(str.encode(msg, encoding='ascii'))
    
    def shutdown_connection(self):
        self.conn.close()

    def shutdown_server_socket(self):
        self.socket.close()
        