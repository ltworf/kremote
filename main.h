#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define FALSE 0
#define TRUE 1

void close(int);
void openDev(char*);
void button(int);
void help();
void version();


//Codes for buttons
#define PLAY -1738078899
#define STOP 1487340877
#define PAUSE -668531379
#define EJECT 952567117
#define PREV -1203305139
#define NEXT 83559757
#define FASTBACK 2022114637
#define FASTFORW -133757619
#define MUTE -200604339
#define VOLUP 885720397
#define VOLDOWN 217253197
#define SHIFT 618333517

#define UP 1153107277
#define DOWN 1420494157
#define ENTER 1687881037
#define LEFT -1537538739
#define RIGHT -467991219
#define MENU -1270151859

#define FULLSCREEN -735378099
#define OSD -1804925619



