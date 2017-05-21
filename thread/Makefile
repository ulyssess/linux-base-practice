all: mutex sync semaphore

mutex: mutex.c
	gcc -o mutex mutex.c -lpthread

sync: sync.c
	gcc -o sync sync.c -lpthread

semaphore: semaphore.c
	gcc -o semaphore semaphore.c -lpthread

clean:
	rm -f mutex
	rm -f sync
	rm -f semaphore
