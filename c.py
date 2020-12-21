import socket
import json
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(('127.0.0.1',8087))

print(s.recv(1024)) # welcome start

dic = {}
dic['freq'] = 155194500
dic['tdb'] = 10
dic['enable'] = 1 
dic['data_bytes'] = 32
dic['data'] = '0123456789abcdef' 
dic['cmd_en'] = 1
dic['data_en'] = 1
dic['overwrite'] = 0

head_info = json.dumps(dic)  
head_info_len = struct.pack('i', len(head_info)) 
s.send(head_info_len)  
s.send(head_info.encode('utf-8'))

print(s.recv(1024)) #welcome finish
s.close()    

