 #include <iostream>
#include"gameManager.h"
using namespace std;


int main()
{
    GameManager g;
    for (int i = 0 ; i < 10 ; i++)
        g.addPlayer(rand());
    g.addPlayer(20, 0);
    cout << "******************************\n";

    g.updateScore(20, 10);
    g.updateScore(20, 50);
    g.updateScore(41, 80);
    g.updateScore(26962, 180);
    g.updateScore(29358, -20);
    g.updateScore(26962, -50);
    g.updateScore(26962, 20);
    cout << "******************************\n";
    g.viewScore(20);
    g.viewScore(26962);
    cout << "******************************\n";
    cout << "******************************\n";
    g.getTopPlayers(5);
    cout << "******************************\n";
    cout << "******************************\n";
    g.removePlayer(20);
    g.removePlayer(41);
    g.removePlayer(6334);
    g.removePlayer(29358);
    g.removePlayer(11478);
    g.removePlayer(20);
    return 0;
}