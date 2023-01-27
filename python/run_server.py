from relay import Relay
from threading import Thread

msg = ""
r = Relay()

def wait_for_input(r):    
    assert type(r) is Relay
    global msg
    while True:
        msg = input()
        if msg == "-1":
            break
        r.write(msg)
    r.shutdown_connection()
    r.shutdown_server_socket()
t = Thread()
t.setDaemon(True)
t.target = wait_for_input(r)
t.start()