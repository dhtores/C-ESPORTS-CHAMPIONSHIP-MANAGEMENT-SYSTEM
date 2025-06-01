#ifndef TASK3_HPP
#define TASK3_HPP

#include <string>

// Spectator struct definition
struct Spectator {
    std::string name;
    std::string type;
    bool wantsStreaming;
    std::string seatNumber = "Unassigned";
    int priority;

    // Constructor
    Spectator(std::string n, int choice, bool stream)
        : name(n), wantsStreaming(stream) {
        if (choice == 1) {
            type = "VIP";
            priority = 1;
        }
        else if (choice == 2) {
            type = "Influencer";
            priority = 2;
        }
        else {
            type = "General";
            priority = 3;
        }
    }

    // Comparison based on priority
    bool operator>(const Spectator& other) const {
        return priority > other.priority;
    }
};

// Function prototypes
void initializeCSV();
void registerSpectator();
void cancelSpectator();
void searchSpectator();
void seatSpectator();
void viewSeatedLog();
void startNextStreaming();
void viewStreamingQueue();
void menu();
void appendToCSV(const Spectator& s, bool seated = false);

#endif // TASK3_HPP
