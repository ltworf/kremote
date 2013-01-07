#!/usr/bin/env python
# -*- coding: utf-8 -*-

import signal
from os import fork, pipe, kill, dup, close, read, execlp
from sys import exit, stdin, stdout
import notify2

from control import Amarok, Kaffeine

tpid = None

def terminate(signum):
    kill(tpid, signal.SIGINT)
    notify('Closing kremote')
    exit(0)

def notify(message,importance=0):
    icons=('multimedia-player','multimedia-player','multimedia-player')
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
        stdout.close()
        
        close (tpipe[0]) #Closes unused end of the pipe
        dup(tpipe[1]) #Redirects the stdout
        
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
    
    #TODO use arguments
    d = ('/home/salvo/dev/kremote/devices/http.py', '-p', '8001')
    
    fd = launch_daemon(d)
    
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
    
#void action (char cmd, int shift) {

    #int mode;

    #if (isKaffeine()==TRUE) mode=KAFFEINE;
    #else if (isAmarok()==TRUE) mode=AMAROK;
    #else mode=NO_PLAYER;

    #char * command=NULL;
    #if (mode==KAFFEINE) {
        #switch (cmd) {

##ifdef KDE4
            #//Basic controls
        #case 'p':
        #case 'P':
            #command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.Pause";
            #break;
        #case 'S':
            #command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.Stop";
            #break;
        #case 'J':
            #command="qdbus org.kde.kaffeine /MainApplication org.kde.KApplication.quit";
            #break;//Not sure if have to keep that

            #//Position
        #case '<':
            #command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.Prev";
            #break;
        #case '>':
            #command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.Next";
            #break;
        #case '«':
            #command="m=`qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.PositionGet`-5000; p=`echo $m|bc`; qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.PositionSet $p";
            #break;
        #case '»':
            #command="m=`qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.PositionGet`+5000; p=`echo $m|bc`; qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.PositionSet $p";
            #break;

            #//Volume
        #case '+':
            #command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.IncreaseVolume";
            #break;
        #case '-':
            #command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.DecreaseVolume";
            #break;
        #case 'M':
            #command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.ToggleMuted";
            #break;

            #//Screen
        #case 'F':
            #command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.ToggleFullScreen";
            #break;
        #}
    #} else if (mode==AMAROK) {
        #switch (cmd) {
##ifdef KDE4

            #//Volume
        #case '+':
            #command="qdbus org.kde.amarok /Player VolumeDown -5";
            #break;
        #case '-':
            #command="qdbus org.kde.amarok /Player VolumeDown 5";
            #break;
        #case 'M':
            #command="qdbus org.kde.amarok /Player Mute";
            #break;

            #//Basic controls
        #case 'P':
            #command="qdbus org.kde.amarok /Player Pause";
            #break;
        #case 'S':
            #command="qdbus org.kde.amarok /Player Stop";
            #break;
        #case 'p':
            #command="qdbus org.kde.amarok /Player Pause";
            #break;
        #case 'J':
            #command="qdbus org.kde.amarok /MainApplication quit";
            #break;//Not sure if have to keep that

            #//Position
        #case '<':
            #command="qdbus org.kde.amarok /Player Prev";
            #break;
        #case '>':
            #command="qdbus org.kde.amarok /Player Next";
            #break;
        #case '«':
            #command="m=`qdbus org.kde.amarok /Player PositionGet`-10000; p=`echo $m |bc`; qdbus org.kde.amarok /Player PositionSet $p";
            #break;
        #case '»':
            #command="m=`qdbus org.kde.amarok /Player PositionGet`+10000; p=`echo $m |bc`; qdbus org.kde.amarok /Player PositionSet $p";
            #break;
        #}
    #} else {//Executing Amarok
##ifdef KDE4
        #system("kdialog --title kremote --passivepopup \"Executing Amarok\"");
##else
        #system("dcop knotify Notify notify executingAmarok kremote \"Executing Amarok\" '' '' 16 0");
##endif
        #int pid=fork();
        #if (pid==0)
            #execlp("amarok","amarok",(char *)0);//Exec amarok
    #}

    #system(command);

#}

if __name__ == '__main__':
    main()