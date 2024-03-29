#Makefile

FLAGS = -pedantic-errors -std=c++11

pugixml.o: pugixml/pugixml.cpp pugixml/pugixml.hpp pugixml/pugiconfig.hpp
	g++ $(FLAGS) -c $<

saveLoad.o: saveLoad.cpp saveLoad.h player.h weapon.h pugixml.o
	g++ $(FLAGS) -c $<

# game objects
monster.o: monster.cpp monster.h player.h pugixml.o
	g++ $(FLAGS) -c $<

player.o: player.cpp player.h fruit.h saveLoad.h weapon.h pugixml.o
	g++ $(FLAGS) -c $<

weapon.o: weapon.cpp weapon.h pugixml.o player.h monster.h
	g++ $(FLAGS) -c $<

fruit.o: fruit.cpp fruit.h player.h pugixml.o
	g++ $(FLAGS) -c $<

skill.o: skill.cpp skill.h monster.o player.h monster.h pugixml.o
	g++ $(FLAGS) -c $<

# scenes
sceneManager.o: sceneManager.cpp sceneManager.h player.h monster.h
	g++ $(FLAGS) -c $<

titleScene.o: titleScene.cpp titleScene.h castleScene.h sceneManager.h combatScene.h combatResultScene.h
	g++ $(FLAGS) -c $<

infoScene.o: infoScene.cpp infoScene.h titleScene.h sceneManager.h
	g++ $(FLAGS) -c $<

castleScene.o: castleScene.cpp castleScene.h sceneManager.h player.h monsterEncounterScene.h
	g++ $(FLAGS) -c $<

lobbyScene.o: lobbyScene.cpp lobbyScene.h sceneManager.h monsterEncounterScene.h player.h
	g++ $(FLAGS) -c $<

monsterEncounterScene.o: monsterEncounterScene.cpp monsterEncounterScene.h sceneManager.h player.h
	g++ $(FLAGS) -c $<

combatScene.o: combatScene.cpp combatScene.h skill.h player.h monster.h
	g++ $(FLAGS) -c $<

combatResultScene.o: combatResultScene.cpp combatResultScene.h player.h monster.h
	g++ $(FLAGS) -c $<

storyScene.o: storyScene.cpp storyScene.h player.h monster.h
	g++ $(FLAGS) -c $<

# main program to run the game
main.o: main.cpp
	g++ $(FLAGS) -c $<

main: main.o sceneManager.o titleScene.o infoScene.o castleScene.o lobbyScene.o monsterEncounterScene.o combatScene.o combatResultScene.o storyScene.o monster.o player.o weapon.o skill.o fruit.o saveLoad.o
	g++ $(FLAGS) $^ -o main

clean:
	rm -f main *.o

.PHONY: main clean
