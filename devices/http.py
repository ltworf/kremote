import argparse
from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler

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
            print self.buttons[self.path]
        self.wfile.write(Handler.htmlpage())

server=HTTPServer(('',8080),Handler)
print dir(server)
server.serve_forever()

