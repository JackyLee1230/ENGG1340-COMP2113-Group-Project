#Makefile

FLAGS = -pedantic-errors -std=c++11

monster.o: monster.cpp monster.h pugixml/pugixml.cpp pugixml/pugixml.hpp
	g++ $(FLAGS) -c $<

sceneManager.o: sceneManager.cpp sceneManager.h
	g++ $(FLAGS) -c $<

titleScene.o: titleScene.cpp titleScene.h sceneManager.h monster.h
	g++ $(FLAGS) -c $<

main.o: main.cpp titleScene.h
	g++ $(FLAGS) -c $<

main: main.o sceneManager.o titleScene.o monster.o
	g++ $(FLAGS) $^ -o main
