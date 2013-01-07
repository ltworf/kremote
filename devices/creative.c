/*
Kremote
Copyright (C) 2010  Salvo "LtWorf" Tomaselli

Kremote is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

@author Salvo "LtWorf" Tomaselli <tiposchi@tiscali.it>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#include "daemon_utils.h"
#include "creative.h"

#define BAUDRATE B2400
#define _POSIX_SOURCE 1 /* POSIX compliant source */

const int SIGN_LEN=6;

int fd;//Descriptor for the serial port
int c;
int res;
struct termios oldtio,newtio; //Old and new port propertyes


int shortOut=TRUE;//Uses the short form for output

int main(int argc, char * argv[]) {


    int i;//used in cycles
    char * device;//Device to use
    if (argc==1) help();

    for (i=1; i<argc; i++) {


        if (argv[i][0]==45 && argv[i][1]==45) { //Long argument
            if (0 != strstr(argv[i],"version")) version();
            if (0 != strstr(argv[i],"help")) help();

        } else if (argv[i][0]==45) { //Short argument
            if (0 != strstr(argv[i], "v")) version();
            if (0 != strstr(argv[i], "h")) help();
            if (0 != strstr(argv[i], "l")) shortOut=FALSE;


        } else { //File.
            device=argv[i]; //If file1 was no yet assigned
        }
    }

    //Adds an handler to the SIGINT
    signal(SIGINT, &quit);

    openDev(device);

    int buf[SIGN_LEN]; //Declaring the buffer for the messages
    while (TRUE) {       /* loop for input */
        res = read(fd,buf,SIGN_LEN);   /* Reads the pressure of 1 button and returns */

        /*for (i=0;i<SIGN_LEN;i++) {
        	printf("%d ",buf[i]);
        }

        if (buf[1]==8620  && buf[5]==0) printf("OK");
        printf("\n");*/

        button(buf[0]);

    }

}
void button (int btn) {
    switch (btn) {
        case PLAY:
            shortOut==FALSE?printf("Play\n"):printf("P");
            break;
        case STOP:
            shortOut==FALSE?printf("Stop\n"):printf("S");
            break;
        case PAUSE:
            shortOut==FALSE?printf("Pause\n"):printf("p");
            break;
        case EJECT:
            shortOut==FALSE?printf("Eject\n"):printf("J");
            break;
        case PREV:
            shortOut==FALSE?printf("Prev\n"):printf("<");
            break;
        case NEXT:
            shortOut==FALSE?printf("Next\n"):printf(">");
            break;
        case MUTE:
            shortOut==FALSE?printf("Mute\n"):printf("M");
            break;
        case VOLUP:
            shortOut==FALSE? printf("VolUp\n"):printf("+");
            break;
        case VOLDOWN:
            shortOut==FALSE?printf("VolDown\n"):printf("-");
            break;
        case FASTBACK:
            shortOut==FALSE? printf("FastBack\n"):printf("«");
            break;
        case FASTFORW:
            shortOut==FALSE? printf("FastForw\n"):printf("»");
            break;
        case UP:
            shortOut==FALSE?printf("Up\n"): printf("u");
            break;
        case DOWN:
            shortOut==FALSE?printf("Down\n"): printf("d");
            break;
        case LEFT:
            shortOut==FALSE? printf("Left\n"): printf("l");
            break;
        case RIGHT:
            shortOut==FALSE? printf("Right\n") : printf("r");
            break;
        case ENTER:
            shortOut==FALSE? printf("Enter\n"): printf("K");
            break;
        case MENU:
            shortOut==FALSE? printf("Menu\n"): printf("m");
            break;
        case FULLSCREEN:
            shortOut==FALSE ? printf("Fullscreen\n") : printf("F");
            break;
        case OSD:
            shortOut==FALSE ? printf("Osd\n") : printf("O");
            break;
        case SHIFT:
            shortOut==FALSE ? printf("Shift\n") : printf("s");
            break;
    }

    fflush(stdout);

}

void quit(int signum) {
    printf("Closing remote control daemon...\n");
    tcsetattr(fd,TCSANOW,&oldtio);//Restores the old attributes
    exit (0);
}

void openDev(char* dev) {
    fd = open(dev, O_RDWR | O_NOCTTY );

    //Exits if an error occurs
    if (fd <0) {
        perror(dev);
        exit(-1);
    }

    tcgetattr(fd,&oldtio); /* save current port settings */

    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
    newtio.c_cc[VMIN]     = SIGN_LEN;   /* blocking read until 5 chars received */

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
}

