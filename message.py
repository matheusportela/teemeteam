import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
REMOTE_IP = '192.168.0.201'
PORT = 8888
MESSAGE_MAX_SIZE = 1024

def get_ip_address():
    sock2.connect(('8.8.8.8', 80))
    return sock2.getsockname()[0]

def format_message(contents):
    message = []
    message.append('IP: ' + get_ip_address())
    message.append('STATUS: START')
    message.append('CMD: MIN')
    message.append('MSG: ' + contents)
    return '\n'.join(message)

if __name__ == '__main__':
    # ' '.join([str(int(random.random()*1000)) for _ in range(30)])
    # numbers = '524 938 930 899 210 238 149 38 401 72 577 118 728 911 152 495 962 199 335 190 127 249 760 983 36 156 363 474 312 300'
    # numbers = '535 90 686 380 750 480 262 5 140 456 690 869 705 695 625 75 397 663 995 689 141 601 265 435 688 916 435 714 413 59 289 811 820 688 836 779 182 977 744 318 816 405 17 165 748 635 209 942 854 730 258 292 613 99 251 7 867 370 674 477 986 680 331 637 119 780 537 274 146 705 684 684 867 357 766 277 76 767 627 622 767 150 743 167 919 95 872 460 210 334 681 725 554 885 966 344 549 663 469 318'
    import random
    numbers = ' '.join([str(int(random.random()*1000)) for _ in range(100)])
    message = format_message(numbers)
    print message
    print min([int(v) for v in numbers.split()])
    sock.sendto(message, (REMOTE_IP, PORT))

    # sock.bind(('', PORT))
    # while True:
    #     data, addr = sock.recvfrom(MESSAGE_MAX_SIZE)
    #     print 'Received from:', addr
    #     print 'Data:', data