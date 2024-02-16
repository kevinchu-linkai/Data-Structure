output: main.o myvector-impl.o contactbst.o contact.o
	g++ main.o myvector-impl.o contactbst.o contact.o -o output
contactbst.o: contactbst.h contactbst.cpp
	g++ -c contactbst.cpp
myvector-impl.o: myvector.cpp myvector-impl.cpp myvector.h 
	g++ -c myvector-impl.cpp
contact.o: contact.cpp contact.h
	g++ -c contact.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o output