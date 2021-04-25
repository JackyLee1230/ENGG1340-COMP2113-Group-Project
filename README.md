# ENGG1340-COMP2113-Group-Project

<pre>
Game Name: DreadPoint

Group No.:      103

Group Member:   Lee Chi Ho    (u3578552)
                Cheng Pak Yim (u3578494)

Topic: Turn-based Combat Text-based RPG

Game description: DreadPoint is a turn-based RPG game that is focusing on the fun and strategic combat with stories being told after each battle.
In DreadPoint, you, as a Monster Slayer, will have to fight the monsters in a historic Castle to uncover the hidden stories and histories, using the weapons and healing items you collect on the way.

Link to repo: https://github.com/u3578552/ENGG1340-COMP2113-Group-Project
Link to video: https://youtu.be/mN2M2c3YBu8
</pre>

## **Problem Statement**
When deciding on the project topic, we decided to challenge ourselves with designing a game that includes both stories and intriguing gameplay. To do so, we have finalized the idea of creating a turn-based combat RPG game.<br>
The main concept of our game is to make a game where the player has a wide-range of freedom in combat and settled on the idea of turn-based combat with various weapon choices and items and have great replay value.

## **Game Rule**  
As a Monster Slayer, you have decided to tackle the castle filled with Ancient Monsters. There are a total of ***6 monsters*** in the game.

You will first be greeted by a Gate Keeper which upon defeat, will grant you access to the Main Castle.

In order to discover the secret hidden within the castle, you will have to defeat all of the monsters and the final boss of the game.

In each battle, you will be given a choice of using your weapon(s) to attack the monster or consume a healing item to regenerate your health. In this turn-based combat game, the player and the monster will take turns attacking or defending.

Each weapon in the game has different damage values and some with*"special ability"*.

Monster will also equip themselves with a shield which can be destroyed with enough damage or using a weapon that deals the opposite damage type.

If you have defeated the monster, you will gain access to the next monster in the castle and be transfered back to the main lobby.

If you cannot defeat the monster, don't fear, you will be able to retry the fight indefinitely.

To win the game, you will have to ***defeat all 6 monsters*** and discover the underlying secrets and treasures of the Castle.

**Reminder: The game is best run on SSH using command prompt / terminal in Full Screen Mode to showcase the arts and elements in the game**

## Running the game (Quick start)
1. Type the following in the terminal to clone this repo

`git clone https://github.com/u3578552/ENGG1340-COMP2113-Group-Project.git`

2. Go in to our project directory

`cd ENGG1340-COMP2113-Group-Project`

3. Type the following to compile our game. It takes around a minute.

`make main`

4. Type the following to run the game

`./main`

The procedure was tested in server academy@11


> Please note that we have made use of **[PugiXML](https://github.com/zeux/pugixml)**, which is around 14500 lines of code, uploaded by Cheng Pak Yim (3035784942)
> The contribution graph may be affected by the addition of **[PugiXML](https://github.com/zeux/pugixml)**.
> The number of lines added by Cheng Pak Yim (u3578494) should be 4999 instead of 19499, while there is no such issue in Lee Chi Ho's (u3578552) contribution graph.
> The use of PugiXML facilitates our implementation of Save File and Save Loading
</br>


## Features of the Proposed Game (and the use of coding elements)

#### 1. Turn-based combat
* Monsters moves are generated randomly from a pre-load move set and stored in a vector array
	 * Generation of random game sets or events
	 * Data structures for storing game status
	 * Dynamic memory management (vectors)
* Players have multiple weapons and fruits loaded from its savefile and stored in vectors array to form an inventory system. Different weapons and fruits can be chosen to attack the monsters and heal himself
	 * Data structures for storing game status
	 * Dynamic memory management (vectors)
* Random critical attack will be dealed during player's round, with varying probability depending on each weapon
	 * Data structures for storing game status
	 * Generation of random game sets or events
* Monsters will dodge attacks randomly depending on a hidden dodge probability stored in monster objects.
	 * Data structures for storing game status
	 * Generation of random game sets or events
* Random amount and types of fruit will be dropped after each combat
	 * Generation of random game sets or events
	 * Data structures for storing game status
* Stories were loaded from txt files illustrating the background and secrets of the castle after winning each combat
	* FIle input/output

#### 2.  Stunning graphics using ASCII characters
* Every monster is equipped with a stunning ascii art which will be showed while encountering the monster
	 * File input/ output
* A stunning opening scene and the main lobby of the castle are showed while gameplay, enhancing the immersive gameplay
	 * File input/ ouput

#### 3. Save load system (supported by pugiXML)
* The player's gameplay will be saved automatically, which will be writen into an xml file, after defeating a monster. Player can continue his adventure when pressing "continue" in the title screen to load the existing savefile. The game will prompt the user to create a new game if no savefile is detected.
	 * Data structures for storing game status
	 * File input/output
* The monsters' stats, weapons' stats, fruits' stats and monsters' moves are all typed in seperated xml files, which will be read and loaded into game objects during gameplay.
	 * Data structures for storing game status
	 * File input/output

#### 4. Object-orientated programming
* Every game objects (monster, player, weapon, fruit, monsters' move) are coded in objects for storing game status
	 * Data structures for storing game status
	 * Program codes in multiple files
	 * Proper indentation and naming styles
	 * In-code documentation
* Every scene (the title scene, castle scene, lobby scene, monster encountering scene, combat scene, combat end scene, story scene, info scene) are coded in seperate files to control the flow of the gameplay
	 * Program codes in multiple files
	 * Proper indentation and naming styles
	 * In-code documentation
* The player and monster object pointers will be passed across different scene, and will be deleted when the program terminates.
	 * Dynamic memory management

## Non-standard C/C++ libraries used
[PugiXML](https://github.com/zeux/pugixml)
* Save load system (feature 3)
