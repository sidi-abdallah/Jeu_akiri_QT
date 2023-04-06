# Akari Game

#

# File: READM.md

# Version: 0.1

# Authors: Mohamed El Mokhtar Sidi Abdallah <mohamed-el-mokhtar.sidi-abdallah@ecole.ensicaen.fr>
#	   Youssef Aghzere <youssef.aghzere@ecole.ensicaen.fr>
#
# Last update: 2023-04-06

## Introduction 
The Akari game is a Japanese logic puzzle that has gained popularity in recent years. The objective of the game is to place lamps on a grid in such a way that all squares are lit without any areas of darkness. You can try it by playing [here](https://www.puzzle-light-up.com/). 

As part of this project, we have implemented a version of the Akari game using the Qt/C++ framework. We have also attempted to follow an agile project approach while adhering to software engineering principles such as MVP and design patterns.

## Features of our project:

#### Responsiveness:

We have placed great emphasis on the responsiveness of our game. In fact, the game interface adapts to the user's screen, but we have chosen to define a minimum size for the interface below which it cannot be displayed. This choice was made because our game is currently only available on PCs.

#### Game Settings:

The player can adjust the game settings as desired. They can choose the grid size, difficulty level, and game time.

#### Player buttons:

To apply the changes made by the player, they need to click on one of the following buttons:

- The "Change Grid button": This button changes the current grid according to the player's choices (size and level) and resets the timer.

- The "Restart" button: This button allows the player to restart the game without changing the grid.

- The "Done" button: This button allows the player to know if they have won the game. A green message ("Bingoooo, you won") is displayed in case of success, and a red message ("Oooops try again") is displayed in case of failure.

- The "Undo" button: This button allows the player to undo the last lamp they placed. The user can remove all lamps by clicking on this button as many times as necessary.

#### Other features:

- Print Screen: The user can save a screenshot of the interface using the print action in the top left corner.

- Game Icon: We have added an icon for our game to attract the user and make them curious to play our game (a kind of advertisement).

- The timer turns red and signals an alert when the time is close to running out (for example, when there are 10 seconds left for a 1-minute game).

#### Keyboard shortcuts:

Undo: CTRL + Z

Restart: space

Print: CTRL + P

Close (Exit the game): CTRL + Q

Done: Return

