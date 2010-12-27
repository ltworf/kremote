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

#ifndef KREMOTE_KREMOTE_H
#define KREMOTE_KREMOTE_H


#define TRUE 1
#define FALSE 0

#define KAFFEINE 1
#define AMAROK 2
#define NO_PLAYER 3

#define KDE4

void terminate(int);
void closeDaemon();
int isKaffeine();
int isAmarok();
void action (char,int);


#endif
