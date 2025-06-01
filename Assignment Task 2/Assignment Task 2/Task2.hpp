#ifndef TASK2_HPP
#define TASK2_HPP
#include <iostream>
#include <cstring>

const int MAX_QUEUE = 100;

struct Player_T2 {
    char id[10];
    char name[50];
    char type[20];  // "EarlyBird", "Wildcard", "Regular"
};

// === PRIORITY QUEUE ===
class PriorityQueue {
private:
    Player_T2 data[MAX_QUEUE];
    int size;

public:
    PriorityQueue();

    bool isFull();
    bool isEmpty();
    void enqueue(Player_T2 p);
    Player_T2 dequeue();
    void display();  // ✅ declaration added
};

// === CIRCULAR QUEUE ===
class CircularQueue {
private:
    Player_T2 data[MAX_QUEUE];
    int front, rear, count;

public:
    CircularQueue();

    bool isFull();
    bool isEmpty();
    void enqueue(Player_T2 p);
    Player_T2 dequeue();
    void display();  // ✅ declaration added
};

// === REPLACEMENT QUEUE ===
class ReplacementQueue {
private:
    Player_T2 data[MAX_QUEUE];
    int front, rear;

public:
    ReplacementQueue();

    void enqueue(Player_T2 p);
    Player_T2 dequeue();
    void display();  // ✅ declaration added
};

void runTask2();

#endif
