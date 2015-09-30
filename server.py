import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
REMOTE_IP = '192.168.0.200'
PORT = 8888
MESSAGE_MAX_SIZE = 1024

if __name__ == '__main__':
    # ' '.join([str(int(random.random()*1000)) for _ in range(30)])
    sock.bind(('', PORT))
    while True:
        data, addr = sock.recvfrom(MESSAGE_MAX_SIZE)
        print 'Received from:', addr
        print 'Data:', data