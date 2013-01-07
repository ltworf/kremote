#!/usr/bin/env python

import argparse
import sys
from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler

shortOut=1

class Handler(BaseHTTPRequestHandler):
    @staticmethod
    def htmlpage():
        r=''
        r+='<html><body>'
        r+='<table>'
        r+='<tr align="center">'
        r+='<td></td>'
        r+='<td><a href="/plus">+</a></td>'
        r+='<td></td>'
        r+='</tr>'
        r+='<tr>'
        r+='<td><a href="/lt">&lt;</a></td>'
        r+='<td><a href="/p">II</a></td>'
        r+='<td><a href="/gt">&gt;</a></td>'
        r+='</tr>'
        r+='<tr>'
        r+='<td></td>'
        r+='<td><a href="/minus">-</a></td>'
        r+='<td></td>'
        r+='</tr>'
        r+='</table>'
        r+='<a href="/menu">Menu</a></body></html>'
        return r


    buttons = { 
            '/p': ('Pause\n', 'p'),
            '/lt': ('Prev\n', '<'),
            '/plus': ('VolUp\n', '+'),
            '/minus': ('VolDown\n','-'),
            '/gt': ('Next\n','>'),
            '/menu': ('Eject\n', 'J')
    }
        
    def do_GET(self):        
        if self.path in self.buttons:
            sys.stdout.write(self.buttons[self.path][shortOut])
            sys.stdout.flush()
        self.wfile.write(Handler.htmlpage())

def main():
    global shortOut
    
    parser = argparse.ArgumentParser(description='kremote HTTP daemon.')
    parser.add_argument('-p', '--port', type=int, default=8080,
                   help='server port')
    parser.add_argument('-H','--hostname', dest='hostname', metavar='h',
                   default='',
                   help='Address to bind (default binds all the interfaces)')
    parser.add_argument('-v','--version', action='version', version='kremote HTTP daemon 1')
    parser.add_argument('-l','--long',help='Uses long output',action='store_true')
    args = parser.parse_args()
    
    if args.long:
        shortOut=0
        
    server=HTTPServer((args.hostname,args.port),Handler)
    server.serve_forever()

if __name__ == '__main__':
    main()
