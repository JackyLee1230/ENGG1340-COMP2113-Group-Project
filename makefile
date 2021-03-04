#Makefile

sceneManager.o: sceneManager.cpp sceneManager.h
	g++ -pedantic-errors -std=c++11 -c sceneManager.cpp

main.o: main.cpp sceneManager.h
	g++ -pedantic-errors -std=c++11 -c main.cpp

main: main.o sceneManager.o
	g++ -pedantic-errors -std=c++11 main.o sceneManager.o -o main
