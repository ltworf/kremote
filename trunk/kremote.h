//
// C++ Interface: kremote
//
// Description: 
//
//
// Author: LtWorf <ltworf@galileo.dmi.unict.it>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

#define KAFFEINE 1
#define AMAROK 2
#define NO_PLAYER 3

void terminate(int);
void closeDaemon();
int isKaffeine();
int isAmarok();
void action (char,int);


