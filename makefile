#Makefile

FLAGS = -pedantic-errors -std=c++11

pugixml.o: pugixml/pugixml.cpp pugixml/pugixml.hpp pugixml/pugiconfig.hpp
	g++ $(FLAGS) -c $<

SaveLoad.o: saveLoad.cpp saveLoad.h player.h pugixml.o
	g++ $(FLAGS) -c $<

player.o: player.cpp player.h SaveLoad.h pugixml.o
	g++ $(FLAGS) -c $<

monster.o: monster.cpp monster.h pugixml.o
	g++ $(FLAGS) -c $<

sceneManager.o: sceneManager.cpp sceneManager.h
	g++ $(FLAGS) -c $<

titleScene.o: titleScene.cpp titleScene.h sceneManager.h monster.h
	g++ $(FLAGS) -c $<

main.o: main.cpp titleScene.h player.h sceneManager.h saveLoad.h
	g++ $(FLAGS) -c $<

main: main.o sceneManager.o titleScene.o monster.o player.o SaveLoad.o
	g++ $(FLAGS) $^ -o main
