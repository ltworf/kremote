/*
Kremote
Copyright (C) 2009  Salvo "LtWorf" Tomaselli

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

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


#include "mac.h"
#include "daemon_utils.h"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

int fd; /* Descriptor for the hid device file */
int c;
int res;
int shortOut=TRUE; /* Uses the short form for output */

int main(int argc, char * argv[]) {
    int i;//used in cycles
    char * device;//Device to use
    char buf[SIGN_LEN]; //Declaring the buffer for the messages
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

    fd = open(device, O_RDONLY);

    
    while (TRUE) {       /* loop for input */
        res = read(fd,buf,SIGN_LEN);   /* Reads the pressure of 1 button and returns */

        button(buf[28]);
    }

}
void button (char btn) {
    switch (btn) {
        case PAUSE:
            shortOut==FALSE?printf("Pause\n"):printf("p");
            break;
        case PREV:
            shortOut==FALSE?printf("Prev\n"):printf("<");
            break;
        case VOLUP:
            shortOut==FALSE? printf("VolUp\n"):printf("+");
            break;
        case VOLDOWN:
            shortOut==FALSE?printf("VolDown\n"):printf("-");
            break;
        case NEXT:
            shortOut==FALSE?printf("Next\n"):printf(">");
            break;
        case EJECT:
            shortOut==FALSE?printf("Eject\n"):printf("J");
            break;
    }

    fflush(stdout);

}

void quit(int signum) {
    printf("Closing remote control daemon...\n");
    exit (0);
}