#include "gameManager.h"
#include<iostream>
#include<algorithm>
#include "../include/skipList.h"
#include<queue>

void GameManager::addPlayer(int playerId, int initialScore) {
    if (scoreList.search(playerId)) {
        cout << "Player already exists.\n";
        return;
    }
    scoreList.insert(playerId, initialScore);
    cout << "Player " << playerId << " added with initial score " << initialScore << ".\n";
}
void GameManager::removePlayer(int playerId) {
    if (!scoreList.search(playerId)) {
        cout << "Player not found.\n";
        return;
    }
    scoreList.remove(playerId);
    cout << "Player " << playerId << " removed successfully.\n";
}
void GameManager::updateScore(int playerId, int delta) {
    if (!scoreList.search(playerId)) {
        cout << "Player not found.\n";
        return;
    }
    // Find current score, remove old entry, and re-insert with updated score
    int currentScore = 0;
    skipNode* targetNode = wrapperSearch(playerId);
    if (targetNode != nullptr && targetNode->key == playerId) {
        currentScore = targetNode->value;
    }
    int newScore = currentScore + delta;
    scoreList.insert(playerId, newScore);
    cout << "Player " << playerId << " score updated. New score: " << newScore << "\n";
}
void GameManager::getTopPlayers(int topN) const
{
    cout << "Top " << topN << " Players:\n";
    int count = 0;
    vector<pair<int, int>> topPlayers; // Store scores and IDs temporarily

    skipNode* current = scoreList.getHead()->next[0]; // Start from the lowest level
    while (current != nullptr) {
        topPlayers.emplace_back(current->value, current->key);
        current = current->next[0];
    }

    // Sort the topPlayers by scores in descending order
    sort(topPlayers.rbegin(), topPlayers.rend());

    for (const auto& entry : topPlayers) {
        if (count >= topN) break;
        cout << "Player " << entry.second << ": " << entry.first << "\n";
        count++;
    }

}
void GameManager::viewScore(int playerId) const
{
    if (!scoreList.search(playerId)) {
        cout << "Player not found.\n";
        return;
    }
    skipNode* foundNode = wrapperSearch(playerId);
    if ( foundNode != nullptr && foundNode->key == playerId)
        cout << "Player " << playerId << " has Score: " << foundNode->value << "\n";

}

