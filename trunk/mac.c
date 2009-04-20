/*                                              
Kremote                                          
Copyright (C) 2009  Salvo "LtWorf" Tomaselli    

Weborf is free software: you can redistribute it and/or modify
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

#include "mac.h"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

int fd;//Descriptor for the serial port
int c;
int res;
int shortOut=TRUE;//Uses the short form for output

int main(int argc, char * argv[]) {
	int i;//used in cycles
	char * device;//Device to use
	if (argc==1) help();
	
	for (i=1;i<argc;i++) {
		if (argv[i][0]==45 && argv[i][1]==45) { //Long argument
			if (0 != strstr(argv[i],"version")) version();
			if (0 != strstr(argv[i],"help")) help();
		} else if (argv[i][0]==45) { //Short argument
			if (0 != strstr(argv[i], "V")) version();
			if (0 != strstr(argv[i], "h")) help();
			if (0 != strstr(argv[i], "l")) shortOut=FALSE;
		} else { //File.
			device=argv[i]; //If file1 was no yet assigned			
		}
	}
	
	//Adds an handler to the SIGINT	
	signal(SIGINT, &close);

    fd = open(device, O_RDONLY); 
	
	char buf[SIGN_LEN]; //Declaring the buffer for the messages
	while (TRUE) {       /* loop for input */
		res = read(fd,buf,SIGN_LEN);   /* Reads the pressure of 1 button and returns */
		
		button(buf[28]);
	}
	
}
void button (char button) {
	if (button==PAUSE) shortOut==FALSE?printf("Pause\n"):printf("p");
    else if (button==PREV) shortOut==FALSE?printf("Prev\n"):printf("<");
    else if (button==VOLUP)shortOut==FALSE? printf("VolUp\n"):printf("+");
    else if (button==VOLDOWN) shortOut==FALSE?printf("VolDown\n"):printf("-");
    else if (button==NEXT) shortOut==FALSE?printf("Next\n"):printf(">");
    else if (button==EJECT) shortOut==FALSE?printf("Eject\n"):printf("J");

	/*else if (button==STOP) shortOut==FALSE?printf("Stop\n"):printf("S");
    if (button==PLAY ) shortOut==FALSE?printf("Play\n"):printf("P");
	else if (button==MUTE) shortOut==FALSE?printf("Mute\n"):printf("M");
	else if (button==FASTBACK)shortOut==FALSE? printf("FastBack\n"):printf("«");
	else if (button==FASTFORW)shortOut==FALSE? printf("FastForw\n"):printf("»");
	else if (button==UP) shortOut==FALSE?printf("Up\n"): printf("u");
	else if (button==DOWN) shortOut==FALSE?printf("Down\n"): printf("d");
	else if (button==LEFT)shortOut==FALSE? printf("Left\n"): printf("l");
	else if (button==RIGHT)shortOut==FALSE? printf("Right\n") : printf("r");
	else if (button==ENTER)shortOut==FALSE? printf("Enter\n"): printf("K");
	else if (button==MENU)shortOut==FALSE? printf("Menu\n"): printf("m");
	else if (button==FULLSCREEN) shortOut==FALSE ? printf("Fullscreen\n") : printf("F");
	else if (button==OSD) shortOut==FALSE ? printf("Osd\n") : printf("O");
	else if (button==SHIFT) shortOut==FALSE ? printf("Shift\n") : printf("s");*/

	fflush(stdout);

}
void version() {	
	printf("Remote control daemon, version 1\n");
}
void help() {
	printf("command [OPTIONS] /dev/usb/hiddevSomething\n");
	exit(0);
}

void close(int signum) {
	printf("Closing remote control daemon...\n");
	exit (0);
}