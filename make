#Makefile

loadScene.o: loadScene.cpp loadScene.h
	g++ -pedantic-erros -std=c++11 -c loadScene.cpp

main.o: main.cpp loadScene.h
	g++ -pedantic-erros -std=c++11 -c main.cpp

main: main.o loadScene.o
	g++ -pedantic-erros -std=c++11 main.o loadScene.o -o main
