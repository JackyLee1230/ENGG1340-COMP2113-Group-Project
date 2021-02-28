#Makefile

loadScene.o: loadScene.cpp loadScene.h
	g++ -c loadScene.cpp

main.o: main.cpp loadScene.h
	g++ -c main.cpp

main: main.o loadScene.o
	g++ main.o loadScene.o -o main
