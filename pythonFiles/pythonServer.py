from socket import *
import sys

port = sys.argv[0]

sock = socket(AF_INET,SOCK_STREAM)
host = '127.0.0.1'
sock.connect((host,port))
header_counter = 0
while True:
    buffer = sock.recv(4096)
    html = str(buffer,'utf8')
    request = html.split("\r\n\r\n")[0]
    request_lines = request.split("\r\n")
    first_line_words = request_lines[0].split(' ')
    if((first_line_words[0]==r"GET") and (first_line_words[1]==r"/counter")):
        header_counter += 1
        header_counter_string = str(header_counter)
        sock.send(bytes(r'HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: '
        +str(len(header_counter_string))+r'\r\n\r\n'+header_counter_string+r'\r\n\r\n','utf8'))
    else:
        sock.send(bytes(r"""HTTP/1.1 404 Not Found\r\n
        Content-type: text/html\r\n
        Content-length: 113\r\n
        <html><head><title>Not Found</title></head><body>\r\n
        Sorry, the object you requested was not found.\r\n
        </body></html>\r\n\r\n""",'utf8'))
    continue

         




