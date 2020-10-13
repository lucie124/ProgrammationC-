CC=g++
CFLAGS = -pthread -std=c++17
LDFLAGS = -I../googletest/googletest/include -L../gtest/lib -lgtest

tests: Nombre.o tests.o
	$(CC) $(CFLAGS) -o tests tests.o Nombre.o $(LDFLAGS)

Nombre.o: Nombre.cpp
	$(CC) $(CFLAGS) -c Nombre.cpp

tests.o: tests.cpp Nombre.h
	$(CC) $(CFLAGS) -c tests.cpp $(LDFLAGS)

clean:
	rm -rf *.o