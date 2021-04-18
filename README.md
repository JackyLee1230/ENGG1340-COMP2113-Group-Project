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
will grant you access to the Main Castle. To discover the secret hidden within the castle, you will have to defeat all of the monsters and the final boss of the game.  
In each battle, you will be given a choice of using your weapon(s) to attack the monster or consume a healing item to regenerate your health.   
In this turn-based combat game, the player and the monster will take turns attacking or defending.  
Each weapon in the game has different damage values and some with *"special ability"*.  
Monster will also equip themselves with a shield which can be destroyed with enough damage or using a weapon that deals the opposite damage type.  
If you have defeated the monster, you will gain access to the next monster in the castle and be transfered back to the main lobby.  
If you cannot defeat the monster, don't fear, you will be able to retry the fight indefinitely.  
To win the game, you will have to ***defeat all 6 monsters*** and discover the underlying secrets and treasures of the Castle.


> ### The game is best run on **_SSH_** using command prompt / terminal in **Full Screen Mode**
> ### To showcase the arts and elements in the game

>Please use makefile to ensure that the game is up to date ,type ***`make main`***. <br/> To execute the game using SSH, type ***`./main`*** in the main game directory.

>Please note that we have made use of **[PugiXML](https://github.com/zeux/pugixml)**, which is around 14500 lines of code.  
> The contribution graph may be affected by the addition of **[PugiXML](https://github.com/zeux/pugixml)**.  
> The use of PugiXML facilitates our implementation of Save File and Save Loading

> ## Features of the Proposed Game (and the use of coding elements):
>1. Turn-based combat RPG
>  - Random Game Sets and Events based on player actions
>2. Graphics using ASCII characters
>  - File IO
>  - Program in Multiple Files
>  - Dynamic Memory Management
>3. Random Enemy Item Drops, Skills, Actions
>  - Random Generation of item drops, skills
>  - Program in Multifile files
>  - Dynamic Memory Management
>>     Memory will be allocated in real time to accompany random events such as Monster Attacks  and Dodge Probability and be saved into the memory.
>4. Save/Load Game Status
>  - File IO
>  - Data Structures for Storing Game Status
>>     Data such as player health, floor, level, weapon
>>     will all be stored using different data structures such as vectors, arrays.
>5. Weapons Randomness
>  - Random Critical for Different Weapons
