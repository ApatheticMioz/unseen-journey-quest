// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppUseAuto
// ReSharper disable CppLocalVariableMayBeConst

// Muhammad Abdullah Ali
// i23-2523
// Section A
// Data Structures Assignment 2


#include <iostream>
#include <curses.h>
using namespace std;

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
    Grid(const int rows, const int cols) {
        this->rows = rows;
        this->cols = cols;
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

    void initGrid() {
        GridNode* previousRow = nullptr;
        GridNode* currentRow = nullptr;
        GridNode* previousCell = nullptr;

        for (int i = 0; i < rows; i++) {
            previousCell = nullptr;
            for (int j = 0; j < cols; j++) {

                GridNode* newCell = new GridNode((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) ? '#' : '.');

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

    void displayGridConsole() const {
        GridNode* currentRow = head;
        while (currentRow != nullptr) {
            GridNode* currentCell = currentRow;

            while (currentCell != nullptr) {
                cout << currentCell->value;
                currentCell = currentCell->right;
            }

            cout << endl;
            currentRow = currentRow->down;
        }
    }

    void displayGrid(GridNode* player) const {
        GridNode* currentRow = head;
        int row = 6;

        while (currentRow != nullptr) {
            GridNode* currentCell = currentRow;
            int col = 14;

            while (currentCell != nullptr) {
                switch (currentCell->value) {
                case '#':
                    attron(COLOR_PAIR(1));
                    mvprintw(row, col, "%c", currentCell->value);
                    break;

                case 'P':
                    attron(COLOR_PAIR(3));
                    mvprintw(row, col, "%c", currentCell->value);
                    break;

                default:
                    attron(COLOR_PAIR(2));
                    mvprintw(row, col, "%c", currentCell->value);
                }

                attroff(COLOR_PAIR(1));
                attroff(COLOR_PAIR(3));
                attroff(COLOR_PAIR(2));

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
    int winHeight, winWidth;
    WINDOW* win;
    GridNode* player;
    bool running;

public:
    Game(const int rows, const int cols) : gameGrid(rows, cols) {
        gameGrid.initGrid();
        winHeight = winWidth = 50;
        win = newwin(winHeight, winWidth, 0, 0);
        player = gameGrid.getHead()->right->down;
        player->value = 'P';
        running = true;
    }

    void run() {
        while (running) {
            this->displayGame();

            if (getch() == 'q') {
                running = false;
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

        getch();
    }

    void playerMove() const {

    }

    ~Game() {
        delwin(win);
        endwin();
    }
};

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

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);  // Yellow boundary + text
    init_pair(2, COLOR_GREEN, COLOR_BLACK);   // Green cells
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); // Player

    int rows = 15, cols = 15;
    Game game(rows, cols);

    game.run();

    return 0;
}


