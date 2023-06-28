#ifndef HORROR_GAME_H
#define HORROR_GAME_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

class HorrorGame {
private:
    bool hasExploredCurrentRoom = false;
    bool hasExploredPantry=false;
    bool hasExploredLeisure=false;
    struct GameState {
        int health;
        bool hasKey;
        int roomnum;
        GameState* next;

        GameState(int health = 100, bool hasKey = false, int roomnum = 1);
    };
    GameState* currentState;
    GameState* head;

public:
    HorrorGame();
    ~HorrorGame();
    void newGame();
    void loadGame();
    void saveGame();
    void playGame();
    void moveRooms();
    void solvePuzzle();
    void exploreBedroom();
    void explorePantry();
    void exploreLeisure();
    void exploreExit();
};

#endif  // HORROR_GAME_H
