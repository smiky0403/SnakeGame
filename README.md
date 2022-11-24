# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## Additional function made by student: Mingqi

1. Short period of time of loading game at beginning before game start
2. A command line for user to slect a game difficulty level 1 - 3, i.e. hard level will have more toxic food
3. Toxic food with white color added to game: it will kill snake once snake hit it
4. And boost food: it flashes in betwween green and red color  
5. Add toggling status to change status of boost:
    * green will reward a lot on score but speed up alot snake as well
    * red will reward a little on score, speed up a little as well
6. Add toxic food:
    * Amont of toxic food depends on the difficulty level from user input
    * toxic foods are imeplemented through smart pointers, added one by one to the game
7. User can hit B to add border to the outside, snake dies once hit; hit B again will cancel the border.
8. highest score will be record on the txt file, each time player reach new record, system will congrats to user.
9. User can hit ESC to pause the game, hit ESC again to resume the game. 
10. When user resume the game, snake remember its last direction before the pause and resume move on that direction


## Rubric Points completed by student: Mingqi

1. Loops, Functions, I/O:
The project code extensively use "for", "while loop" at different places (e.g. invalid user input of game difficulty level, adding toxic food and cycle the boost food). Functions mostly pass by reference to prevent copy paste on the backend of the system. Code clearly organized into functions and classes. All reusable functions implemented as methods inside their class.

Project accept user inputs at the beginning or during the game, these inputs include pause or resume the game and choose a difficulty level. 
User can also hit B to add or cancel border to the game when game is running, which will make game even tougher/
A command line for utser to slect a game difficulty level, i.e. hard level will have more toxic food; These keyboard related functions are completed mostly in the game.cpp and render.cpp

2. Object Oriented Programming - Classes use appropriate access specifiers for class members and their constructors utilize member initialization lists.

The project code added some new classes with attributes and methods to perform tasks and to hold the data: Some of class, structure, enum and funcions are written inside the files of toxic.h toxic.cpp menu.h menu.h, which have been used mostly by game or controller class.  The constructor of these new class are added and have been make sure to get initialized properly. 
All class commute internal or each other with their functionality once needed, also all class data members are specified with public or private. 

Under game.h game.cpp render.h render.cpp snake.h snake.cpp. many new methods and properties have been added to be able to perform the new capability lists aboved inside additional function.

3. Memory Management
  Again, The project pass references in function declarations have been used in most of the cases to save from copy-paste. Both references and pointers are used a lot espeically on the new game object of toxic food and boost.
  The toxic food class adds smart pointer: unique_ptr<std::vector<Coord>> _coords inside _toxic.h:  when called by game constrcutor to intilize and render, those toxic food spawn one by one to the game. Depend based on its vector size > 0 or not, system will prompt a warning to user not to eat toxic food with white color. We can clearly observe the instance been destrcuted automatically once I placed a printout inside its destructor, the magic of RAII.

4. Concurrency
   At the beginning of the game, system use a thread to wait for a short time to wait for game loading;
   The boost food creates a thread to loop the light status in between red and green. This thread waits for 1 - 3 seconds each light pahs and toggle its state to the othe light once the elapsed time has pass the threshold inside the thread.  



## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
