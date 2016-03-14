CC = cc
COPS =
LINT = lint
LOPS = -x -u

all: ring ring1 ring2 ring3 ring4 ring5 ringtopology exercise0702test exercise0703test exercise0704test example0705test

ring: ring.c
	$(CC) $(COPS) -o ring ring.c

ring1: ring1.c
	$(CC) $(COPS) -o ring1 ring1.c
	
ring2: ring2.c
	$(CC) $(COPS) -o ring2 ring2.c

ring3: ring3.c
	$(CC) $(COPS) -o ring3 ring3.c
	
ring4: ring4.c
	$(CC) $(COPS) -o ring4 ring4.c
	
ring5: ring5.c
	$(CC) $(COPS) -o ring5 ring5.c
	
ringtopology: ringtopology.c
	$(CC) $(COPS) -o ringtopology ringtopology.c

exercise0702test: exercise0702test.c exercise0702.c
	$(CC) $(COPS) -o exercise0702test exercise0702test.c

exercise0703test: exercise0703test.c exercise0703.c
	$(CC) $(COPS) -o exercise0703test exercise0703test.c

exercise0704test: exercise0704test.c exercise0704.c
	$(CC) $(COPS) -o exercise0704test exercise0704test.c

example0705test: example0705test.c exercise0702.c
	$(CC) $(COPS) -o example0705test example0705test.c

lintall: lintring lintexercise0702 lintexercise0703 lintexercise0704 lintexample0705

lintring:
	$(LINT) $(LOPS) ring.c

lintexercise0702:
	$(LINT) $(LOPS) exercise0702test.c

lintexercise0703:
	$(LINT) $(LOPS) exercise0703test.c

lintexercise0704:
	$(LINT) $(LOPS) exercise0704test.c

lintexample0705:
	$(LINT) $(LOPS) example0705test.c

clean:
	rm -f *.o core ring ring1 ring2 ring3 exercise0702test exercise0703test exercise0704test example0705test
