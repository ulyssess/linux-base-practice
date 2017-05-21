all: mutex spin semaphore cond

mutex: mutex.c
	gcc -o mutex mutex.c -lpthread

spin: spin.c
	gcc -o spin spin.c -lpthread

semaphore: semaphore.c
	gcc -o semaphore semaphore.c -lpthread

cond: cond.c
	gcc -o cond cond.c -lpthread

clean:
	rm -f mutex
	rm -f spin
	rm -f semaphore
	rm -f cond
