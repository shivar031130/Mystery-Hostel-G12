#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include "HorrorGame.h"

using namespace std;

// Main function
int main() {
    HorrorGame game;
    int choice;

    do {
        cout << "---------------------" << endl;
        cout << "\033[1mMystery Hostel Main Menu\033[0m" << endl;
        cout << "---------------------" << endl;
        cout << "\033[32m1. New Game\033[0m" << endl;
        cout << "\033[31m2. Load Game\033[0m" << endl;
        cout << "\033[34m3. Exit\033[0m" << endl;
        cout << "---------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                game.newGame();
                break;
            case 2:
                game.loadGame();
                break;
            case 3:
                cout << "\nExiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);

    return 0;
}
