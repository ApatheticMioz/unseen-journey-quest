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

class NodeList {
public:
    int x;
    int y;
    NodeList* right;
    NodeList* left;
    NodeList* down;
    NodeList* up;

    NodeList(const int x, const int y) {
        this->x = x;
        this->y = y;
        right = nullptr;
        left = nullptr;
        down = nullptr;
        up = nullptr;
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

    return 0;
}
