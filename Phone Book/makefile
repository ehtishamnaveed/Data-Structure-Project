
Main: Main.o Functions.o
	g++ Main.o Functions.o -o Main

Main.o: Main.cpp
	g++ -c Main.cpp

Functions.o: Functions.cpp Functions.h Structure.h
	g++ -c Functions.cpp

run:
	./Main

clean: 
	rm *.o Main