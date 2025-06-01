#include <iostream>
#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"

using namespace std;

int main() {
    int choice;
    do {
        cout << "\n===== APU ESPORTS SYSTEM MAIN MENU =====\n";
        cout << "1. Match Scheduling & Player Progression\n";
        cout << "2. Tournament Registration & Player Queueing\n";
        cout << "3. Live Stream & Spectator Queue Management\n";  
        cout << "4. Game Result Logging & Performance History\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            runTask1();
            break;
        case 2:
            runTask2();
            break;
        case 3:
            menu();  
            break;
        case 4:
            runTask4();
            break;
        case 0:
            cout << "Exiting system.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
