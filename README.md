# CPPND: Capstone Snake Game Example

A modifed version of Snake Game example project udacity

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

## New features
1. Added a loop in main() so user will not have to run program again
2. Added a menu with 4 options:
     - 1. Start game
     - 2. View highest score and 5 recents game score
     - 3. Remove all the data from game (sometime not working)
     - 4. Quit game
3. User now can enter their name and save some current scores
4. Obstacles are 3 pixels on the game, snake will die if it hits the obstacle and appears only after eating the first food.
5. The food will relocate after every few seconds (6s - 10s)

## Project Rubric

1. README: all rubrics met
2. Compile and test: project compiles and runs without error
3. Loops, Functions, I/O:
  - The project demonstrates an understanding of C++ functions and control structures. -> through out the project workspace
  - The project reads data from a file and process the data, or the program writes data to a file. -> In constructor and destructor of class **Score**
  - The project accepts user input and processes the input. -> **Score::PrintMenu()** allows user input their name
  - The project uses data structures and immutable variables. -> **obstacle** in game.h is defined as vector and constant directory in main.cpp.
4. Object Oriented Programming
  - One or more classes are added to the project with appropriate access specifiers for class members. -> class **Score** met this rubric
  - Class constructors utilize member initialization lists -> Constructor of class **Score** met this rubric
  - Classes follow an appropriate inheritance hierarchy with virtual and override functions. -> class **Score** inherits the **Menu** class, and override the virtual function of base class
  - Classes abstract implementation details from their interfaces. -> Methods added are comprehensiveness
5. Memory management
  - The project makes use of references in function declarations. -> parameterized constructor and void AddNewScore() uses pass by ref
  - The project uses destructors appropriately. -> **Score** use destructor to write new things to file
  - The project uses smart pointers instead of raw pointers. -> class **Game** constructor uses unique_ptr to allocate heap for Score.
6. Concurrency
  - The project uses multithreading. -> Game::UpdateFood() runs in a new thread to update food every 6 - 10 sec
  - A mutex or lock is used in the project -> Mutex lock is used before PlaceFood() to avoid race condition.
## Tested device
 - Macos 11.7
 - Ubuntu 23.0
## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
