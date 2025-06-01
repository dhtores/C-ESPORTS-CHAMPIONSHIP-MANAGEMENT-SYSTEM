#include "task1.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

// ====== PlayerQueue Implementation ======

PlayerQueue::PlayerQueue() : front(0), rear(-1), count(0) {}

bool PlayerQueue::isEmpty() {
    return count == 0;
}

bool PlayerQueue::isFull() {
    return count == MAX;
}

void PlayerQueue::enqueue(Player p) {
    if (isFull()) {
        cout << "Queue is full!\n";
        return;
    }
    rear = (rear + 1) % MAX;
    data[rear] = p;
    count++;
}

Player PlayerQueue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty!\n";
        return {};
    }
    Player p = data[front];
    front = (front + 1) % MAX;
    count--;
    return p;
}

int PlayerQueue::size() {
    return count;
}

void PlayerQueue::displayQueue() {
    if (isEmpty()) {
        cout << "No players in queue.\n";
        return;
    }
    cout << "\nRegistered Players:\n";
    for (int i = 0; i < count; i++) {
        int index = (front + i) % MAX;
        Player p = data[index];
        cout << "- " << p.id << " | " << p.name << " | Rank: " << p.ranking << endl;
    }
}

// ====== File Functions ======

void loadPlayersFromFile(PlayerQueue& q, const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Player file not found.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Player p;
        getline(ss, p.id, ',');
        getline(ss, p.name, ',');
        ss >> p.ranking;
        q.enqueue(p);
    }
    file.close();
}

void appendPlayerToFile(const string& filename, const Player& p) {
    ofstream file(filename, ios::app);
    file << p.id << "," << p.name << "," << p.ranking << "\n";
    file.close();
}

// ====== Match Scheduling ======

void registerPlayer(PlayerQueue& queue) {
    Player p;
    cout << "\nEnter Player ID: ";
    cin >> p.id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Ranking: ";
    cin >> p.ranking;

    queue.enqueue(p);
    appendPlayerToFile("players.txt", p);
    cout << "\n✅ Registered and saved!\n";
}

void scheduleMatches(PlayerQueue& queue, MatchSchedule matches[], int& matchCount) {
    while (queue.size() >= 2) {
        Player p1 = queue.dequeue();
        Player p2 = queue.dequeue();

        MatchSchedule m;
        m.matchID = "MATCH" + to_string(matchCount + 1);
        m.player1 = p1;
        m.player2 = p2;
        m.score1 = -1;
        m.score2 = -1;
        m.winner = "TBD";
        m.date = "TBD";

        matches[matchCount++] = m;

        cout << "\n🗓️ Match Scheduled → " << m.matchID << ": " << p1.name << " vs " << p2.name << "\n";
    }

    if (queue.size() == 1) {
        cout << "\n1 player left unmatched.\n";
    }
}

void simulateMatches(MatchSchedule matches[], int matchCount) {
    srand((unsigned int)time(0));
    for (int i = 0; i < matchCount; i++) {
        matches[i].score1 = rand() % 10;
        matches[i].score2 = rand() % 10;

        if (matches[i].score1 > matches[i].score2)
            matches[i].winner = matches[i].player1.name;
        else if (matches[i].score2 > matches[i].score1)
            matches[i].winner = matches[i].player2.name;
        else
            matches[i].winner = "Draw";

        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        ostringstream oss;
        oss << 1900 + ltm.tm_year << "-" << 1 + ltm.tm_mon << "-" << ltm.tm_mday;
        matches[i].date = oss.str();

        cout << "\n🎮 " << matches[i].matchID << " → "
            << matches[i].player1.name << " [" << matches[i].score1 << "] vs "
            << matches[i].player2.name << " [" << matches[i].score2 << "] → Winner: "
            << matches[i].winner << " | Date: " << matches[i].date;
    }
}

void exportMatchesToFile(MatchSchedule matches[], int matchCount, const string& filename) {
    ofstream file(filename);
    for (int i = 0; i < matchCount; i++) {
        file << matches[i].matchID << ","
            << matches[i].player1.name << ","
            << matches[i].player2.name << ","
            << matches[i].score1 << ","
            << matches[i].score2 << ","
            << matches[i].winner << ","
            << matches[i].date << "\n";
    }
    file.close();
    cout << "\n📁 Match results exported to " << filename << "\n";
}
void runTask1() {
    PlayerQueue queue;
    MatchSchedule matches[100];
    int matchCount = 0;

    loadPlayersFromFile(queue, "players.txt");

    int option;
    do {
        cout << "\n=== Match Scheduling & Player Progression ===\n";
        cout << "1. Register new player\n";
        cout << "2. View queue\n";
        cout << "3. Schedule matches\n";
        cout << "4. Simulate matches\n";
        cout << "5. Export match results\n";
        cout << "0. Back to main menu\n";
        cout << "Enter choice: ";
        cin >> option;

        switch (option) {
        case 1:
            registerPlayer(queue);
            break;
        case 2:
            queue.displayQueue();
            break;
        case 3:
            scheduleMatches(queue, matches, matchCount);
            break;
        case 4:
            simulateMatches(matches, matchCount);
            break;
        case 5:
            exportMatchesToFile(matches, matchCount, "match_results.csv");
            break;
        case 0:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (option != 0);
}
