#include "Task4.hpp"

// --- MatchStack Implementation ---
MatchStack::MatchStack() { top = -1; }
bool MatchStack::isEmpty() { return top == -1; }
bool MatchStack::isFull() { return top == MAX_STACK - 1; }

void MatchStack::push(MatchResult m) {
    if (!isFull()) stack[++top] = m;
}

MatchResult MatchStack::pop() {
    if (!isEmpty()) return stack[top--];
    return {};
}

void MatchStack::displayRecent(int count) {
    int shown = 0;
    for (int i = top; i >= 0 && shown < count; i--, shown++) {
        MatchResult& m = stack[i];
        std::cout << m.matchID << ": " << m.player1 << " vs " << m.player2
            << " → Winner: " << m.winner << "\n";
    }
}

// --- MatchHistoryList Implementation ---
MatchHistoryList::MatchHistoryList() { head = nullptr; }

void MatchHistoryList::insert(MatchResult m) {
    HistoryNode* newNode = new HistoryNode{ m, nullptr };
    if (!head) head = newNode;
    else {
        HistoryNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void MatchHistoryList::displayByPlayer(std::string player) {
    HistoryNode* temp = head;
    while (temp) {
        if (temp->data.player1 == player || temp->data.player2 == player) {
            std::cout << temp->data.matchID << ": "
                << temp->data.player1 << " vs " << temp->data.player2
                << " → Winner: " << temp->data.winner << "\n";
        }
        temp = temp->next;
    }
}

void MatchHistoryList::removeLast() {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    HistoryNode* temp = head;
    while (temp->next->next) temp = temp->next;
    delete temp->next;
    temp->next = nullptr;
}

HistoryNode* MatchHistoryList::getHead() { return head; }

// --- File + Utility Functions ---
void loadHistoryFromFile(const std::string& filename,
    MatchStack& stack, MatchHistoryList& list) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        MatchResult m;
        getline(ss, m.matchID, ',');
        getline(ss, m.player1, ',');
        getline(ss, m.player2, ',');
        ss >> m.score1; ss.ignore();
        ss >> m.score2; ss.ignore();
        getline(ss, m.winner, ',');
        getline(ss, m.date);

        stack.push(m);
        list.insert(m);
    }
    file.close();
}

void appendMatchToFile(const std::string& filename, const MatchResult& m) {
    std::ofstream file(filename, std::ios::app);
    file << m.matchID << "," << m.player1 << "," << m.player2 << ","
        << m.score1 << "," << m.score2 << "," << m.winner << "," << m.date << "\n";
    file.close();
}

void logMatchResult(MatchStack& stack, MatchHistoryList& list, const std::string& filename) {
    MatchResult m;
    std::cout << "Enter Match ID: ";
    std::cin >> m.matchID;
    std::cout << "Enter Player 1 Name: ";
    std::cin >> m.player1;
    std::cout << "Enter Player 2 Name: ";
    std::cin >> m.player2;
    std::cout << "Enter Player 1 Score: ";
    std::cin >> m.score1;
    std::cout << "Enter Player 2 Score: ";
    std::cin >> m.score2;

    if (m.score1 > m.score2) m.winner = m.player1;
    else if (m.score2 > m.score1) m.winner = m.player2;
    else m.winner = "Draw";

    std::cout << "Enter Match Date (YYYY-MM-DD): ";
    std::cin >> m.date;

    stack.push(m);
    list.insert(m);
    appendMatchToFile(filename, m);

    std::cout << "Match result logged successfully.\n";
}

void viewRecentResults(MatchStack& stack) {
    if (stack.isEmpty()) {
        std::cout << "No recent match results to display.\n";
        return;
    }
    std::cout << "\nRecent Match Results:\n";
    stack.displayRecent();
}

void viewPlayerHistory(MatchHistoryList& list) {
    std::string player;
    std::cout << "Enter player name to view history: ";
    std::cin >> player;
    std::cout << "\nMatch History for " << player << ":\n";
    list.displayByPlayer(player);
}

void undoLastResult(MatchStack& stack, MatchHistoryList& list, const std::string& filename) {
    if (stack.isEmpty()) {
        std::cout << "No match to undo.\n";
        return;
    }

    MatchResult removed = stack.pop();
    list.removeLast();
    std::cout << "Removed last match: " << removed.matchID << "\n";

    std::ofstream file(filename);
    HistoryNode* temp = list.getHead();
    while (temp) {
        MatchResult m = temp->data;
        file << m.matchID << "," << m.player1 << "," << m.player2 << ","
            << m.score1 << "," << m.score2 << "," << m.winner << "," << m.date << "\n";
        temp = temp->next;
    }
    file.close();
    std::cout << "Match history file updated.\n";
}

void viewPlayerStatsAndHighlights(MatchHistoryList& list, MatchStack& stack) {
    std::string player;
    std::cout << "Enter player name: ";
    std::cin >> player;

    int played = 0, wins = 0, losses = 0, draws = 0;
    int highestScore = 0;
    int biggestWinMargin = 0;
    std::string marginOpponent = "-";
    std::string mostRecentMatchID = "-";
    std::string mostRecentDate = "-";

    HistoryNode* temp = list.getHead();

    while (temp) {
        MatchResult m = temp->data;
        bool involved = (m.player1 == player || m.player2 == player);
        if (involved) {
            played++;
            if (m.winner == player) wins++;
            else if (m.winner == "Draw") draws++;
            else losses++;

            int playerScore = (m.player1 == player) ? m.score1 : m.score2;
            int opponentScore = (m.player1 == player) ? m.score2 : m.score1;

            if (playerScore > highestScore)
                highestScore = playerScore;

            if (playerScore > opponentScore) {
                int margin = playerScore - opponentScore;
                if (margin > biggestWinMargin) {
                    biggestWinMargin = margin;
                    marginOpponent = (m.player1 == player) ? m.player2 : m.player1;
                }
            }
        }
        temp = temp->next;
    }

    // Get most recent match from stack (top)
    if (!stack.isEmpty()) {
        MatchResult recent = stack.peek(); // need to add a peek function!
        if (recent.player1 == player || recent.player2 == player) {
            mostRecentMatchID = recent.matchID;
            mostRecentDate = recent.date;
        }
    }

    // Output results
    std::cout << "\nStats for " << player << ":\n";
    std::cout << "Matches Played: " << played << "\n";
    std::cout << "Wins: " << wins << "\n";
    std::cout << "Losses: " << losses << "\n";
    std::cout << "Draws: " << draws << "\n";

    std::cout << "\nHighlights:\n";
    std::cout << "Highest Score: " << highestScore << "\n";
    std::cout << "Biggest Win Margin: " << biggestWinMargin;
    if (biggestWinMargin > 0)
        std::cout << " (vs " << marginOpponent << ")";
    std::cout << "\n";

    std::cout << "Most Recent Match: " << mostRecentMatchID
        << " (" << mostRecentDate << ")\n";
    }
    

    // --- Stack Peek Implementation ---
    MatchResult MatchStack::peek() {
        if (!isEmpty()) return stack[top];
        return {};
    }
    void runTask4() {
        MatchStack stack;
        MatchHistoryList list;
        const std::string filename = "match_history.txt";

        loadHistoryFromFile(filename, stack, list);

        int option;
        do {
            std::cout << "\n=== Game Result Logging & Performance History ===\n";
            std::cout << "1. Log New Match Result\n";
            std::cout << "2. View Recent Match Results\n";
            std::cout << "3. View Player Match History\n";
            std::cout << "4. Undo Last Match Result\n";
            std::cout << "5. Player Stats & Highlights\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Enter your choice: ";
            std::cin >> option;

            switch (option) {
            case 1:
                logMatchResult(stack, list, filename);
                break;
            case 2:
                viewRecentResults(stack);
                break;
            case 3:
                viewPlayerHistory(list);
                break;
            case 4:
                undoLastResult(stack, list, filename);
                break;
            case 5:
                viewPlayerStatsAndHighlights(list, stack);
                break;
            case 0:
                std::cout << "Returning to main menu...\n";
                break;
            default:
                std::cout << "Invalid option.\n";
            }
        } while (option != 0);
    }

