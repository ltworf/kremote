# Kremote
# Copyright (C) 2012  Salvo "LtWorf" Tomaselli
# 
# kremote is free software: you can redistribute it and/or modify
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
OFLAGS=-O2
CFLAGS=-Wall $(DEFS) $(ARCHFLAGS)  -Wformat -Wextra
#ARCHFLAGS=-m64

all: macbook creative

macbook: mac.o daemon_utils.o
	echo "Compiling the MacBook daemon"
	$(CC) -ggdb3 $(LDFLAGS) $(ARCHFLAGS) $+ -o $@       
	#gcc -O2 -o remoteDaemon.mac mac.c

creative: creative.o daemon_utils.o
	echo "Compiling the creative daemon"
	$(CC) -ggdb3 $(LDFLAGS) $(ARCHFLAGS) $+ -o $@       
	#gcc -O2 -o remoteDaemon.cre main.c

tplayer.c: tplayer.h
mac.c: mac.h
daemon_utils.c: daemon_utils.h
creative.c: creative.h

clean:
	rm -f *.o
	rm -f macbook
	rm -f creative