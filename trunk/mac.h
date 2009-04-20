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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

void close(int fd);
void button(char button);
void help();
void version();

#define SIGN_LEN 32

//Codes for buttons
#define PAUSE 5
#define VOLUP 10
#define VOLDOWN 12
#define PREV 9
#define NEXT 6
#define EJECT 3

/*#define STOP 1487340877

#define PLAY 5
#define FASTBACK 2022114637
#define FASTFORW -133757619
#define MUTE -200604339
#define SHIFT 618333517

#define UP 1153107277
#define DOWN 1420494157
#define ENTER 1687881037
#define LEFT -1537538739
#define RIGHT -467991219
#define MENU -1270151859

#define FULLSCREEN -735378099
#define OSD -1804925619
*/