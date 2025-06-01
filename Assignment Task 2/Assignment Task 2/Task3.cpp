#include "task3.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// === Global Queues ===
vector<Spectator> generalQueue;
priority_queue<Spectator, vector<Spectator>, greater<>> vipQueue;
queue<Spectator> streamQueue;

// === CSV INIT ===
void initializeCSV() {
    ofstream file("seated_spectators.csv");
    file << "Name,Type,WantsStreaming,SeatNumber,Priority\n";
    file.close();
}

// === CSV APPEND ===
void appendToCSV(const Spectator& s, bool seated) {
    ofstream file("seated_spectators.csv", ios::app);
    if (!file.is_open()) {
        cerr << "Error: Cannot open CSV file for writing.\n";
        return;
    }
    file << s.name << "," << s.type << "," << (s.wantsStreaming ? "Yes" : "No") << ","
        << (seated ? s.seatNumber : "Pending") << "," << s.priority << "\n";
    file.close();
}

// === Registration ===
void registerSpectator() {
    string name;
    int typeChoice;
    char streamChoice;

    cout << "\nEnter Spectator Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Type (1=VIP, 2=General): ";
    cin >> typeChoice;
    cout << "Wants to watch stream? (y/n): ";
    cin >> streamChoice;

    bool wantsStreaming = (streamChoice == 'y' || streamChoice == 'Y');
    Spectator s(name, typeChoice, wantsStreaming);

    if (typeChoice == 1)
        vipQueue.push(s);
    else
        generalQueue.push_back(s);

    if (wantsStreaming)
        streamQueue.push(s);

    appendToCSV(s);
    cout << "Registered successfully!\n";
}

// === Cancel Spectator ===
void cancelSpectator() {
    string name;
    cout << "\nEnter spectator name to cancel: ";
    cin.ignore();
    getline(cin, name);

    auto it = remove_if(generalQueue.begin(), generalQueue.end(), [&](const Spectator& s) {
        return s.name == name;
        });

    if (it != generalQueue.end()) {
        generalQueue.erase(it, generalQueue.end());
        cout << "Spectator cancelled from general queue.\n";
        return;
    }

    // VIP and streamQueue trimming left as extension
    cout << "Spectator not found in general queue.\n";
}

// === Search by Name ===
void searchSpectator() {
    string name;
    cout << "\nEnter name to search: ";
    cin.ignore();
    getline(cin, name);

    bool found = false;

    for (const auto& s : generalQueue) {
        if (s.name == name) {
            cout << "\n[GENERAL] Found " << s.name << " | Stream: " << (s.wantsStreaming ? "Yes" : "No") << "\n";
            found = true;
        }
    }

    priority_queue<Spectator, vector<Spectator>, greater<>> tempVip = vipQueue;
    while (!tempVip.empty()) {
        Spectator s = tempVip.top(); tempVip.pop();
        if (s.name == name) {
            cout << "\n[VIP] Found " << s.name << " | Stream: " << (s.wantsStreaming ? "Yes" : "No") << "\n";
            found = true;
        }
    }

    if (!found) cout << "Spectator not found.\n";
}

// === Seat Spectator ===
void seatSpectator() {
    string name, seat;
    cout << "\nEnter name to assign seat: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter seat number: ";
    getline(cin, seat);

    for (auto& s : generalQueue) {
        if (s.name == name) {
            s.seatNumber = seat;
            appendToCSV(s, true);
            cout << "Seat assigned.\n";
            return;
        }
    }

    cout << "Spectator not found.\n";
}

// === View Log ===
void viewSeatedLog() {
    ifstream file("seated_spectators.csv");
    if (!file.is_open()) {
        cerr << "Cannot open file.\n";
        return;
    }

    string line;
    while (getline(file, line))
        cout << line << "\n";
    file.close();
}

// === Streaming Order ===
void startNextStreaming() {
    if (streamQueue.empty()) {
        cout << "No spectators waiting for streaming.\n";
        return;
    }

    Spectator s = streamQueue.front(); streamQueue.pop();
    cout << "\nNow Streaming: " << s.name << " (" << s.type << ")\n";
}

// === View Streaming Queue ===
void viewStreamingQueue() {
    if (streamQueue.empty()) {
        cout << "No streaming spectators.\n";
        return;
    }

    cout << "\n--- Streaming Queue ---\n";
    queue<Spectator> temp = streamQueue;
    while (!temp.empty()) {
        Spectator s = temp.front(); temp.pop();
        cout << s.name << " (" << s.type << ")\n";
    }
}

// === Main Menu ===
void menu() {
    int choice;
    do {
        cout << "\n--- SLive Stream & Spectator Queue Management ---\n";
        cout << "1. Register\n2. Cancel\n3. Search\n4. Assign Seat\n5. View Seated Log\n";
        cout << "6. Start Streaming\n7. View Streaming Queue\n0. Back to main menu\nChoose: ";
        cin >> choice;
        switch (choice) {
        case 1: registerSpectator(); break;
        case 2: cancelSpectator(); break;
        case 3: searchSpectator(); break;
        case 4: seatSpectator(); break;
        case 5: viewSeatedLog(); break;
        case 6: startNextStreaming(); break;
        case 7: viewStreamingQueue(); break;
        }
    } while (choice != 0);
}
