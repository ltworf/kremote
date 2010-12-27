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


#ifndef KREMOTE_MAC_H
#define KREMOTE_MAC_H

#define FALSE 0
#define TRUE 1

void quit(int fd);
void button(char button);

#define SIGN_LEN 32

//Codes for buttons
#define PAUSE 5
#define VOLUP 10
#define VOLDOWN 12
#define PREV 9
#define NEXT 6
#define EJECT 3

#endif
