output: main.o flightticket.o flighthashtable.o mylist_impl.o
	g++ main.o flightticket.o flighthashtable.o mylist_impl.o -o output
flightticket.o: flightticket.h flightticket.cpp
	g++ -c flightticket.cpp
flighthashtable.o: flighthashtable.cpp flighthashtable.h 
	g++ -c flighthashtable.cpp
mylist_impl.o: mylist_impl.cpp mylist.cpp mylist.h
	g++ -c mylist_impl.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o output
