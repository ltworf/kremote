CC=gcc
#DEFS=-Ddebug
OFLAGS=-O3
#-pedantic -Wextra
CFLAGS=-Wall $(DEFS) $(ARCHFLAGS)  -Wformat
LDFLAGS=-lpthread
#ARCHFLAGS=-m64

all: macbook creative mplayer kremote

macbook:
	echo "Compiling the MacBook daemon"
	gcc -O2 -o remoteDaemon.mac mac.c

creative: 
	echo "Compiling the creative daemon"
	gcc -O2 -o remoteDaemon.cre main.c

mplayer:
	echo "Compiling mplayer wrapper"
	gcc -O2 -o tplayer tplayer.c

kremote:
	echo "Compiling kremote daemon"
	gcc -O2 -o kremote kremote.c

clean:
	rm -f *~ kremote tplayer remoteDaemon.cre remoteDaemon.mac
