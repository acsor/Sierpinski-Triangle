cc=gcc
flags=-Wall `pkg-config --cflags --libs cairo`


runscratch: scratch.out
	./scratch.out temp.png
	eog temp.png

scratch.out: scratch.c
	$(cc) $(flags) -o scratch.out $^
