#Makefile

FLAGS = -pedantic-errors -std=c++11

pugixml.o: pugixml/pugixml.cpp pugixml/pugixml.hpp pugixml/pugiconfig.hpp
	g++ $(FLAGS) -c $<

SaveLoad.o: saveLoad.cpp saveLoad.h player.h pugixml.o
	g++ $(FLAGS) -c $<

# game objects
player.o: player.cpp player.h SaveLoad.h pugixml.o
	g++ $(FLAGS) -c $<

monster.o: monster.cpp monster.h pugixml.o
	g++ $(FLAGS) -c $<

# scenes
sceneManager.o: sceneManager.cpp sceneManager.h
	g++ $(FLAGS) -c $<

titleScene.o: titleScene.cpp titleScene.h castleScene.h sceneManager.h
	g++ $(FLAGS) -c $<

castleScene.o: castleScene.cpp castleScene.h sceneManager.h player.h
	g++ $(FLAGS) -c $<

lobbyScene.o: lobbyScene.cpp lobbyScene.h sceneManager.h player.h pugixml.o
	g++ $(FLAGS) -c $<

# main program to run the game
main.o: main.cpp titleScene.h player.h sceneManager.h saveLoad.h lobbyScene.h
	g++ $(FLAGS) -c $<

main: main.o sceneManager.o titleScene.o castleScene.o monster.o player.o SaveLoad.o lobbyScene.o
	g++ $(FLAGS) $^ -o main
