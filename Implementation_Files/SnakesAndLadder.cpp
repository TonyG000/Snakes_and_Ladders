#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include "Graph.h"
#include "AnimAndColour.h"
#include "PlayerAndBoard.h"

using namespace std;

int main() {
	srand(static_cast<unsigned int>(time(0)));
	string Answer;
	string plays;
	AnimAndColour effects;
	Graph g;
	PlayerAndBoard Design;
	do {
		/*for (int i = 0; i < 5; i++) {
			bool music = PlaySound(L"game-music-teste-204327.wav", NULL, SND_ASYNC);
		}*/ //Music has been commented out since it could cause an error unless "winmm.lib" is manually added as an input in the linker
		effects.showBlinkingLights();
		int num = 0;
		effects.changeColour(effects.AQUA);
		cout << "Would you like to play? (Enter yes or no) " << endl;
		effects.changeColour(effects.LightPurple);
		cin >> plays;
		Sleep(1000);
		if (plays == "Yes" || plays == "yes") {
			effects.changeColour(effects.PURPLE);
			cout << "Here are the rules of the game!" << endl;
			effects.changeColour(effects.LightGreen);
			cout << "1. The game will continue until all players have reached a score of 100!" << endl;
			cout << "2. If you reach a ladder, you'll move upwards! :)" << endl;
			cout << "3. If you reach a snake, you'll move back down! :(" << endl;
			cout << "4. Have lots of fun and Enjoy!" << endl;

			effects.changeColour(effects.AQUA);
			cout << "How many players would you like to register? ";
			Sleep(500);
			effects.changeColour(effects.LightPurple);
			cin >> num;
			player *pls = new player[num];
			vector<player> winners;
			Design.create_players(pls, num, effects);

			int turn = 0;
			int roll = 0;
			int wins = 0;
			string c;

	
			int c1, c2;

			effects.changeColour(effects.AQUA);

			cout << "\nSelect 2 different colors for the board to be displayed in. Colors available: " << endl;
			effects.changeColour(effects.BLUE);
			cout << "BLUE = 1" << endl;
			effects.changeColour(effects.GREEN);
			cout << "GREEN = 2" << endl;
			effects.changeColour(effects.AQUA);
			cout << "AQUA = 3" << endl;
			effects.changeColour(effects.RED);
			cout << "RED = 4" << endl;
			effects.changeColour(effects.PURPLE);
			cout << "PURPLE = 5" << endl;
			effects.changeColour(effects.YELLOW);
			cout << "YELLOW = 6" << endl;
			effects.changeColour(effects.LightBlue);
			cout << "Light Blue = 9" << endl;
			effects.changeColour(effects.LightGreen);
			cout << "Light Green = 10 " << endl;
			effects.changeColour(effects.LightPurple);
			cout << "Light Purple = 13" << endl;
			effects.changeColour(effects.WHITE);
			cout << "WHITE = 15" << endl;
			effects.changeColour(effects.LightPurple);
			cin >> c1 >> c2;
			cout << endl;

			char l_top[5] = { char(218),'_','_',char(191) };
			char l_bottom[5] = { char(195),'^','^',char(180) };


			effects.changeColour(effects.WHITE);

			string s_head, s_tail;

			s_head = "~__~";
			s_tail = "<---";

			cout << "\t\t\t\t\t\t\t" << "Ladder top: " << l_top << endl << endl;
			cout << "\t\t\t\t\t\t\t" << "Ladder bottom: " << l_bottom << endl << endl;

			cout << "\t\t\t\t\t\t\t" << "Snake head: " << s_head << endl << endl;
			cout << "\t\t\t\t\t\t\t" << "Snake tail: " << s_tail << endl << endl;
			while (wins < num) {
				if (pls[turn].win == 1) {
					turn = ++turn % num;
					continue;
				}

				else {
					effects.changeColour(effects.GREEN);
					cout << endl << "It is now " << pls[turn].name << "'s turn to roll." << endl;
					effects.changeColour(effects.RED);
						cout << "Press enter to roll the dice. \n\n";
						cin.ignore();
					roll = Design.die_roll();
					effects.changeColour(effects.PURPLE);
					cout << "\t\t\t\t\t\t\t\t" << pls[turn].name << " rolled a " << roll << "." << endl;
					Design.move_player(pls, turn, roll, wins, g, num, winners, effects);
					Design.display_board(pls, num, c1, c2, effects);
					turn = ++turn % num;
				}

			}
			effects.changeColour(effects.LightYellow);
			cout << "Scoreboard:" << endl;
			for (int i = 0; i < winners.size(); i++) {
				cout << "Place " << i + 1 << ": " << winners[i].name << endl;
			}
			effects.changeColour(effects.RED);
			cout << "Would you like to play again? (Enter Yes or No): " << endl;
			cin >> Answer;
		}
		else {

			effects.changeColour(effects.PURPLE);
			cout << "Hope you can play next time! " << endl;
			Sleep(1000); 
			return 0;
		}
		effects.changeColour(effects.WHITE);
	} while (((Answer == "Yes" && Answer != "No") || (Answer == "yes" && Answer != "no")));
	return 0;
}


