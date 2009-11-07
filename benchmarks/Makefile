CC      = g++
CFLAGS  = -std=c++98 -pedantic -Wall -O2 -s -DNDEBUG
LDFLAGS =
LOGFILE = log.txt
GRAPHPNG = log.png
GRAPHSVG = log.svg
TIME_CMD = /usr/bin/time -f %U -o $(LOGFILE) -a

all: var array func

var: var.cpp
	$(CC) -o var var.cpp $(CFLAGS)

array: array.cpp
	$(CC) -o array array.cpp $(CFLAGS)

func: func.cpp
	$(CC) -o func func.cpp $(CFLAGS)

clean:
	rm -f var array func core *.dat log*.txt *.png *.svg *.pdf

run:
	if [ -e $(LOGFILE) ] ; then mv $(LOGFILE) log_`date +%F_%T | tr ':' '-'`.txt ; fi
	if [ -e $(GRAPHPNG) ] ; then mv $(GRAPHPNG) log_`date +%F_%T | tr ':' '-'`.png ; fi
	if [ -e $(GRAPHSVG) ] ; then mv $(GRAPHSVG) log_`date +%F_%T | tr ':' '-'`.svg ; fi
	echo -n '0 ' >> $(LOGFILE) ; $(TIME_CMD) ./var
	echo -n '1 ' >> $(LOGFILE) ; $(TIME_CMD) ./array
	echo -n '2 ' >> $(LOGFILE) ; $(TIME_CMD) ./func
	echo -n '0 ' >> $(LOGFILE) ; $(TIME_CMD) ./var.pl
	echo -n '1 ' >> $(LOGFILE) ; $(TIME_CMD) ./array.pl
	echo -n '2 ' >> $(LOGFILE) ; $(TIME_CMD) ./func.pl
	echo -n '0 ' >> $(LOGFILE) ; $(TIME_CMD) ../bbd/bbd var.txt
	echo -n '1 ' >> $(LOGFILE) ; $(TIME_CMD) ../bbd/bbd array.txt
	echo -n '2 ' >> $(LOGFILE) ; $(TIME_CMD) ../bbd/bbd func.txt
	head -n 3 $(LOGFILE) > cpp.dat
	head -n 6 $(LOGFILE) | tail -n 3 > perl.dat
	tail -n 3 $(LOGFILE) > bbd.dat
	gnuplot log_png.plot
	gnuplot log_svg.plot
	rsvg-convert -f pdf -o log.pdf log.svg
