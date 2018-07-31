cc=gcc
flags=-Wall `pkg-config --cflags --libs cairo`


sierpinskit: main.c utils.o
	$(cc) $(flags) -o sierpinskit $^

runscratch: scratch.out
	./scratch.out temp.png
	eog ./temp.png

scratch.out: scratch.c utils.o
	$(cc) $(flags) -o scratch.out $^

utils.o: utils.h utils.c
	$(cc) $(flags) -c $^
