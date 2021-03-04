#Makefile

monster.o: monster.cpp monster.h
	g++ -pedantic-errors -std=c++11 -c $<

sceneManager.o: sceneManager.cpp sceneManager.h
	g++ -pedantic-errors -std=c++11 -c $<

titleScene.o: titleScene.cpp titleScene.h sceneManager.h monster.h
	g++ -pedantic-errors -std=c++11 -c $<

main.o: main.cpp titleScene.h
	g++ -pedantic-errors -std=c++11 -c $<

main: main.o sceneManager.o titleScene.o monster.o
	g++ -pedantic-errors -std=c++11 $^ -o main
