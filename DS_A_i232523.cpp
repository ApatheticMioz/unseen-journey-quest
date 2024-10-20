// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppUseAuto
// ReSharper disable CppLocalVariableMayBeConst

// Muhammad Abdullah Ali
// i23-2523
// Section A
// Data Structures Assignment 2

#include <curses.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

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

class Queue {
    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    ~Queue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(const int x) {
        Node* temp = new Node(x);

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

        Node* temp = front;
        front = front->next;

        if (isEmpty()) {
            rear = nullptr;
        }

        delete temp;
    }

    int getFront() const {
        if (isEmpty()) {
            return -1;
        }

        return front->data;
    }

    int getRear() const {
        if (isEmpty()) {
            return -1;
        }

        return rear->data;
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
};

class Grid {
    GridNode* head;
    int rows;
    int cols;

public:
    Grid() {
        this->rows = 0;
        this->cols = 0;
        this->head = nullptr;
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

    void initGrid(const int difficulty) {
        srand(time(0));

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

        GridNode* previousRow = nullptr;
        GridNode* currentRow = nullptr;
        GridNode* previousCell = nullptr;

        int coinThresh = static_cast<int>(rows * cols * 0.09);
        int bombThresh = static_cast<int>(rows * cols * 0.06);

        int xDoor = rand() % 12 + 1, yDoor = rand() % 12 + 1, xKey = rand() % 12 + 1, yKey = rand() % 12 + 1;
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
                    } else if ((randomValue >= 30 && randomValue < 40 && bombCount < bombThresh) && (i != 2 && j != 1) && (i != 1 && j != 2)) {
                        cell = 'B';
                        bombCount++;
                    } else if (randomValue >= 85 && randomValue < 100 && coinCount < coinThresh) {
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

    void displayGrid(GridNode* player) const {
        GridNode* currentRow = head;
        int row = 6;

        while (currentRow != nullptr) {
            GridNode* currentCell = currentRow;
            int col = 14;

            while (currentCell != nullptr) {
                move(row, col);

                switch (currentCell->value) {
                    case '#':
                        attron(COLOR_PAIR(1));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(1));
                        break;
                    case 'P':
                        attron(COLOR_PAIR(3));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(3));
                        break;
                    case 'K':
                        attron(COLOR_PAIR(5));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(5));
                        break;
                    case 'O':
                        attron(COLOR_PAIR(4));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(4));
                        break;
                    case 'B':
                        attron(COLOR_PAIR(6));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(6));
                        break;
                    case 'D':
                        attron(COLOR_PAIR(7));
                        addch(currentCell->value);
                        attroff(COLOR_PAIR(7));
                        break;
                    default:
                        addch(currentCell->value);
                }

                currentCell = currentCell->right;
                col += 2;
            }

            currentRow = currentRow->down;
            row++;
        }
    }
};

class Game {
    Grid gameGrid;
    WINDOW* win;
    GridNode* player;
    Stack moves;
    bool running;
    int winHeight, winWidth;
    int coinThresh, bombThresh;

public:
    Game(const int rows, const int cols, int difficulty) {
        winHeight = 100;
        winWidth = 50;
        win = newwin(winHeight, winWidth, 0, 0);

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

        gameGrid.initGrid(difficulty);

        player = gameGrid.getHead()->right->down;
        player->value = 'P';
        running = true;
        coinThresh = static_cast<int>(rows * cols * 0.09);
        bombThresh = static_cast<int>(rows * cols * 0.06);
    }

    ~Game() {
        delwin(win);
        endwin();
    }

    void run() {
        int iterations = 0;
        while (running) {
            this->displayGame();
            this->playerMove();
            this->updateCoins(iterations);
            iterations++;

            if (iterations % 15 == 0) {
                iterations = 0;
            }
        }
    }

    void updateCoins(int &iterations) {
        int randomValue1 = rand() % 6 + 10;
        int randomValue2 = rand() % 6 + 10;

        if ((randomValue1 >= 10 && randomValue1 < iterations) || (randomValue2 >= 10 && randomValue2 < iterations)) {
            iterations = 0;
            int coinCount = 0;

            GridNode* currentRow = gameGrid.getHead();

            while (currentRow != nullptr) {
                GridNode* currentCell = currentRow;

                while (currentCell != nullptr) {
                    int randomNum = rand() % 100 + 1;

                    if (randomNum >= 85 && randomNum < 100 && currentCell->value != 'P' && currentCell->value != 'K' && currentCell->value != 'D' && currentCell->value != 'B' && currentCell->value != '#' && coinCount < coinThresh) {
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

    void displayGame() const {
        attron(COLOR_PAIR(1));

        int offsetRow = 0;

        mvprintw(offsetRow, 0, "%s", "|\t|\t|");
        mvprintw(offsetRow, 25, "%s", "Mode: ");

        mvprintw(offsetRow + 2, 0, "%s", "Remaining moves: ");
        mvprintw(offsetRow + 2, 25, "%s", "Remaining undoes: ");
        mvprintw(offsetRow + 2, 50, "%s", "Score: ");

        mvprintw(offsetRow + 4, 0, "%s", "Hint: ");

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
        char newCell;

        if (keyPress == KEY_UP && player->up->value != '#' && moves.peek() != 2) {
            newCell = player->up->value;
            player = player->up;
            moves.push(8);
        }
        else if (keyPress == KEY_LEFT && player->left->value != '#' && moves.peek() != 6) {
            newCell = player->left->value;
            player = player->left;
            moves.push(4);
        }
        else if (keyPress == KEY_RIGHT && player->right->value != '#' && moves.peek() != 4) {
            newCell = player->right->value;
            player = player->right;
            moves.push(6);
        }
        else if (keyPress == KEY_DOWN && player->down->value != '#' && moves.peek() != 8) {
            newCell = player->down->value;
            player = player->down;
            moves.push(2);
        }
        else if (keyPress == 'u' || keyPress == 'U') {
            undo();
            return;
        }
        else {
            return;
        }

        player->value = 'P';
        previousCell->value = '.';
    }

    void undo() {
        GridNode* previousCell = player;

        switch (moves.peek()) {
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
        moves.pop();
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