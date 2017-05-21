all: mutex sync

mutex: mutex.c
	gcc -o mutex mutex.c -lpthread

sync: sync.c
	gcc -o sync sync.c -lpthread

clean:
	rm -f mutex
	rm -f sync
