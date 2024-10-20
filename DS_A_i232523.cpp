// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppUseAuto
// ReSharper disable CppLocalVariableMayBeConst

// Muhammad Abdullah Ali
// i23-2523
// Section A
// Data Structures Assignment 2

#include <curses.h>
#include <iostream>

using namespace std;

int abs(int x) {
    return (x < 0) ? -x : x;  // If x is negative, return -x; otherwise, return x
}

class Node {
public:
    int data;
    Node* next;

    Node(const int d) {
        this->data = d;
        this->next = nullptr;
    }
};

class Stack {
    Node* head;

public:
    Stack() {
        head = nullptr;
    }

    ~Stack() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void push(const int x) {
        Node* temp = new Node(x);
        temp->next = head;
        head = temp;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    int peek() const {
        if (!isEmpty()) {
            return head->data;
        }

        return -1;
    }
};

class NodeQueue {
public:
    int x;
    int y;
    char ch;
    NodeQueue* next;

    NodeQueue(const int x, const int y, const char ch) {
        this->x = x;
        this->y = y;
        this->ch = ch;
        this->next = nullptr;
    }
};

class Queue {
    NodeQueue* front;
    NodeQueue* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    ~Queue() {
        while (front != nullptr) {
            NodeQueue* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(const int x, const int y, const char ch) {
        NodeQueue* temp = new NodeQueue(x, y, ch);

        if (isEmpty()) {
            front = temp;
            rear = temp;
            return;
        }

        rear->next = temp;
        rear = temp;
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }

        NodeQueue* temp = front;
        front = front->next;

        if (isEmpty()) {
            rear = nullptr;
        }

        delete temp;
    }

    int getFrontX() const {
        if (isEmpty()) {
            return -1;
        }

        return front->x;
    }

    int getFrontY() const {
        if (isEmpty()) {
            return -1;
        }

        return front->y;
    }

    char getFrontCh() const {
        if (isEmpty()) {
            return -1;
        }

        return front->ch;
    }

    int getRearX() const {
        if (isEmpty()) {
            return -1;
        }

        return rear->x;
    }

    int getRearY() const {
        if (isEmpty()) {
            return -1;
        }

        return rear->y;
    }

    char getRearCh() const {
        if (isEmpty()) {
            return -1;
        }

        return rear->ch;
    }
};

class GridNode {
public:
    char value;
    GridNode* right;
    GridNode* left;
    GridNode* down;
    GridNode* up;

    GridNode(const char v) {
        this->value = v;
        right = nullptr;
        left = nullptr;
        down = nullptr;
        up = nullptr;
    }

    GridNode(const GridNode& other) {
        value = other.value;
        right = nullptr;
        left = nullptr;
        down = nullptr;
        up = nullptr;
    }
};

class Grid {
    GridNode* head;
    int rows;
    int cols;
    static int coinThresh;
    static int bombThresh;
    int xDoor, yDoor;
    int xKey, yKey;

public:
    Grid() {
        this->rows = 0;
        this->cols = 0;
        this->head = nullptr;
        xDoor = yDoor = xKey = yKey = -1;
    }

    Grid& operator=(const Grid& other) {
        if (this == &other) {
            return *this;
        }

        this->~Grid();

        this->rows = other.rows;
        this->cols = other.cols;
        this->xDoor = other.xDoor;
        this->yDoor = other.yDoor;
        this->xKey = other.xKey;
        this->yKey = other.yKey;

        GridNode* otherRow = other.head;
        GridNode* previousRow = nullptr;

        while (otherRow != nullptr) {
            GridNode* otherCell = otherRow;
            GridNode* newCell = nullptr;
            GridNode* previousCell = nullptr;
            GridNode* newRowHead = nullptr;

            while (otherCell != nullptr) {

                newCell = new GridNode(otherCell->value);

                if (this->head == nullptr) {
                    this->head = newCell;
                }

                if (newRowHead == nullptr) {
                    newRowHead = newCell;
                }

                if (previousCell != nullptr) {
                    previousCell->right = newCell;
                    newCell->left = previousCell;
                }

                if (previousRow != nullptr) {
                    GridNode* above = previousRow;

                    while (above->right != nullptr && otherCell != otherRow) {
                        above = above->right;
                    }
                    above->down = newCell;
                    newCell->up = above;
                }

                previousCell = newCell;
                otherCell = otherCell->right;
            }

            previousRow = newRowHead;
            otherRow = otherRow->down;
        }

        return *this;
    }

    ~Grid() {
        GridNode* currentRow = head;
        while (currentRow != nullptr) {
            GridNode* currentCell = currentRow;

            while (currentCell != nullptr) {
                GridNode* temp = currentCell;
                currentCell = currentCell->right;
                delete temp;
            }

            currentRow = currentRow->down;
        }

        head = nullptr;
    }

    GridNode* getHead() const {
        return head;
    }

    static int getBombThresh(const int rows, const int cols) {
        return static_cast<int>(rows * cols * 0.06);
    }

    static int getCoinThresh(const int rows, const int cols) {
        return static_cast<int>(rows * cols * 0.09);
    }

    static void decCoinThresh() {
        if (Grid::coinThresh >= 1)
            Grid::coinThresh--;
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    GridNode* getNode(const int targetRow, const int targetCol) {
        GridNode* currentRow = head;
        int row = 0;

        while (currentRow != nullptr) {
            GridNode* currentCell = currentRow;
            int col = 0;

            while (currentCell != nullptr) {
                if (row == targetRow && col == targetCol) {
                    return currentCell;
                }

                currentCell = currentCell->right;
                col++;
            }

            currentRow = currentRow->down;
            row++;
        }

        return nullptr;
    }

    GridNode* getKey() {
        GridNode* currentRow = head;
        int row = 0;

        while (currentRow != nullptr) {
            GridNode* currentCell = currentRow;
            int col = 0;

            while (currentCell != nullptr) {
                if (row == xKey && col == yKey) {
                    return currentCell;
                }

                currentCell = currentCell->right;
                col++;
            }

            currentRow = currentRow->down;
            row++;
        }

        return nullptr;
    }

    GridNode* getDoor() {
        GridNode* currentRow = head;
        int row = 0;

        while (currentRow != nullptr) {
            GridNode* currentCell = currentRow;
            int col = 0;

            while (currentCell != nullptr) {
                if (row == xDoor && col == yDoor) {
                    return currentCell;
                }

                currentCell = currentCell->right;
                col++;
            }

            currentRow = currentRow->down;
            row++;
        }

        return nullptr;
    }

    void initGrid(const int difficulty) {
        srand(time(nullptr));

        switch (difficulty) {
            case 1:
                rows = cols = 10;
                break;
            case 2:
                rows = cols = 15;
                break;
            case 3:
                rows = cols = 20;
                break;
            default:
                exit(-1);
        }

        coinThresh = getCoinThresh(rows, cols);
        bombThresh = getBombThresh(rows, cols);

        GridNode* previousRow = nullptr;
        GridNode* currentRow = nullptr;
        GridNode* previousCell = nullptr;

        xDoor = rand() % 12 + 1, yDoor = rand() % 12 + 1, xKey = rand() % 12 + 1, yKey = rand() % 12 + 1;
        while ((xDoor == 1 && yDoor == 1) || (xKey == 1 && yKey == 1)) {
            xDoor = rand() % 12 + 1;
            yDoor = rand() % 12 + 1;
            xKey = rand() % 12 + 1;
            yKey = rand() % 12 + 1;
        }

        int bombCount = 0, coinCount = 0;

        for (int i = 0; i < rows; i++) {
            previousCell = nullptr;
            for (int j = 0; j < cols; j++) {

                char cell;

                if (i == 0 || j == 0 || j == cols - 1 || i == rows - 1) {
                    cell = '#';
                } else {
                    int randomValue = rand() % 100 + 1;

                    if (i == xDoor && j == yDoor) {
                        cell = 'D';
                    } else if (i == xKey && j == yKey) {
                        cell = 'K';
                    } else if ((randomValue >= 30 && randomValue < 40 && bombCount < Grid::bombThresh) && (i != 2 && j != 1) && (i != 1 && j != 2)) {
                        cell = 'B';
                        bombCount++;
                    } else if (randomValue >= 85 && randomValue < 100 && coinCount < Grid::coinThresh) {
                        cell = 'O';
                        coinCount++;
                    } else {
                        cell = '.';
                    }
                }

                GridNode* newCell = new GridNode(cell);

                if (i == 0 && j == 0) {
                    head = newCell;
                }

                if (previousCell) {
                    previousCell->right = newCell;
                    newCell->left = previousCell;
                }
                previousCell = newCell;

                if (previousRow) {
                    GridNode* above = previousRow;

                    for (int k = 0; k < j; k++) {
                        above = above->right;
                    }
                    above->down = newCell;
                    newCell->up = above;
                }

                if (j == 0) {
                    currentRow = newCell;
                }
            }

            previousRow = currentRow;
        }
    }

    int distance(const GridNode* player, const GridNode* node) {
        int startX = 0, startY = 0;
        int targetX = 0, targetY = 0;

        for (int i = 1; i < 15; i++) {
            for (int j = 1; j < 15; j++) {
                if (player == getNode(i, j)) {
                    startX = i;
                    startY = j;
                }

                if (node == getNode(i, j)) {
                    targetX = i;
                    targetY = j;
                }
            }
        }

        return abs(targetX - startX) + abs(targetY - startY);
    }

    void displayGrid(GridNode* player) {
        GridNode* currentRow = head;
        int row = 6;

        while (currentRow != nullptr) {
            GridNode* currentCell = currentRow;
            int col = 14;

            while (currentCell != nullptr) {
                move(row, col);

                switch (currentCell->value) {
                    case '#': {
                        attron(COLOR_PAIR(1));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(1));
                        break;
                    }
                    case 'P': {
                        attron(COLOR_PAIR(3));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    case 'K': {
                        attron(COLOR_PAIR(5));
                        addch('.'); // Key
                        attroff(COLOR_PAIR(5));
                        break;
                    }
                    case 'O': {
                        attron(COLOR_PAIR(4));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(4));
                        break;
                    }
                    case 'B': {
                        int distanceVal = distance(player, currentCell);

                        if (distanceVal > static_cast<int>(rows * 0.3)) {
                            addch('.');
                        } else {
                            attron(COLOR_PAIR(6));
                            addch('B');
                            attroff(COLOR_PAIR(6));
                        }
                        break;
                    }
                    case 'D': {
                        attron(COLOR_PAIR(7));
                        addch('.'); // Door
                        attroff(COLOR_PAIR(7));
                        break;
                    }
                    default: {
                        addch(currentCell->value);
                    }
                }

                currentCell = currentCell->right;
                col += 2;
            }

            currentRow = currentRow->down;
            row++;
        }
    }
};

int Grid::coinThresh = 0;
int Grid::bombThresh = 0;

class Game {
    Grid gameGrid;
    Grid copyGame;
    WINDOW* win;
    GridNode* player;
    GridNode* key;
    GridNode* door;
    Stack movesMade;
    Queue itemsCollected;
    bool running, gameOver, keyFound, gameWon;
    int winHeight, winWidth;
    int score, movesRemaining, undoes;

public:
    Game(const int rows, const int cols, int difficulty) {
        winHeight = 100;
        winWidth = 50;
        win = newwin(winHeight, winWidth, 0, 0);

        displayMenu(win, difficulty);

        gameGrid.initGrid(difficulty);
        copyGame = gameGrid;
        wrefresh(win);
        player = gameGrid.getHead()->right->down;
        player->value = 'P';
        key = gameGrid.getKey();
        door = gameGrid.getDoor();
        running = true;
        gameOver = false;
        gameWon = false;
        score = 0;
        movesRemaining = distance(player, key, door, 0) + distance(player, key, door, 2);
        undoes = 0;
        keyFound = false;
    }

    ~Game() {
        delwin(win);
        endwin();
    }

    void displayMenu(WINDOW* win, int &difficulty) {
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "%s", "Choose your difficulty.");
        mvprintw(1, 0, "%s", "1 - Easy.");
        mvprintw(2, 0, "%s", "2 - Medium.");
        mvprintw(3, 0, "%s", "3 - Hard.");
        mvprintw(4, 0, "%s", "Anything Else - Crash.");
        attroff(COLOR_PAIR(1));
        int choice = getch();

        switch (choice) {
            case '1':
                difficulty = 1;
                break;
            case '2':
                difficulty = 2;
                break;
            case '3':
                difficulty = 3;
                break;
            default:
                difficulty = -1;
            beep();
        }

        clear();
        wrefresh(win);
    }

    void displayItems(Queue& itemQueue) {
        int index = 0;

        if (itemQueue.isEmpty()) {
            mvprintw(0, 60, "No items collected to display.");
            return;
        }

        mvprintw(0, 60, "Items collected:");

        while (!itemQueue.isEmpty()) {
            int x = itemQueue.getFrontX();
            int y = itemQueue.getFrontY();
            char ch = itemQueue.getFrontCh();

            mvprintw(1 + index, 60, "Item %d: (%2d, %2d, '%c')", index + 1, y - 1, x - 2, ch);
            itemQueue.dequeue();
            index++;
        }
    }

    void run() {
        int iterations = 0;
        while (running) {
            if (!gameOver) {
                this->displayGame(iterations);
                this->playerMove();
                this->updateCoins(iterations);
                iterations++;
            } else {
                score += movesRemaining;

                if (gameWon) {
                    clear();
                    wclear(win);
                    refresh();
                    wrefresh(win);

                    attron(COLOR_PAIR(1));
                    mvprintw(0, 0, "%s", "Congratulations! You actually won!!!");
                    mvprintw(1, 0, "%s", "You found the key and then found the door!!");
                    attroff(COLOR_PAIR(1));

                    copyGame.displayGrid(copyGame.getHead()->right->down);

                    attron(COLOR_PAIR(1));
                    mvprintw(26, 0, "%s", "Initial game state.");
                    mvprintw(27, 0, "%s", "Press any key to exit.");
                    displayItems(itemsCollected);
                    attroff(COLOR_PAIR(1));

                    refresh();
                    wrefresh(win);

                    getch();
                    running = false;
                } else {
                    if (movesRemaining == 0) {
                        clear();
                        wclear(win);
                        refresh();
                        wrefresh(win);

                        attron(COLOR_PAIR(1));
                        mvprintw(0, 0, "%s", "That didn't work, you lost!");
                        mvprintw(1, 0, "%s", "You ran out of moves.");
                        mvprintw(2, 0, "Score: %3d", score);
                        attroff(COLOR_PAIR(1));

                        copyGame.displayGrid(copyGame.getHead()->right->down);

                        attron(COLOR_PAIR(1));
                        mvprintw(26, 0, "%s", "Initial game state.");
                        mvprintw(27, 0, "%s", "Press any key to exit.");
                        displayItems(itemsCollected);
                        attroff(COLOR_PAIR(1));

                        refresh();
                        wrefresh(win);

                        getch();
                        running = false;
                    } else {
                        clear();
                        wclear(win);
                        refresh();
                        wrefresh(win);

                        attron(COLOR_PAIR(1));
                        mvprintw(0, 0, "%s", "Congratulations! You have lost!");
                        mvprintw(1, 0, "%s", "You ran into a bomb.");
                        mvprintw(2, 0, "Score: %3d", score);
                        attroff(COLOR_PAIR(1));

                        copyGame.displayGrid(copyGame.getHead()->right->down);

                        attron(COLOR_PAIR(1));
                        mvprintw(26, 0, "%s", "Initial game state.");
                        mvprintw(27, 0, "%s", "Press any key to exit.");
                        displayItems(itemsCollected);
                        attroff(COLOR_PAIR(1));

                        refresh();
                        wrefresh(win);

                        getch();
                        running = false;
                    }
                }
            }
        }
    }

    int distance(const GridNode* player, const GridNode* key, const GridNode* door, const int mode) {
        int startX = 0, startY = 0;
        int targetX = 0, targetY = 0;
        int keyX = 0, keyY = 0;

        for (int i = 1; i < 15; i++) {
            for (int j = 1; j < 15; j++) {
                if (gameGrid.getNode(i, j) == player) {
                    startX = i;
                    startY = j;
                }

                if (gameGrid.getNode(i, j) == key && mode == 0) {
                    targetX = i;
                    targetY = j;
                }

                if (gameGrid.getNode(i, j) == key && mode == 2) {
                    keyX = i;
                    keyY = j;
                }

                if (gameGrid.getNode(i, j) == door && (mode == 1 || mode == 2)) {
                    targetX = i;
                    targetY = j;
                }
            }
        }

        if (mode == 2) {
            startX = keyX;
            startY = keyY;
        }

        std::cout << "Player: (" << startX << "," << startY << ") ";
        std::cout << "Target (Key/Door): (" << targetX << "," << targetY << ")" << std::endl;

        /*mvprintw(0, 0, "%3d", startX);
        mvprintw(1, 0, "%3d", startY);
        mvprintw(2, 0, "%3d", targetX);
        mvprintw(3, 0, "%3d", targetY);*/

        return abs(startX - targetX - 2) + abs(startY - targetY - 2);
    }

    void updateCoins(int &iterations) {
        int randomValue1 = rand() % 6 + 10;
        int randomValue2 = rand() % 6 + 10;

        if ((randomValue1 >= 10 && randomValue1 < (iterations % 16)) || (randomValue2 >= 10 && randomValue2 < (iterations % 16))) {
            iterations = 0;
            int coinCount = 0;

            GridNode* currentRow = gameGrid.getHead();

            while (currentRow != nullptr) {
                GridNode* currentCell = currentRow;

                while (currentCell != nullptr) {
                    int randomNum = rand() % 100 + 1;

                    if (randomNum >= 85 && randomNum < 100 && currentCell->value != 'P' && currentCell->value != 'K' && currentCell->value != 'D' && currentCell->value != 'B' && currentCell->value != '#' && coinCount < Grid::getCoinThresh(gameGrid.getRows(), gameGrid.getCols())) {
                        currentCell->value = 'O';
                        coinCount++;
                    } else {
                        if (currentCell->value == 'O') {
                            currentCell->value = '.';
                        }
                    }

                    currentCell = currentCell->right;
                }

                currentRow = currentRow->down;
            }
        }
    }

    void displayGame(int &iterations) {
        attron(COLOR_PAIR(1));

        int offsetRow = 0;

        mvprintw(offsetRow, 0, "%s", "|\t|\t|");
        mvprintw(offsetRow, 25, "%s", "Mode: ");
        switch (gameGrid.getRows()) {
            case 10:
                mvprintw(offsetRow, 31, "%s", "Easy.");
                if (iterations == 0) {
                    movesRemaining += 6;
                    undoes = 6;
                }
                break;
            case 15:
                mvprintw(offsetRow, 31, "%s", "Medium.");
                if (iterations == 0) {
                    movesRemaining += 2;
                    undoes = 4;
                }
                break;
            case 20:
                mvprintw(offsetRow, 31, "%s", "Hard.");
                if (iterations == 0) {
                    movesRemaining += 1;
                    undoes = 1;
                }
                break;
            default:
                NULL;
        }

        iterations++;

        mvprintw(offsetRow + 2, 0, "%s", "Remaining moves: ");
        mvprintw(offsetRow + 2, 16, "%2d", movesRemaining);
        mvprintw(offsetRow + 2, 25, "%s", "Remaining undoes: ");
        mvprintw(offsetRow + 2, 42, "%2d", undoes);
        mvprintw(offsetRow + 2, 50, "%s", "Score:");
        mvprintw(offsetRow + 2, 56, "%2d", score);

        mvprintw(offsetRow + 4, 0, "%s", "Hint: ");
        mvprintw(offsetRow + 4, 50, "%s", "Key Status: ");
        mvprintw(offsetRow + 4, 62, "%s", "                    ");

        switch (keyFound) {
            case false:
                mvprintw(offsetRow + 4, 62, "%s", "Not found.");
                break;
            case true:
                mvprintw(offsetRow + 4, 62, "%s", "Found.");
                break;
            default:
                NULL;
        }

        attroff(COLOR_PAIR(1));

        gameGrid.displayGrid(player);
        wrefresh(win);

    }

    void playerMove() {
        int keyPress = getch();

        if (keyPress == 'q' || keyPress == 'Q') {
            running = false;
            return;
        }

        GridNode* previousCell = player;

        if (keyPress == KEY_UP && player->up->value != '#' && movesMade.peek() != 2) {
            player = player->up;
            movesMade.push(8);
        }
        else if (keyPress == KEY_LEFT && player->left->value != '#' && movesMade.peek() != 6) {
            player = player->left;
            movesMade.push(4);
        }
        else if (keyPress == KEY_RIGHT && player->right->value != '#' && movesMade.peek() != 4) {
            player = player->right;
            movesMade.push(6);
        }
        else if (keyPress == KEY_DOWN && player->down->value != '#' && movesMade.peek() != 8) {
            player = player->down;
            movesMade.push(2);
        }
        else if (keyPress == 'u' || keyPress == 'U') {
            undo();
            return;
        }
        else {
            return;
        }

        if (player->value == 'O' || key == player || (door == player && keyFound)) {
            int xCoord = 0, yCoord = 0;
            char ch;

            if (player->value == 'O') {
                ch = 'O';
                score += 2;
                undoes++;
            } else if (key == player) {
                keyFound = true;
                ch = 'K';
            } else if (door == player && keyFound) {
                gameWon = true;
                gameOver = true;
                ch = 'D';
            }

            GridNode* currentRow = gameGrid.getHead();
            while (currentRow != nullptr) {
                GridNode* currentCell = currentRow;
                xCoord++;
                yCoord = 0;
                while (currentCell != nullptr) {
                    if (currentCell == player) {
                        itemsCollected.enqueue(xCoord, yCoord, ch);
                        break;
                    }

                    yCoord++;
                    currentCell = currentCell->right;
                }

                currentRow = currentRow->down;
            }
        }

        switch (player->value) {
            case 'B':
                gameOver = true;
                break;
            case 'O':

                break;
            default:
                NULL;
        }

        player->value = 'P';
        previousCell->value = '.';
        movesRemaining--;
    }

    void undo() {
        GridNode* previousCell = player;

        switch (movesMade.peek()) {
            case 8:
                player = player->down;
                break;
            case 4:
                player = player->right;
                break;
            case 6:
                player = player->left;
                break;
            case 2:
                player = player->up;
                break;
            default:
                return;
        }

        player->value = 'P';
        previousCell->value = '.';
        movesMade.pop();
    }
};

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Yellow boundary + text
    init_pair(2, COLOR_WHITE, COLOR_BLACK);   // Cells
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); // Player
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // Coin
    init_pair(5, COLOR_CYAN, COLOR_BLACK); // Key
    init_pair(6, COLOR_RED, COLOR_BLACK); // Bomb
    init_pair(7, COLOR_BLUE, COLOR_BLACK); // Door

    int rows = 15, cols = 15;
    int difficulty = -1;
    Game game(rows, cols, difficulty);

    game.run();

    return 0;
}