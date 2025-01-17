OBJS = cards.o cards_test.o dealer.o dealer_test.o user.o main.o
CXXFLAGS = -std=c++11 -Wall -pedantic -g

main:	$(OBJS)
		g++ $(OBJS) -o main

clean:
		rm -f *.o
