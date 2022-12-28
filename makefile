output: main.o flightticket.o flighthashtable.o mylist.o
	g++ main.o flightticket.o flighthashtable.o mylist.o -o output

flighthashtable.o: flighthashtable.cpp flighthashtable.h flightticket.cpp flightticket.h mylist.h mylist.cpp
	g++ -c flighthashtable.cpp flightticket.cpp

mylist.o: mylist.h mylist.cpp flighthashtable.h flighthashtable.cpp
	g++ -c mylist.cpp

flightticket.o: flightticket.cpp flightticket.h
	g++ -c flightticket.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output
