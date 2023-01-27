# echo-client.py

from node import Node
n = Node()

while True:
    buffer_length = n.read(4)
    buffer_length = int.from_bytes(buffer_length, "little")
    msg = n.read(buffer_length)
    msg = msg.decode('ascii')
    print(msg)
    if msg == "-1":
        print("close")
        n.shutdown()
        exit(0)
