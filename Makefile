CFLAGS=$(shell pkgconf -cflags gtk4)
LDFLAGS=$(shell pkgconf -libs  gtk4)
semaphore: main.cpp
	g++ -g -O0 -o semaphore main.cpp $(CFLAGS) $(LDFLAGS)
clean:
	rm semaphore
