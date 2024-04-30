// SnakesAndLadder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Die roll (rand % 7)
//Variable to represent turn
//Win function(remove player from game)


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std; 

struct Player {
    string name;
    int *score;
};

void DieRoll() {


        int Roll = 1 + (rand() % 6);
        cout << "You have rolled a: " << Roll << endl;
}

void Win(Player* Player1, Player* Player2, Player* Player3, Player* Player4) {

    vector<Player*> players = { Player1, Player2, Player3, Player4 };
    static vector<Player*> winners; 

    for (vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {

        Player* player = *it;
        if (*player->score == 100) {
            if (find(winners.begin(), winners.end(), player) == winners.end()) { //to check if the player had already won
                winners.push_back(player);
            }
        }
    }

 
    for (int i = 0; i < winners.size(); ++i) {
        cout << "Place " << i + 1 << ": " << winners[i]->name << " with a score of: " << *winners[i]->score << endl; // To print the winners in order
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); //This has to be in the main for the DieRoll to worK correctly

        return 0;
    }

