#ifndef TASK1_HPP
#define TASK1_HPP
void runTask1();
#include <iostream>
#include <fstream>
#include <string>

// Structs
struct Player {
    std::string id;
    std::string name;
    int ranking;
};

struct MatchSchedule {
    std::string matchID;
    Player player1;
    Player player2;
    int score1;
    int score2;
    std::string winner;
    std::string date;
};

// Queue class
class PlayerQueue {
private:
    static const int MAX = 100;
    Player data[MAX];
    int front, rear, count;
public:
    PlayerQueue();
    bool isEmpty();
    bool isFull();
    void enqueue(Player p);
    Player dequeue();
    int size();
    void displayQueue();
};

// Functions
void registerPlayer(PlayerQueue& queue);
void scheduleMatches(PlayerQueue& queue, MatchSchedule scheduledMatches[], int& matchCount);
void simulateMatches(MatchSchedule matches[], int matchCount);
void exportMatchesToFile(MatchSchedule matches[], int matchCount, const std::string& filename);
void loadPlayersFromFile(PlayerQueue& q, const std::string& filename);
void appendPlayerToFile(const std::string& filename, const Player& p);
#endif
