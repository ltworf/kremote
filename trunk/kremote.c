/*
*  C Implementation: kremote
*
* Description:
*
*
* Author: LtWorf <ltworf@galileo.dmi.unict.it>, (C) 2007
*
* Copyright: See COPYING file that comes with this distribution
*
*/

#include "kremote.h"


int tpid;//Pid of the remote daemon process
int tpipe[2];//Descriptors for pipe

int main(int argc, char * argv[]) {

    signal(SIGINT, &terminate);//Adds a signal handler.

    //Start the daemon
    pipe(tpipe);//Creates the pipe
    tpid=fork();//Forks
    if (tpid<0) exit(1); //An error occured
    if (tpid==0) {//Child
        fclose (stdout); //Closing the stdout
        close (tpipe[0]); //Closes unused end of the pipe
        dup(tpipe[1]); //Redirects the stdout
        char * port;
        if (argc>1)port=argv[1];
        else port="/dev/ttyS0";
        execlp("remoteDaemon","remoteDaemon", port ,(char *)0);//Exec the daemon
        printf("Can't find remoteDaemon executable");
#ifdef KDE4
        system("kdialog --title kremote --passivepopup \"Can't find remoteDaemon executable\"");
#else
        system("dcop knotify Notify notify executableError kremote \"Can't find remoteDaemon executable\" '' '' 16 0");
#endif

    }

#ifdef KDE4
    system("kdialog --title kremote --passivepopup \"Ready to work\"");
#else
    system("dcop knotify Notify notify ready kremote \"Ready to work\" '' '' 16 0");
#endif


    char buf;//Buffer containing the remote command issued
    int shift=FALSE;
    while (read(tpipe[0], &buf, 1) > 0) {
        printf("Letto un carattere: %c\n",buf);

        if (buf=='s') {//shift
            shift= !shift; //=FALSE ? shift=TRUE : shift=FALSE;
            printf("Shift mode %d",shift);
        }

        action(buf, shift); //Will do the necessary action

    }

}

void action (char cmd, int shift) {

    int mode;

    if (isKaffeine()==TRUE) mode=KAFFEINE;
    else if (isAmarok()==TRUE) mode=AMAROK;
    else mode=NO_PLAYER;

    char * command;
    if (mode==KAFFEINE) {
        switch (cmd) {

#ifdef KDE4
            //Basic controls
        case 'p':
        case 'P':
            command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.Pause";
            break;
        case 'S':
            command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.Stop";
            break;
        case 'J':
            command="qdbus org.kde.kaffeine /MainApplication org.kde.KApplication.quit";
            break;//Not sure if have to keep that

            //Position
        case '<':
            command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.Prev";
            break;
        case '>':
            command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.Next";
            break;
        case '«':
            command="m=`qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.PositionGet`-5000; p=`echo $m|bc`; qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.PositionSet $p";
            break;
        case '»':
            command="m=`qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.PositionGet`+5000; p=`echo $m|bc`; qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.PositionSet $p";
            break;

            //Volume
        case '+':
            command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.IncreaseVolume";
            break;
        case '-':
            command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.DecreaseVolume";
            break;
        case 'M':
            command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.ToggleMuted";
            break;

            //Screen
        case 'F':
            command="qdbus org.kde.kaffeine /Player org.freedesktop.MediaPlayer.ToggleFullScreen";
            break;
#else
            //Basic controls
        case 'P':
            command="dcop kaffeine KaffeineIface play";
            break;
        case 'S':
            command="dcop kaffeine KaffeineIface stop";
            break;
        case 'p':
            command="dcop kaffeine KaffeineIface pause";
            break;
        case 'J':
            command="dcop kaffeine KaffeineIface quit";
            break;//Not sure if have to keep that

            //Position
        case '<':
            command="dcop kaffeine KaffeineIface previous";
            break;
        case '>':
            command="dcop kaffeine KaffeineIface next";
            break;
        case '«':
            command="dcop kaffeine KaffeineIface posMinus";
            break;
        case '»':
            command="dcop kaffeine KaffeineIface posPlus";
            break;

            //Volume
        case '+':
            command="dcop kaffeine KaffeineIface volUp";
            break;
        case '-':
            command="dcop kaffeine KaffeineIface volDown";
            break;
        case 'M':
            command="dcop kaffeine KaffeineIface mute";
            break;

            //Screen
        case 'F':
            command="dcop kaffeine KaffeineIface fullscreen";
            break;
#endif
        }
    } else if (mode==AMAROK) {
        switch (cmd) {
#ifdef KDE4

            //Volume
        case '+':
            command="qdbus org.kde.amarok /Player VolumeDown -5";
            break;
        case '-':
            command="qdbus org.kde.amarok /Player VolumeDown 5";
            break;
        case 'M':
            command="qdbus org.kde.amarok /Player Mute";
            break;

            //Basic controls
        case 'P':
            command="qdbus org.kde.amarok /Player Pause";
            break;
        case 'S':
            command="qdbus org.kde.amarok /Player Stop";
            break;
        case 'p':
            command="qdbus org.kde.amarok /Player Pause";
            break;
        case 'J':
            command="qdbus org.kde.amarok /MainApplication quit";
            break;//Not sure if have to keep that

            //Position
        case '<':
            command="qdbus org.kde.amarok /Player Prev";
            break;
        case '>':
            command="qdbus org.kde.amarok /Player Next";
            break;
        case '«':
            command="dcop amarok player seekRelative -";
            break;
        case '»':
            command="dcop amarok player seekRelative +10";
            break;
#else
            //Volume
        case '+':
            command="dcop amarok player volumeUp";
            break;
        case '-':
            command="dcop amarok player volumeDown";
            break;
        case 'M':
            command="dcop amarok player mute";
            break;

            //Basic controls
        case 'P':
            command="dcop amarok player playPause";
            break;
        case 'S':
            command="dcop amarok player stop";
            break;
        case 'p':
            command="dcop amarok player playPause";
            break;
        case 'J':
            command="dcop amarok MainApplication-Interface quit";
            break;//Not sure if have to keep that

            //Position
        case '<':
            command="dcop amarok player prev";
            break;
        case '>':
            command="dcop amarok player next";
            break;
        case '«':
            command="m=`qdbus org.kde.amarok /Player PositionGet`-10000; p=`echo $m |bc`; qdbus org.kde.amarok /Player PositionSet $p";
            break;
        case '»':
            command="m=`qdbus org.kde.amarok /Player PositionGet`+10000; p=`echo $m |bc`; qdbus org.kde.amarok /Player PositionSet $p";
            break;
#endif
        }
    } else {//Executing Amarok
#ifdef KDE4
        system("kdialog --title kremote --passivepopup \"Executing Amarok\"");
#else
        system("dcop knotify Notify notify executingAmarok kremote \"Executing Amarok\" '' '' 16 0");
#endif
        int pid=fork();
        if (pid==0)
            execlp("amarok","amarok",(char *)0);//Exec amarok
    }

    system(command);

}




/**
	Returns true if Kaffeine is running
*/
int isKaffeine() {
    if (system("dcop |fgrep kaffeine")==0) return TRUE;
    return FALSE;
}

/**
	Returns true if Amarok is running
*/
int isAmarok() {
#ifdef KDE4
    if (system("qdbus |fgrep org.kde.amarok")==0) return TRUE;
#else
    if (system("dcop |fgrep amarok")==0) return TRUE;
#endif
    return FALSE;
}

void terminate(int signum) {

    closeDaemon();
    exit (0);
}

void closeDaemon() {
    close(tpipe[1]);//Closing reading end of the pipe
    printf("Closing remote control daemon...\n");
    kill(tpid, SIGINT);//Sending a SIGINT to the daemon, so it will exit
}

