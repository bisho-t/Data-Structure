#include "skipList.h"


skipList::skipList(): generator (random_device{}()), distribution(0, 1)
{
    this->level = 0;
    this->size = 0;
    this->head = new skipNode(INT_MIN, INT_MIN,  5);

}
skipList::~skipList()
{
    skipNode* current = head;
    while (current)
    {
        skipNode* nextNode = current->next[0];
        delete current;
        current = nextNode;
    }
}
void skipList::insert(int comparableKey, int value)
{
    if (search(comparableKey))
    {
        skipNode* current = head;
        for (int i = level ; i >= 0 ; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->key < comparableKey )
            {
                current = current->next[i];
            }
        }
        current = current->next[0];
        current->value = value;
        return;

    }
    size++;
    int levelsOccupied = 0;
    int randomValue;
    int maxNumberOfLevels = ceil(log2(size)); // Calculate max levels dynamically based on size
    while (levelsOccupied < max(maxNumberOfLevels, 1) - 1 &&
           (randomValue = distribution(generator), randomValue % 2 == 1))
    {
        levelsOccupied++;
    }
    // cout << levelsOccupied << endl;

    if (level < levelsOccupied)
    {
        head->next.resize( levelsOccupied + 1 , nullptr);
        level = levelsOccupied;
    }

    vector<skipNode*> update(levelsOccupied + 1, nullptr);
    skipNode* current = head;
    for (int i = levelsOccupied ; i >=0 ; i--)
    {
        while (current->next[i] != nullptr && current->next[i]->key < comparableKey)
        {
            current = current->next[i];
        }
        update[i] = current;
    }
    auto* newNode = new skipNode(comparableKey, value, levelsOccupied + 1);
    for (int i = 0 ; i <= levelsOccupied ;i++)
    {
        newNode->next[i] = update[i]->next[i];
        update[i]->next[i] = newNode;
    }
}
skipNode* skipList::getHead() const
{
    return head;
}
bool skipList::search(const int key) const
{
    skipNode* current = head;
    for (int i = level ; i >= 0 ; i--)
    {
        while (current->next[i] != nullptr && current->next[i]->key < key )
        {
            current = current->next[i];
        }
    }
    current = current->next[0];

    return current != nullptr && current->key == key;
}
void skipList:: remove (int key)
{
    if (!search(key))
    {
        cout << "Element doesn't exist" << endl;
        return;
    }
    vector<skipNode*> update(level + 1, nullptr);
    skipNode* current = head;
    for(int i = level ; i >= 0 ; i--)
    {
        while (current->next[i] != nullptr && current->next[i]->key < key)
            current = current->next[i];
        update[i] = current;
    }

    current = current->next[0];     // Move to the actual node to be removed
    if (current != nullptr && current->key == key){
        for (int i = 0 ; i <= level ; i++)
        {
            if (update[i]->next[i] != current)
                break;
            update[i]->next[i] = current->next[i];
        }
    }
    size--;
    delete current;
    while (level > 0 &&  head->next[level] == nullptr)
        level--;
    // cout << "element deleted successfully" << endl;
}
void skipList::display() const
{
    skipNode* current = head->next[0];
    while (current != nullptr)
    {
        cout << current->key << " " << current->value << endl;
        current = current->next[0];
    }
}
int skipList::getLevel()  const
{
    return level;
}