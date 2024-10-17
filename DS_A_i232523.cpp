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

class GridCell {
public:
    char value;
    GridCell* right;
    GridCell* left;
    GridCell* down;
    GridCell* up;

    GridCell(const char v) {
        this->value = v;
        right = nullptr;
        left = nullptr;
        down = nullptr;
        up = nullptr;
    }
};

class Grid {
    GridCell* head;
    int rows;
    int cols;

public:
    Grid(const int rows, const int cols) {
        this->rows = rows;
        this->cols = cols;
        this->head = nullptr;
    }

    void initGrid() {
        GridCell* previousRow = nullptr;
        GridCell* currentRow = nullptr;
        GridCell* previousCell = nullptr;

        for (int i = 0; i < rows; i++) {
            previousCell = nullptr;
            for (int j = 0; j < cols; j++) {

                GridCell* newCell = new GridCell((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) ? '#' : '.');

                if (previousCell) {
                    previousCell->right = newCell;
                    newCell->left = previousCell;
                }
                previousCell = newCell;

                if (previousRow) {
                    GridCell* above = previousRow;

                    for (int k = 0; k < j; k++) {
                        above = above->right;
                    }
                    above->down = newCell;
                    newCell->up = above;
                }

                if (i == 0 && j == 0) {
                    head = newCell;
                }

                if (j == 0) {
                    currentRow = newCell;
                }
            }

            previousRow = currentRow;
        }
    }

    void displayGridConsole() const {
        GridCell* currentRow = head;
        while (currentRow != nullptr) {
            GridCell* currentCell = currentRow;
            while (currentCell != nullptr) {
                cout << currentCell->value;
                currentCell = currentCell->right;
            }
            cout << endl;
            currentRow = currentRow->down;
        }
    }

    void displayGrid(WINDOW* window) const {
        GridCell* currentRow = head;
        while (currentRow != nullptr) {
            GridCell* currentCell = currentRow;
            while (currentCell != nullptr) {
                wprintw(window, &currentCell->value);
                currentCell = currentCell->right;
            }
            wprintw(window, "\n");
            currentRow = currentRow->down;
        }
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

    int window_height = 17;
    int window_width = 17;

    WINDOW* win = newwin(window_height, window_width, 0, 0);

    Grid gameGrid(15, 15);
    gameGrid.initGrid();
    gameGrid.displayGridConsole();

    wmove(win, 1, 1);

    gameGrid.displayGrid(win);

    wrefresh(win);

    getch();
    endwin();

    return 0;
}

