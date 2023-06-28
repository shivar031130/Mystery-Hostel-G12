#include "HorrorGame.h"

using namespace std;

HorrorGame::GameState::GameState(int health, bool hasKey, int roomnum) {
    this->health = health;
    this->hasKey = hasKey;
    this->roomnum = roomnum;

    next = nullptr;
}

HorrorGame::HorrorGame() {
    currentState = nullptr;
    head = nullptr;

}

HorrorGame::~HorrorGame() {
    // Clean up the linked list
    GameState* current = head;
    while (current != nullptr) {
        GameState* temp = current;
        current = current->next;
        delete temp;
    }
}

void HorrorGame::newGame() {
    // Clear the linked list
    GameState* current = head;
    while (current != nullptr) {
        GameState* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;

    currentState = new GameState();
    head = currentState;

    playGame();
}

void HorrorGame::loadGame() {
    // Load game state from file
    ifstream file("game_state.txt");
    if (file.is_open()) {
        // Clear the linked list
        GameState* current = head;
        while (current != nullptr) {
            GameState* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;

        int health;
        bool hasKey;
        int roomnum;
        while (file >> health >> hasKey >> roomnum) {
            GameState* newState = new GameState(health, hasKey, roomnum);
            if (head == nullptr) {
                head = newState;
                currentState = head;
            } else {
                currentState->next = newState;
                currentState = currentState->next;
            }
        }

        file.close();
        cout << "Game loaded successfully!" << endl;
        playGame();
    } else {
        cout << "No saved game found." << endl;
    }
}

void HorrorGame::saveGame() {
    // Save game state to file
    ofstream file("game_state.txt");
    if (file.is_open()) {
        GameState* current = head;
        while (current != nullptr) {
            file << current->health << " " << current->hasKey << " "<< current->roomnum << endl;
            current = current->next;
        }
        file.close();
        cout << "\nGame saved successfully!" << endl;
    } else {
        cout << "\nUnable to save the game." << endl;
    }
}

void HorrorGame::playGame() {

    cout << "\033[1m\nYou find yourself trapped in your new hostel room on a stormy night.\033[0m" << endl;
    cout << "\033[1mAs the protagonist, you must navigate through the dark corridors, solving puzzles and uncovering the secrets hidden within the hostel.\033[0m" << endl;
    cout << "\033[1mBeware, for the hostel is haunted and danger lurks in every corner.\033[0m" << endl;

    do {
        cout << "---------------------" << endl;
        cout << "\033[31mCurrent Health: \033[0m" << currentState->health << endl;
        cout << "---------------------" << endl;
        cout << "Choose an action:" << endl;
        cout << "1. Explore the current room" << endl;

        if (hasExploredCurrentRoom) {
            cout << "2. Move to a different room" << endl;
        }

        cout << "3. Save and Quit the game" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
              if(currentState->roomnum==1)
                exploreBedroom();
              else if(currentState->roomnum==2)
                explorePantry();
              else if(currentState->roomnum==3)
                exploreLeisure();
              else if(currentState->roomnum==4)
                exploreExit();

                break;
            case 2:
                if (hasExploredCurrentRoom) {
                    moveRooms();
                } else {
                    cout << "\033[1mYou need to explore the current room first.\033[0m" << endl;
                }
                break;
            case 3:
                saveGame();
                cout << "Exiting the game..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        // Check player's health
        if (currentState->health <= 0) {
            cout << "\033[31mGame over! Your health dropped to zero.\033[0m" << endl;
            return;
        }
    } while (true);
}

void HorrorGame::exploreBedroom() {
        cout << "\033[1m\nYou enter a dimly lit room. Shadows dance on the walls.\033[0m" << endl;
        cout << "\033[1mYou notice a dusty bookshelf in the corner of the room.\033[0m" << endl;
        cout << "1. Examine the bookshelf" << endl;
        cout << "2. Leave the room" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\033[1m\nAs you approach the bookshelf, a gust of wind blows through the room, causing the books to sway.\033[0m" << endl;
                cout << "\033[1mYou notice a book that stands out from the rest. It appears to be partially hidden.\033[0m" << endl;
                cout << "1. Take the book" << endl;
                cout << "2. Leave the bookshelf" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    cout << "\033[1m\nYou carefully pull out the hidden book from the shelf. It's a journal with cryptic writings.\033[0m" << endl;
                    solvePuzzle();
                } else {
                    cout << "\033[1m\nYou decide to leave the bookshelf and continue exploring the room.\033[0m" << endl;
                }
                break;
            case 2:
                cout << "\033[1m\nYou leave the room and continue your exploration of the haunted hostel.\033[0m" << endl;
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    }


   void HorrorGame::moveRooms() {

    cout << "\033[1m\nYou cautiously navigate through the dark corridors of the hostel.\033[0m" << endl;
    cout << "\033[1mThe sound of your footsteps echoes eerily.\033[0m" << endl;
    cout << "\033[1mYou come across a fork in the path. One way leads to the east wing, while the other leads to the west wing.\033[0m" << endl;
    cout << "1. Take the path to the east wing" << endl;
    cout << "2. Take the path to the west wing" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    string answer1;
    switch (choice) {
        case 1:
            explorePantry();
            break;
        case 2:
            int choose1;

            cout << "\033[1m\nYou enter the west wing, where an eerie silence hangs in the air.\033[0m" << endl;
            cout << "\033[1mThere is two room along the wing.\033[0m"<<endl;
            cout << "\033[1mOne with a red door and another with a black door.\033[0m"<<endl;
            cout << "Choose one room to enter (Press 1 for red door or 2 for black door) : ";
            cin >> choose1;

            if(choose1 == 1)

            {
              if(hasExploredPantry==true)
              {
              exploreLeisure();
              hasExploredLeisure= true;
              exploreExit();
              }

              else
              {
                currentState->health-=10;
                if((currentState->health)<0)
                cout<<"\033[31mCurrent Health: 0\033[0m"<<endl;
                else
                cout << "\033[31mCurrent Health: \033[0m" << currentState->health << endl;
                cout << "---------------------" << endl;
                cout<<"\033[31mYou entered the wrong room. Read the previous hint carefully. \033[0m"<<endl;
                if((currentState->health)<0)
                break;
              }
            }
            else if (choose1 == 2)
            {
              if(hasExploredPantry==true && hasExploredLeisure==true)
              {
              exploreLeisure();
              hasExploredLeisure= true;
              exploreExit();
              }

              else
              {
                currentState->health-=10;
                if((currentState->health)<0)
                cout<<"\033[31mCurrent Health: 0\033[0m"<<endl;
                else
                cout << "\033[31mCurrent Health: \033[0m" << currentState->health << endl;
                cout << "---------------------" << endl;
                cout<<"\033[31mYou entered the wrong room. Read the previous hint carefully. \033[0m"<<endl;
                if((currentState->health)<0)
                break;
              }
            }
            else
            {
              cout << "Invalid choice. Try again. ";
              cin >> choose1;
            }

     break;

        default:
            cout << "Invalid choice. Please try again." << endl;
    }
            }

void HorrorGame::solvePuzzle() {
        cout << "\033[1m\nAs you examine the journal, you notice a strange inscription on the last page.\033[0m" << endl;
        cout << "\033[1mIt reads: 'To proceed, you must find the missing pieces and restore what was broken.'\033[0m" << endl;
        cout << "\033[1mYou look around the room and notice a shattered mirror on the floor.\033[0m" << endl;
        cout << "1. Examine the shattered mirror" << endl;
        cout << "2. Leave the mirror" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "\033[1m\nYou carefully pick up the broken pieces of the mirror.\033[0m" << endl;
            cout << "1. Attempt to restore the mirror" << endl;
            cout << "2. Leave the mirror and continue exploring" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                hasExploredCurrentRoom = true;
                cout << "\033[1m\nYou spend some time meticulously piecing together the fragments of the mirror.\033[0m" << endl;
                cout << "\033[1mAs you place the final piece, the mirror magically repairs itself and reveals a hidden compartment behind it.\033[0m" << endl;
                cout << "\033[1m\nInside the compartment, you find an old note saying 'Beyond the path veiled by obscurity, where the shadows deepen and the air \033[0m"<<endl;
                cout<<"\033[1mgrows dense, lies the gateway to your next trial. In the realm where the sun's first light awakens, \033[0m"<<endl;
                cout<<"\033[1mwhere the rays of dawn creep upon the land of nightmares, awaits the doorway you seek. \033[0m"<<endl;
                cout<<"\033[1mTraverse towards the realm of daybreak, for there, the secrets yearn to be discovered. \033[0m"<<endl;
                cout<<"\033[1mBut tread carefully, for what you find may haunt your every step, forevermore.' \033[0m"<< endl;
            } else {
                cout << "\033[1m\nYou decide to leave the mirror and its broken pieces behind, uncertain of its significance. \033[0m" << endl;
            }
        } else {
            cout << "\033[1mYou choose to leave the shattered mirror and continue exploring the room.\033[0m" << endl;
        }
    }

void HorrorGame::explorePantry() {

    currentState->roomnum=2;

            cout << "\033[1m\nYou enter the east wing, guided by a flickering light at the end of the corridor. \033[0m" << endl;
            cout << "\033[1mAs you explore further, you find yourself in an old pantry. \033[0m" << endl;
            cout << "\033[1mThe room is filled with shelves lined with dusty jars and containers. \033[0m" << endl;
            cout << "\033[1mYou notice a kettle placed on the table.\033[0m" << endl;
            cout << "1. Examine the kettle" << endl;
            cout << "2. Leave the pantry" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                cout << "\033[1m\nYou take a closer look at the kettle and discover a combination lock on its lid.\033[0m" << endl;
                cout << "\033[1mTo open the kettle, you need to solve the combination puzzle.\033[0m" << endl;
                cout << "\033[1mThe lock has three dials labeled A, B, and C.\033[0m" << endl;
                cout << "\033[1mEach dial has numbers from 0 to 9.\033[0m" << endl;

                bool puzzleSolved = false;
                int attempts = 0;

                while (!puzzleSolved) {
                    attempts++;
                    cout << "\nAttempt #" << attempts << endl;
                    cout << "\033[1mRiddle A --> If you divide twelve by half, and add one, what do you get?\033[0m" << endl;
                    cout << "Enter the combination for dial A: ";
                    cin >> choice;
                    int combinationA = choice;
                    cout << "\033[1mRiddle B --> If you multiply this number by any other number, the answer will always be the same. What number is this?\033[0m" << endl;
                    cout << "Enter the combination for dial B: ";
                    cin >> choice;
                    int combinationB = choice;
                    cout << "\033[1mRiddle C --> A boy blows 18 bubbles, then pops 6 eats 7, and then he pops 5 and blows 1. How many are left?\033[0m" << endl;
                    cout << "Enter the combination for dial C: ";
                    cin >> choice;
                    int combinationC = choice;

                    // Check if the combination is correct
                    if (combinationA == 7 && combinationB == 0 && combinationC == 1) {
                        hasExploredPantry = true;
                        cout << "\033[1m\nYou hear a click as you correctly set the combination.\033[0m" << endl;
                        cout << "\033[1mExcitedly, you open the kettle, expecting to find the key.\033[0m" << endl;
                        cout << "\033[1mHowever, as you open the kettle, a message with fright-filled red font pops up inside it.\033[0m" << endl;
                        cout << "\033[1mIt reads: 'Congratulations! You have been tricked. No key is placed here.'\033[0m" << endl;

                        currentState->health -= 10 * attempts; // Reduce player's health as a penalty for attempting the puzzle
                        puzzleSolved = true;
                    } else {
                        cout << "\033[1m\nYou turn the dials but the lock doesn't budge.\033[0m" << endl;
                        cout << "\033[1mThe combination seems to be incorrect.\033[0m" << endl;
                        currentState->health -= 5 * attempts; // Reduce player's health for failing to solve the puzzle
                        cout << "\n---------------------" << endl;
                        if((currentState->health)<0)
                        cout<<"\033[31mCurrent Health: 0\033[0m"<<endl;
                        else
                        cout << "\033[31mCurrent Health: \033[0m" << currentState->health << endl;
                        cout << "---------------------" << endl;
                        if((currentState->health)<0)
                        break;
                    }
                }
            }
            else {
                cout << "\033[1m\nYou decide to leave the pantry and continue exploring the east wing.\033[0m" << endl;
}
}

void HorrorGame::exploreLeisure() {

    currentState->roomnum=3;

    // Define the Room struct
    struct Room {
        string description;
        bool puzzleSolved;
    };

    Room currentRoom;
    currentRoom.description = "\033[1mYou are trapped in a room. There is a locked door in front of you.\033[0m";

    currentRoom.puzzleSolved = false;
    string choice2;
    int numattempts = 0;

    cout << currentRoom.description << endl;
    cout << "\033[1mThe chains, tarnished and rusted, hold the door captive, their gnarled forms snaking around it like serpents in an unholy embrace.\033[0m"<< endl;
    cout << "\033[1mThey seem to pulsate with malevolence, as if fueled by the tormented souls that once dared to challenge the horrors within.\033[0m" << endl;

    while (!currentRoom.puzzleSolved) {
        cout << "\033[1m\nYou search the room and find a small table with three objects on it: a key, a notebook, and a candle.\033[0m" << endl;
        cout << "Which one do you want to interact? Enter your choice: ";
        string choice;
        cin >> choice;

        if (choice == "key" || choice == "Key") {
            cout << "\033[1m\nYou take the key from the table.\033[0m" << endl;
            cout << "\033[31mBut it's just a dummy and not the real exit door key. Try again. \033[0m" << endl;
        } else if (choice == "notebook" || choice == "Notebook") {
            cout << "\033[1m\nYou open the notebook and find a riddle written on one of the pages.\033[0m" << endl;
            cout << "\033[1mRiddle: What goes up but never comes down? \033[0m" << endl;
            cout << "\nEnter your answer : ";
            cin >> choice2;
            while(choice2 != "age" && choice2 != "Age"){
                cout << "\nTry again. Enter your answer : ";
                cin >> choice2;
                numattempts++;      }
            if(choice2 == "Age" || choice2 == "age")
               currentRoom.puzzleSolved = true;
        } else if (choice == "candle" || choice == "Candle") {
            cout << "\033[1m\nYou light the candle and it illuminates the room, revealing a hidden message on the wall.\033[0m" << endl;
            cout << "\033[1mThe message reads: 'The answer lies within the riddle.' Try again. \033[0m" << endl;
        } else if (choice == "quit") {
            cout << "\033[31m\nYou give up and quit the game. Game over!\033[0m" << endl;
            return;
        } else {
            cout << "\033[31m\nInvalid choice. Please try again.\033[0m" << endl;
        }
    }
        cout << "\033[1m\nYou think for a moment and realize that the answer to the riddle is 'age'.\033[0m" << endl;
        cout << "\033[1mYou say the word 'age' out loud, and suddenly, a mysterious voice shouts, 'Get out from here!'. \033[0m" << endl;
        currentState->health -= 5 * numattempts;
        cout << "\n\033[31mCurrent Health: \033[0m" << currentState->health << endl;
  }

void HorrorGame::exploreExit() {

    currentState->roomnum=4;

      string answer1;
      cout <<"\033[1m\nWith a jarring screech, the chains come alive, writhing and contorting as if possessed by unseen horrors.\033[0m"<<endl;
      cout <<"\033[1mThe door, liberated from their grip, creaks open with a chilling gust of wind, revealing the abyss of terror that lies beyond.\033[0m"<<endl;
      cout << "\033[1m\nYou enter a through the opened door and notice a mysterious riddle written on the wall.\033[0m" << endl;
      cout << "\033[1mSolving the riddle might unlock a hidden passage.\033[0m" << endl;
      cout << "\033[1m\nHere's the riddle:\033[0m" << endl;
      cout << "\033[1mI am an odd number. Take away one letter, and I become even. What number am I?\033[0m" << endl;
      cout << "\nEnter your answer: ";
      cin >> answer1;

    if (answer1 == "seven") {
        cout << "\033[1m\nCongratulations! You have solved the riddle and unlocked a hidden passage.\033[0m" << endl;
        cout << "\033[1mYou enter the passage and find a valuable item.\033[0m" << endl;
        cout << "\033[1mYou have found the key and the door to be unlocked. Congrats you survived this haunted hostel game.\033[0m";
    } else {
        cout << "\033[31m\nThe riddle stumps you, and you are unable to unlock the hidden passage.\033[0m" << endl;
        cout << "\033[31mYou feel a sudden chill, and a mysterious force drains your life energy. Game over.\033[0m" << endl;
        currentState->health =0;
    }
}
