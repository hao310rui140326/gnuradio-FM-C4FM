import socket
import threading
import struct
import json

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)

s.bind(('127.0.0.1', 8087))
##s.bind(('192.168.0.108', 8087))
s.listen(5)

cnt=0 

def map(a):
    b=-3
    if a==0:
        b=1
    if a==1:
        b=3
    if a==2:
        b=-1
    return b 

def float_to_hex(f):
    return struct.pack('f',f) 

def handle_tcp(sock, addr,cnt):
    print("new connection from %s:%s" % addr)
    sock.send(b'Welcome start!')

    #total_data=[]
    #while True:
    #    data = sock.recv(1024)
    #    if not data:
    #        break
    #    #total_data.append(data)
    data_len_s = sock.recv(4)
    data_len_t = struct.unpack('i',data_len_s)
    data_len = data_len_t[0]
    print("data length is %d" % data_len)
    data=sock.recv(data_len)
    total_data=data
    sock.send(b'Welcome end with %d bytes received!' % data_len)
    sock.close()

    #write total_data into file
    recv_json = json.loads(total_data.decode('utf-8'))
    ##print(recv_json)
    print(recv_json['freq'])
    if recv_json['data_en']==1:
        if recv_json['overwrite']==1:
            fd=open("rx_data","wb")
        else:    
            fd=open("rx_data","ab")
        music=recv_json['data']
        for i in range(len(music)):
            a=0
            b=0  
            if music[i] == '0': ### 00 to 
                a=0
                b=0  
            if music[i] == '1': ### 00 to 
                a=0
                b=1  
            if music[i] == '2': ### 00 to 
                a=0
                b=2  
            if music[i] == '3': ### 00 to 
                a=0
                b=3  
            if music[i] == '4': ### 00 to 
                a=1
                b=0  
            if music[i] == '5': ### 00 to 
                a=1
                b=1  
            if music[i] == '6': ### 00 to 
                a=1
                b=2  
            if music[i] == '7': ### 00 to 
                a=1
                b=3  
            if music[i] == '8': ### 00 to 
                a=2
                b=0  
            if music[i] == '9': ### 00 to 
                a=2
                b=1  
            if music[i] == 'a' or music[i] == 'A' : ### 00 to 
                a=2
                b=2  
            if music[i] == 'b' or music[i] == 'B' : ### 00 to 
                a=2
                b=3  
            if music[i] == 'c' or music[i] == 'C' : ### 00 to 
                a=3
                b=0  
            if music[i] == 'd' or music[i] == 'D' : ### 00 to 
                a=3
                b=1  
            if music[i] == 'e' or music[i] == 'E' : ### 00 to 
                a=3
                b=2  
            if music[i] == 'f' or music[i] == 'F' : ### 00 to 
                a=3
                b=3  
                
            fd.write(float_to_hex(map(a)))
            fd.write(float_to_hex(map(b)))
            #fd.write(struct.pack(str(a),x))
            #fd.write(struct.pack(str(b),x))
        fd.close()    
    if recv_json['cmd_en']==1:
        fc=open("cmd","w")
        fc.write("%d\n" % recv_json['enable'])
        fc.write("%d\n" % recv_json['freq'])
        fc.write("%d\n" % cnt)
        fc.write("%d\n" % recv_json['data_bytes'])
        fc.write("%d\n" % recv_json['overwrite'])
        fc.close()    

while True:
    sock, addr = s.accept()
    cnt+=1
    if cnt==256:
        cnt=1
    t = threading.Thread(target=handle_tcp, args=(sock, addr,cnt))
    t.start()
    print("the %d connection" % cnt )    
