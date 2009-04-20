#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void terminate(int);
void closeDaemon();
const int TRUE=1;
const int FALSE=0;

