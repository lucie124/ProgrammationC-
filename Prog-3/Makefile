CC=g++
CFLAGS = -pthread -std=c++17
LDFLAGS = -Igoogletest/googletest/include -Lgtest/lib -lgtest

tests: Expression.o TestExpression.o
	$(CC) $(CFLAGS) -o tests TestExpression.o Expression.o $(LDFLAGS)

Expression.o: Expression.cpp
	$(CC) $(CFLAGS) -c Expression.cpp

TestExpression.o: TestExpression.cpp Expression.hpp
	$(CC) $(CFLAGS) -c TestExpression.cpp $(LDFLAGS)

clean:
	rm -rf *.o