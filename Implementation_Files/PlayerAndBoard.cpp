#include "PlayerAndBoard.h"
int PlayerAndBoard::die_roll() {
	return 1 + (rand() % 6);
}


void PlayerAndBoard::create_players(player* players, int num, AnimAndColour effects) {
	for (int i = 0; i < num; i++) {
		effects.changeColour(effects.YELLOW);
		cout << "Enter name of player " << i + 1 << ": ";
		effects.changeColour(effects.LightPurple);
		cin >> players[i].name;
		effects.changeColour(effects.YELLOW);
		cout << "What color would player " << players[i].name << " like to be:" << endl;
		cout << "Here is the list of colours (Pick the number equivalent to it): " << endl;
		effects.changeColour(effects.BLUE);
		cout << "BLUE = 1" << endl;
		effects.changeColour(effects.GREEN);
		cout << "GREEN = 2" << endl;
		effects.changeColour(effects.RED);
		cout << "RED = 4" << endl;
		effects.changeColour(effects.PURPLE);
		cout << "PURPLE = 5" << endl;
		effects.changeColour(effects.YELLOW);
		cout << "YELLOW = 6" << endl;
		effects.changeColour(effects.WHITE);
		cout << "WHITE = 15" << endl;
		effects.changeColour(effects.LightPurple);
		cin >> players[i].color;

	}
	effects.changeColour(effects.WHITE);
}

void PlayerAndBoard::display_players(player* players, int num) {
	for (int i = 0; i < num; i++) {
		cout << endl;
		cout << "PLAYER " << i << endl;
		cout << "Name: " << players[i].name << endl;
		cout << "Score: " << players[i].score << endl << endl;
	}
}

void PlayerAndBoard::move_player(player* players, int turn, int roll, int& wins, Graph& g, int num, vector<player>& winners, AnimAndColour effects) {
	effects.changeColour(effects.WHITE);
	if (players[turn].score + roll > 100) {
		effects.changeColour(effects.RED);
		cout << players[turn].name << "'s score has exceeded 100." << endl << "Their turn will be skipped." << endl;
	}
	else {
		effects.changeColour(effects.LightBlue);
		players[turn].score += roll;
		for (int i = 0; i < num; i++) {
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << players[i].name << "'s score is: " << players[i].score << endl;
		}
		int prev = players[turn].score; // Store the previous score
		players[turn].score = g.getDest(players[turn].score);
		effects.changeColour(effects.WHITE);

		if (prev != players[turn].score) {
			effects.changeColour(effects.LightPurple);
			string s = (prev < players[turn].score) ? "ladder" : "snake";

			cout << endl << players[turn].name << " landed on a " << s << "! \nTheir score is now " << players[turn].score << ".\n\n";
		}
	}


	if (players[turn].score == 100) {
		players[turn].win = 1;
		wins++;
		winners.push_back(players[turn]);
		effects.changeColour(effects.LightYellow);
		cout << players[turn].name << " has won!" << endl << endl;
	}
	effects.changeColour(effects.WHITE);
}
void PlayerAndBoard::display_board(player* players, int num, int c1, int c2, AnimAndColour& effects) {
	char l_top[5] = { char(218),'_','_',char(191) };
	char l_bottom[5] = { char(195),'^','^',char(180) };


	string s_head, s_tail;

	s_head = "~__~";
	s_tail = "<---";


	string board[10][10];
	int row[10]; // Array to store the rows of all players
	int col[10]; // Array to store the columns of all players
	effects.changeColour(effects.WHITE);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int pos;
			ostringstream temp;
			string square;

			if (i % 2 == 0) {
				pos = 100 - 10 * i - j;
				temp << pos;
				square = temp.str();
			}
			else {
				pos = 100 - 10 * i - (9 - j);
				temp << pos;
				square = temp.str();
			}

			board[i][j] = "|" + square + "|";
		}
	}

	board[8][6] = board[6][9] = board[6][2] = board[5][1] = board[3][6] = board[1][3] = board[0][9] = board[0][1] = l_top; // Ladder tops
	board[9][0] = board[9][3] = board[9][8] = board[7][0] = board[7][7] = board[4][9] = board[2][0] = board[2][8] = l_bottom; // Ladder bottoms

	board[8][3] = board[4][6] = board[3][1] = board[3][3] = board[1][6] = board[0][7] = board[0][5] = board[0][2] = s_head; // Snake heads
	board[9][6] = board[8][1] = board[6][4] = board[6][6] = board[4][0] = board[2][1] = board[2][5] = board[2][7] = s_tail; // Snake tails

	for (int i = 0; i < num; i++) {
		int score = players[i].score;
		if (score > 0) {
			row[i] = 9 - (score - 1) / 10;
			col[i] = (score - 1) % 10;
			if (row[i] % 2 == 0) {
				col[i] = 9 - col[i];
			}
			board[row[i]][col[i]] = "|" + players[i].name + "|";
		}
	}

	for (int i = 0; i < 10; i++) {
		cout << "\t\t\t\t\t\t";
		for (int j = 0; j < 10; j++) {
			bool isPlayerPosition = false;
			int playerColor = effects.WHITE; // Default color
			for (int k = 0; k < num; k++) {
				if (i == row[k] && j == col[k]) {
					isPlayerPosition = true;
					playerColor = players[k].color; // Use the player's color
					break;
				}
			}
			if (isPlayerPosition) {
				effects.changeColour(playerColor);
			}
			else if ((i + j) % 2 == 1) {
				effects.changeColour(c1);
			}
			else {
				effects.changeColour(c2);
			}
			cout << board[i][j];
		}
		cout << endl;
	}
	effects.changeColour(effects.WHITE);
}
