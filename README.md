# Unseen Journey Quest

A console-based 2D maze game where the player navigates a dark maze using proximity hints to find a hidden key and unlock the exit. Built with C++ and ncurses, demonstrating data structures including quadruply linked lists, stacks, and queues.

## Status

**Archived / Refactored**

## Features

- **Quadruply Linked List Maze** - Each cell connects in four directions for efficient navigation
- **Proximity Sensing** - Hints indicate if you're moving closer or farther from objectives
- **Undo System** - Stack-based move history allows backtracking
- **Dynamic Coins** - Respawning collectibles that grant extra undos and points
- **Bomb Obstacles** - Hidden dangers revealed based on proximity
- **Three Difficulty Levels** - Easy (10x10), Medium (15x15), Hard (20x20)

## Project Structure

```
unseen-journey-quest/
├── main.cpp           # Game source code
├── README.md          # Documentation
├── LICENSE            # MIT License
├── CONTRIBUTING.md    # Contribution guidelines
├── CHANGELOG.md       # Version history
├── .gitignore         # Git ignore rules
└── .editorconfig      # Editor configuration
```

## Installation

### Prerequisites

**Linux/macOS:**
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev  # Debian/Ubuntu
# or
brew install ncurses  # macOS
```

**Windows:**
Install [PDCurses](https://pdcurses.org/) via MSYS2:
```bash
pacman -S mingw-w64-x86_64-pdcurses
```

### Build

**Linux/macOS:**
```bash
g++ -o unseen_journey_quest main.cpp -lncurses
```

**Windows (MinGW with PDCurses):**
```bash
g++ -o unseen_journey_quest.exe main.cpp -lpdcurses
```

## Usage

```bash
./unseen_journey_quest
```

### Controls

| Key | Action |
|-----|--------|
| ↑ ↓ ← → | Move player |
| U | Undo last move |
| Q | Quit game |

### Gameplay

1. Select difficulty (1=Easy, 2=Medium, 3=Hard)
2. Navigate the maze using arrow keys
3. Use hints to locate the hidden key (K)
4. Collect coins (O) for extra undos and points
5. Avoid bombs (B) - they end the game
6. Find the door (D) after collecting the key to win

### Scoring

- Coins collected: +2 points each
- Remaining moves: +1 point each

## License

[MIT](LICENSE)

## Author

Muhammad Abdullah Ali
