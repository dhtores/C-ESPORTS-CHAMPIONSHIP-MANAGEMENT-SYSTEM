#include "task2.hpp"
#include <iostream>
using namespace std;

PriorityQueue::PriorityQueue() { size = 0; }

bool PriorityQueue::isFull() { return size == MAX_QUEUE; }
bool PriorityQueue::isEmpty() { return size == 0; }

void PriorityQueue::enqueue(Player_T2 p) {
    if (isFull()) {
        cout << "Priority queue is full.\n";
        return;
    }
    int i = size - 1;
    while (i >= 0 && strcmp(data[i].type, p.type) > 0) {
        data[i + 1] = data[i];
        i--;
    }
    data[i + 1] = p;
    size++;
}

Player_T2 PriorityQueue::dequeue() {
    if (isEmpty()) {
        cout << "Priority queue is empty.\n";
        Player_T2 temp;
        strcpy_s(temp.name, sizeof(temp.name), "EMPTY");
        strcpy_s(temp.id, sizeof(temp.id), "EMPTY");
        strcpy_s(temp.type, sizeof(temp.type), "EMPTY");
        return temp;
    }
    return data[--size];
}

void PriorityQueue::display() {
    cout << "\n[Priority Queue - Early Birds & Wildcards]\n";
    for (int i = 0; i < size; i++) {
        cout << data[i].name << " (" << data[i].type << ")\n";
    }
}

CircularQueue::CircularQueue() : front(0), rear(-1), count(0) {}

bool CircularQueue::isFull() { return count == MAX_QUEUE; }
bool CircularQueue::isEmpty() { return count == 0; }

void CircularQueue::enqueue(Player_T2 p) {
    if (isFull()) {
        cout << "Check-in queue is full.\n";
        return;
    }
    rear = (rear + 1) % MAX_QUEUE;
    data[rear] = p;
    count++;
}

Player_T2 CircularQueue::dequeue() {
    if (isEmpty()) {
        cout << "Check-in queue is empty.\n";
        Player_T2 temp;
        strcpy_s(temp.name, sizeof(temp.name), "EMPTY");
        strcpy_s(temp.id, sizeof(temp.id), "EMPTY");
        strcpy_s(temp.type, sizeof(temp.type), "EMPTY");
        return temp;
    }
    Player_T2 temp = data[front];
    front = (front + 1) % MAX_QUEUE;
    count--;
    return temp;
}

void CircularQueue::display() {
    cout << "\n[Regular Check-in Queue]\n";
    int i = front;
    for (int c = 0; c < count; c++) {
        cout << data[i].name << " (" << data[i].type << ")\n";
        i = (i + 1) % MAX_QUEUE;
    }
}

ReplacementQueue::ReplacementQueue() : front(0), rear(-1) {}

void ReplacementQueue::enqueue(Player_T2 p) {
    if (rear >= MAX_QUEUE - 1) {
        cout << "Replacement queue is full.\n";
        return;
    }
    data[++rear] = p;
}

Player_T2 ReplacementQueue::dequeue() {
    if (front > rear) {
        cout << "No replacements available.\n";
        Player_T2 temp;
        strcpy_s(temp.name, sizeof(temp.name), "EMPTY");
        strcpy_s(temp.id, sizeof(temp.id), "EMPTY");
        strcpy_s(temp.type, sizeof(temp.type), "EMPTY");
        return temp;
    }
    return data[front++];
}

void ReplacementQueue::display() {
    cout << "\n[Replacement Queue]\n";
    for (int i = front; i <= rear; i++) {
        cout << data[i].name << " (" << data[i].type << ")\n";
    }
}

void runTask2() {
    PriorityQueue pq;
    CircularQueue cq;
    ReplacementQueue rq;

    int choice;
    Player_T2 p;

    do {
        cout << "\n=== Tournament Registration & Player Queueing ===\n";
        cout << "1. Register/Check-in Player\n";
        cout << "2. Withdraw Player & Add Replacement\n";
        cout << "3. Replace Withdrawn Player\n";
        cout << "4. View All Queues\n";
        cout << "0. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter Player Name: ";
            cin.getline(p.name, 50);
            cout << "Enter Player ID: ";
            cin.getline(p.id, 10);
            cout << "Enter Type (EarlyBird / Wildcard / Regular): ";
            cin.getline(p.type, 20);
            if (strcmp(p.type, "EarlyBird") == 0 || strcmp(p.type, "Wildcard") == 0)
                pq.enqueue(p);
            else
                cq.enqueue(p);
            break;

        case 2:
            cout << "Withdrawing a player...\n";
            cout << "Enter Replacement Name: ";
            cin.getline(p.name, 50);
            cout << "Enter Replacement ID: ";
            cin.getline(p.id, 10);
            strcpy_s(p.type, sizeof(p.type), "Regular");
            rq.enqueue(p);
            break;

        case 3:
            cout << "Replacing withdrawn player...\n";
            p = rq.dequeue();
            if (strcmp(p.name, "EMPTY") != 0)
                cq.enqueue(p);
            break;

        case 4:
            pq.display();
            cq.display();
            rq.display();
            break;

        case 0:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}
