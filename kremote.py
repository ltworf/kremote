#!/usr/bin/env python
# -*- coding: utf-8 -*-

import signal
from os import fork, pipe, kill, dup2, close, read, execlp
from sys import exit

import argparse

import notify2

from control import Amarok, Kaffeine

tpid = None

def terminate(x,y):
    kill(tpid, signal.SIGINT)
    notify('Quitting...')
    exit(0)

def notify(message,importance=0):
    icons=('multimedia-player','face-plain','face-sad')
    n = notify2.Notification('kremote', message, icons[importance])
    n.show()
    
def launch_daemon(daemon):
    '''Launches a child process and returns a file descriptor connected to its
    standard output.
    
    daemon is an iterable of the command name plus its arguments
    '''
    global tpid
    
    tpipe=pipe()
    
    tpid=fork()
    if tpid<0:
        notify('Can\'t fork',2)
        exit(1)
    elif tpid==0: #Child
        close (tpipe[0]) #Closes unused end of the pipe
        dup2(tpipe[1],1) #Redirects the stdout
        
        try:
            execlp(daemon[0],*daemon)
        except:
            notify('Can\'t find executable',2)
            exit(1)
    else: #Father
        notify('Ready to work')
        close(tpipe[1])
        return tpipe[0]
    
def main():
    notify2.init ('kremote')
    signal.signal(signal.SIGINT,terminate)
    
    parser = argparse.ArgumentParser(description='kremote daemon.')
    parser.add_argument('-D','--daemon', dest='cmdline', required=True,
                   help='Command line to start the remote daemon')
    parser.add_argument('-v','--version', action='version', version='kremote daemon 1')
    args = parser.parse_args()
    
    print args.cmdline
    
    fd = launch_daemon(args.cmdline.split(' '))
    
    shift = False
    
    while True:
        buf = read(fd,1)
        if len(buf)==0:
            break
        if buf == 's':
            shift = not shift
        print '->', buf
        action(buf, shift)
    notify('Device listener failure',1)
    exit(2)

def action(buf, shift):
    print buf,shift
    
    if Kaffeine.is_running():
        player = Kaffeine()
    elif Amarok.is_running():
        player = Amarok()
    else:
        notify('No player found',1)
        return
    
    a = {
        'p': player.pause,
        'P': player.pause,
        '<': player.prev,
        '>': player.next,
        '-': lambda: player.voldown(5),
        '+': lambda: player.volup(5),
        'J': player.quit,
        'M': player.mute,
        'S': player.stop,
        'F': player.fullscreen,
        '«': lambda: player.posdelta(-5000),
        '»': lambda: player.posdelta(5000),
    }
    
    try:
        a[buf]()
    except:
        pass

if __name__ == '__main__':
    main()