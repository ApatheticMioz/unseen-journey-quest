
# The Unseen Journey Quest

### FAST NUCES CS-2001: Data Structures (Fall 2024) - Assignment #02

---

## Introduction

Welcome to *The Unseen Journey Quest*, a console-based 2D maze game where the player is trapped in a dark maze. The player can only sense their surroundings and must find a hidden key to unlock the exit. The challenge lies in navigating the maze blind, using hints to determine whether they are moving closer or further from the key, and surviving with limited moves and an undo feature.

This project demonstrates the use of data structures such as multidimensional linked lists and stacks, alongside game logic and pathfinding techniques.

---

## Key Features

- **Maze Representation:** (TODO)
- **Player Movement:** (TODO)
- **Sense Ability (Hints):** (TODO)
- **Random Placement:** (TODO)
- **Difficulty Levels:** (TODO)
- **Coins and Bombs:** (TODO)
- **Undo Feature:** (TODO)
- **Score Calculation:** (TODO)

---

## Game Objectives

1. **Find the Key**: Use your sensing ability to locate the hidden key in the maze.
2. **Unlock the Exit**: Once you have the key, find and unlock the exit door to escape the maze.
3. **Collect Coins**: Gather coins to earn additional undo moves and boost your score.
4. **Avoid the Bombs**: Avoid stepping on bombs, which end the game instantly.
5. **Complete with Remaining Moves**: Unused moves will add to your final score.

---

## How to Run the Game

### Requirements

#### For Windows:
- **PDCurses Library**  
  The game uses the **PDCurses** library to handle the display of the maze on the console. Ensure PDCurses is installed.
  
  **Setup for MinGW with MSYS2:**
  - Install MSYS2 and update the packages:
    ```bash
    pacman -Syu
    ```
  - Install GCC and make tools:
    ```bash
    pacman -S mingw-w64-x86_64-toolchain base-devel
    ```
    
  **Building the library**

  - Compile PDCurses for MinGW:
    ```bash
    cd PDCurses/wincon
    mingw32-make -f Makefile
    ```
    
  **Setup for Clion/IDE with CmakeLists.txt**
  
  - Set up your CMakeLists.txt to link PDCurses with your project:
    ```cmake
    find_library(CURSES_LIBRARIES pdcurses PATHS /path/to/PDCurses)
    include_directories(/path/to/PDCurses)
    target_link_libraries(YourProjectName ${CURSES_LIBRARIES})
    ```

#### For Linux/Mac:
- **Ncurses Library**  
  For Linux/Mac systems, use the **Ncurses** library:
  ```bash
  sudo apt-get install libncurses5-dev libncursesw5-dev
  ```

  **Compile and Run:**
  ```bash
  g++ -o maze_game game.cpp -lncurses
  ./maze_game
  ```

---

## How to Play

- Use the arrow keys to move in the maze (up, down, left, right).
- Sense your proximity to the hidden key using the hints.
- Collect coins to gain additional undo moves.
- Avoid bombs and reach the exit with the key in the fewest moves possible.
- Use the undo feature wisely to backtrack when necessary.

---

## Installation

Clone this repository and follow the instructions for your platform:

```bash
git clone https://github.com/yourusername/unseen-journey-quest.git
cd unseen-journey-quest
```

