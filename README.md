# EndlessRunnerAssigmentUE5

How to play:
Press spacebar to go up.
Avoid Rockects which are indicated by red dots.

Whole game is fully made with C++ classes.

- Player Class:
  Standard implementation of UE5 new input system nothing fancy. Keeps track of lives.
  
- DamageableInterface:
  Interface for anything that might get killed by obstacles (for now only player).

- EndlessRunnerGameModeBase Class:
  Since it is a GameMode class it can be accessed from any object in the level acting as singleton. Takes care of keeping track of the time, score and whether the game is paused aditionally does values can be Get/Set.

- Level Classes:
  - ScrollingActor Class (should be renamed):
    Manager class for level. Spawns Fragments of the level, assigns speed and blueprint instance to them.
  - LevelFragment Class:
    Level fragments are building blocks for the level they have predetermined hiarchy structure in C++ and are made for quick creation of new blueprint instance. They move on their own and insted of destroing itself is moved to the end of the line of the level resembling object pulling when getting out of game scope (more on that in Cleaner Class).

- Rocket Classes:
  - RocketManager Class:
    Manager class for Rockets. Responsible for spawning projectiles, setting their speed, blueprint instance, etc. Calculates values using equations based on time from the GameMode Class: Spawn interval = 0.995^InGameTime, Rocket Speed = 2 * Log(3, InGameTime+15).
  - Rocket Class:
    Simple object that moves towards the player with predetrmined parameters. On collision checks for DamageableInterface and runs TakeDamge function.
   
- Cleaner Class:
  - It is a big trigger box that is out side of the game view. Takes care of objects that need to be taken care of when they get out of view checking for CleanAbleInterface and running Clean function. Usage of an Interface for this allows for quick and easy check for if the object should be cleaned additionaly alows for different implementation of Clean function deppending on an object.

- CleanAbleInterface Class:
  - Is a Interface Class that all objects that should be delt with by the Cleaner Class inherit from.
