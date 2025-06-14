#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "skipList.h"
using namespace std;

class GameManager
{
    skipList scoreList; // Skip list to manage scores
    [[nodiscard]] skipNode* wrapperSearch(int playerId) const
    {
        skipNode* current = scoreList.getHead();
        for(int i = scoreList.getLevel() ; i >= 0 ; i--)
        {
            while (current->next[i] != nullptr &&  current->next[i]->key < playerId) {

                current = current->next[i];
            }
        }
        return current->next[0];
    }

public:
    void addPlayer(int playerId, int initialScore = 0);
    // {
    //     if (scoreList.search(playerId)) {
    //         cout << "Player already exists.\n";
    //         return;
    //     }
    //     scoreList.insert(playerId, initialScore);
    //     cout << "Player " << playerId << " added with initial score " << initialScore << ".\n";
    // }

    void removePlayer(int playerId);
    // {
    //     if (!scoreList.search(playerId)) {
    //         cout << "Player not found.\n";
    //         return;
    //     }
    //     scoreList.remove(playerId);
    //     cout << "Player " << playerId << " removed successfully.\n";
    // }

    void updateScore(int playerId, int delta);
    // {
    //     if (!scoreList.search(playerId)) {
    //         cout << "Player not found.\n";
    //         return;
    //     }
    //     // Find current score, remove old entry, and re-insert with updated score
    //     int currentScore = 0;
    //     node* targetNode = wrapperSearch(playerId);
    //         if (targetNode != nullptr && targetNode->key == playerId) {
    //             currentScore = targetNode->value;
    //         }
    //     scoreList.remove(playerId);
    //     int newScore = currentScore + delta;
    //     scoreList.insert(playerId, newScore);
    //     cout << "Player " << playerId << " score updated. New score: " << newScore << "\n";
    // }

    void getTopPlayers(int topN) const;
    // {
    //     cout << "Top " << topN << " Players:\n";
    //     int count = 0;
    //     vector<pair<int, int>> leaderboard; // Store scores and IDs temporarily
    //
    //     node* current = scoreList.getHead()->next[0]; // Start from the lowest level
    //     while (current != nullptr) {
    //         leaderboard.emplace_back(current->value, current->key);
    //         current = current->next[0];
    //     }
    //
    //     // Sort the leaderboard by scores in descending order
    //     sort(leaderboard.rbegin(), leaderboard.rend());
    //
    //     for (const auto& entry : leaderboard) {
    //         if (count >= topN) break;
    //         cout << "Player " << entry.second << ": " << entry.first << "\n";
    //         count++;
    //     }
    // }

    void viewScore(int playerId) const;
    // {
    //     if (!scoreList.search(playerId)) {
    //         cout << "Player not found.\n";
    //         return;
    //     }
    //     node* foundNode = wrapperSearch(playerId);
    //     if ( foundNode != nullptr && foundNode->key == playerId)
    //         cout << "Player " << playerId << " has Score: " << foundNode->value << "\n";
    //
    // }


};




#endif //GAMEMANAGER_H
