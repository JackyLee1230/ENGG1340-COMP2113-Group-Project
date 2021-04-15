# ENGG1340-COMP2113-Group-Project

<pre>
Game Name: DreadPoint

Group No.:      103

Group Member:   Lee Chi Ho    (u3578552)
                Cheng Pak Yim (u3578494)

Topic: Turn-based Combat Text-based RPG

Link: https://github.com/u3578552/ENGG1340-COMP2113-Group-Project
</pre>

## **Game Rule:**  
As a Monster Slayer, you have decided to tackle the castle filled with Ancient Monsters.  
There are a total of ***6 monsters*** in the game. You will first be greeted by a Gate Keeper which upon defeat  
will grant you the access to the main Castle. To discover the secret hidden within the castle, you will have to    defeat all of the monster and the final boss of the game.  
In each battle, you will be given a choice of using your weapon(s) to attack the monster or consume a healing item to regenerate your health.   
In this turn-based combat, the player and the monster will take turn attacking or defending.  
Each weapon in the game have different damage value and some with *"special ability"*.  
Monster will also equip themselves with shield which can br broken with enough damage or using weapon that deals the opposite damage type.  
If you have defeated the monster, you will gain access to the next monster in the castle and be transfered back to the main lobby.  
If you could not defeat the monster, don't feat, you will be able to retry the fight indefinitely.  
To win the game, you will have to ***defeat all 6 monsters*** and discover the underlying secrets and treasures of the Castle.

> ### The game is best run on **_X2Go / SSH_** using command prompt / terminal <br> in **Full Screen Mode**
> ### To showcase the arts and elements in the game

>Please use makefile to ensure that the game is up to date ,type `make main`. <br/> To execute the game using X2Go/SSH, type `./main` in the game directory.

>Please note that we have made use of **[PugiXML](https://github.com/zeux/pugixml)**, which is around 14500 lines of code.
> The contribution graph may be affected by the addition of **[PugiXML](https://github.com/zeux/pugixml)**.

> ## Features of the Proposed Game (and the use of coding elements):
>1. Turn-based combat RPG
>  - Random Game Sets and Events
>2. Graphics using ASCII characters
>  - File IO
>  - Program in Multiple Files
>  - Dynamic Memory Management
>3. Randomly Generated Enemies, Health, Weapons
>  - Random Generation
>  - Program in Multifile files
>  - Dynamic Memory Management
>>     Memory will be allocated in real time to accompany random events such as Monster Attacks  and Dodge Probability and be saved into the memory.
>4. Save/Load Game Status
>  - File IO
>  - Data Structures for Storing Game Status
>>     Data such as player health, floor, level, weapon
>>     will all be stored using different data structures such as vectors, arrays.
>5. Random Weapons Set
>  - Random
