#ifndef TASK4_HPP
#define TASK4_HPP
void runTask4();
#include <iostream>
#include <fstream>
#include <sstream>

// Struct
struct MatchResult {
    std::string matchID;
    std::string player1;
    std::string player2;
    int score1;
    int score2;
    std::string winner;
    std::string date;
};

// Stack Class
class MatchStack {
private:
    static const int MAX_STACK = 100;
    MatchResult stack[MAX_STACK];
    int top;

public:
    MatchStack();  // just declare constructor

    bool isEmpty();
    bool isFull();
    void push(MatchResult m);
    MatchResult pop();
    MatchResult peek();  // ✅ declare it like this
    void displayRecent(int count = 5);
};


// Linked List Node
struct HistoryNode {
    MatchResult data;
    HistoryNode* next;
};

// Linked List Class
class MatchHistoryList {
private:
    HistoryNode* head;

public:
    MatchHistoryList();
    void insert(MatchResult m);
    void displayByPlayer(std::string player);
    void removeLast();
    HistoryNode* getHead();
};

// File + Utility Functions
void loadHistoryFromFile(const std::string& filename, MatchStack& stack, MatchHistoryList& list);
void appendMatchToFile(const std::string& filename, const MatchResult& m);
void logMatchResult(MatchStack& stack, MatchHistoryList& list, const std::string& filename);
void viewRecentResults(MatchStack& stack);
void viewPlayerHistory(MatchHistoryList& list);
void undoLastResult(MatchStack& stack, MatchHistoryList& list, const std::string& filename);
void viewPlayerStatsAndHighlights(MatchHistoryList& list, MatchStack& stack);


#endif
