cc=gcc
flags=-Wall `pkg-config --cflags --libs cairo`
testdir=./tests
aceunit=$(testdir)/AceUnit-0.12.0.jar


.PHONY: runscratch clean

sierpinskit: main.c utils.o
	$(cc) $(flags) -o sierpinskit $^

runscratch: scratch.out
	./scratch.out temp.png

test: $(testdir)/test.c utils.o
	$(cc) $(flags) -o test $^

scratch.out: scratch.c utils.o
	$(cc) $(flags) -o scratch.out $^

utils.o: utils.c
	$(cc) $(flags) -c $^

clean:
	rm -f sierpinskit *.out *.o temp.png Sierpinski*.png test\
		Sierpinski*.svg
