# Kremote
# Copyright (C) 2009  Salvo "LtWorf" Tomaselli
# 
# Weborf is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC=gcc
#DEFS=-Ddebug
OFLAGS=-O3
#-pedantic -Wextra
CFLAGS=-Wall $(DEFS) $(ARCHFLAGS)  -Wformat
LDFLAGS=-lpthread
#ARCHFLAGS=-m64

all: macbook creative mplayer kremote

macbook: mac.o
	echo "Compiling the MacBook daemon"
	$(CC) -ggdb3 $(LDFLAGS) $(ARCHFLAGS) $+ -o $@		
	#gcc -O2 -o remoteDaemon.mac mac.c

creative: main.o 
	echo "Compiling the creative daemon"
	$(CC) -ggdb3 $(LDFLAGS) $(ARCHFLAGS) $+ -o $@		
	#gcc -O2 -o remoteDaemon.cre main.c

mplayer: tplayer.o
	echo "Compiling mplayer wrapper"
	$(CC) -ggdb3 $(LDFLAGS) $(ARCHFLAGS) $+ -o $@		
	#gcc -O2 -o tplayer tplayer.c

kremote: kremote.o
	echo "Compiling kremote daemon"
	$(CC) -ggdb3 $(LDFLAGS) $(ARCHFLAGS) $+ -o $@		
	#gcc -O2 -o kremote kremote.c

main.c: main.h
tplayer.c: tplayer.h
mac.c: mac.h
kremote.c: kremote.h
daemon_utils.c: daemon_utils.h

clean:
	rm -f *~ kremote tplayer remoteDaemon.cre remoteDaemon.mac
