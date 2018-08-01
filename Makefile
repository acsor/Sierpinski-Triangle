cc=gcc
flags=-Wall `pkg-config --cflags --libs cairo`


.PHONY: runscratch clean

sierpinskit: main.c utils.o
	$(cc) $(flags) -o sierpinskit $^

runscratch: scratch.out
	./scratch.out temp.png

scratch.out: scratch.c utils.o
	$(cc) $(flags) -o scratch.out $^

utils.o: utils.c
	$(cc) $(flags) -c $^

clean:
	rm -f sierpinskit *.out *.o temp.png Sierpinski*.png test
