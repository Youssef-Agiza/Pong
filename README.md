# Project 3

This project is submitted under the supervision of Dr. Michael Ibrahim.\
The project is submitted by:\
Youssef Agiza\
Kirolos Mikhail\
Kareem Talaat

# Compilation & Running

In this section, you shall find a guide to walk you through how to compile and run our project.

## Libraries Needed

- SFML (This library is used to create and control the GUI)

## Environment

This code was written compiled and tested on Linux's Ubuntu and has not been tested on any other environments, hence abnormal behavior is expected when running on a different OS. If the latter happens, please check the libraries used and look for your OS equivalent ones.

The code was also compiled and run on Visual Studio Code, hence a change in IDE might cause an issue.

## Running the Code

To compile and run the code, you need to use the MakeFile created to "make" the executable by running the following line in your command line at the location of the project

```
make
```

and then run the executable by running the following line of code into your terminal.

```
./pong
```

# Gameover

The game ends when either of the players scores 3 or more. On gameover, the two processes exit and the windows close. The win score can be changed in defs.h file.

# Shared Memory

We used a shared memory to share the data between all the working processes, for the ease of use. Instead of creating multiple pipes between all the processes and each other, we created one shared memory, that has a single structure, containing the position of the ball, the bats, the scores, delta time, and a flag to know when game is over. The parent process writes and updates the position of the ball, the scores of each player, a flag that determines when the game over and sends it to the children. The children detect keystrokes and adjust the position of the bats accordingly, by communicating their new positions between each other. This approach was preferred, as in the case of this game, date security is not as vital, hence shared memory wouldn’t create a security risk or compromise.
