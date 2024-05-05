#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <Windows.h>
#include <iterator>
#include <sstream>
#include <cstring>
#include <bitset>

const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int WHITE = 15;
const int YELLOW = 6;
const int PURPLE = 5;
const int AQUA = 3;
const int LightPurple = 13;
const int LightBlue = 9;
const int LightGeen = 10;
using namespace std;

struct player {
	string name = "";
	int score = 0;
	bool win = 0;
};

class Graph {
	vector<pair<int, int> > adj[101];

public:
	Graph() {
		// Ladders
		addEdge(1, 38, 1);
		addEdge(4, 14, 1);
		addEdge(9, 31, 1);
		addEdge(21, 42, 1);
		addEdge(28, 84, 1);
		addEdge(51, 67, 1);
		addEdge(72, 91, 1);
		addEdge(80, 99, 1);

		// Snakes
		addEdge(17, 7, 1);
		addEdge(54, 34, 1);
		addEdge(62, 19, 1);
		addEdge(64, 60, 1);
		addEdge(87, 36, 1);
		addEdge(93, 73, 1);
		addEdge(95, 75, 1);
		addEdge(98, 79, 1);
	}

	void addEdge(int u, int v, int wt) {
		adj[u].push_back(make_pair(v, wt));
		adj[v].push_back(make_pair(u, wt)); //reference GeeksforGeeks
	}
	int getDest(int score) {
		int v, w;
		
		for (vector<pair<int,int> >:: iterator it = adj[score].begin(); it!= adj[score].end(); it++) {
			v = it->first;
			w = it->second;
			if (isLadder(score) || isSnake(score)) {
				return v; // Return the destination of the second edge
			}
		}
		return score;
	}

	bool isLadder(int node) {
		// Check if the node is the starting node of a ladder
		return (node == 1 || node == 4 || node == 9 || node == 21 || node == 28 || node == 51 || node == 72 || node == 80);
	}
	bool isSnake(int node) {
		return (node == 17 || node == 54 || node == 62 || node == 64 || node == 87 || node == 93 || node == 95 || node == 98);
	}
};

int die_roll() {
	return 1 + (rand() % 6);
}

void changeColour(int colour) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}

void create_players(player *players, int num) {
	for (int i = 0; i < num; i++) {
		changeColour(YELLOW);
		cout << "Enter name of player " << i+1 << ": ";
		changeColour(LightPurple);
		cin >> players[i].name;
	}
}

void display_players(player *players, int num) {
	for (int i = 0; i < num; i++) {
		cout << endl;
		cout << "PLAYER " << i << endl;
		cout << "Name: " << players[i].name << endl;
		cout << "Score: " << players[i].score << endl << endl;
	}
}

void move_player(player *players, int turn, int roll, int& wins, Graph& g, int num) {
	changeColour(WHITE);
	if (players[turn].score + roll > 100) {
		changeColour(RED);
		cout << players[turn].name << "'s score has exceeded 100." << endl << "Their turn will be skipped." << endl;
	}
	else {
		changeColour(LightBlue);
		players[turn].score += roll;
		for (int i = 0; i < num; i++) {
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t" << players[i].name << "'s score is: " << players[i].score << endl;
		}
		int prev = players[turn].score; // Store the previous score
		players[turn].score = g.getDest(players[turn].score);
		changeColour(WHITE);

		if (prev != players[turn].score) {
			changeColour(LightPurple);
			string s = (prev < players[turn].score) ? "ladder" : "snake";

			cout << endl << players[turn].name << " landed on a " << s << "! \nTheir score is now " << players[turn].score << ".\n\n";
		}
	}


	if (players[turn].score == 100) {
		players[turn].win = 1;
		wins++;
		cout << players[turn].name << " has won!" << endl << endl;
	}

}


void display_board(player *players, int num, int c1, int c2) { //might need to be changed but just a general idea to show how the output should look like :)
	char l_top[4] = {char(218),'_','_',char(191)};	
	char l_bottom[4] = {char(195),'^','^',char(180)};

	
	string s_head, s_tail;
	
	s_head = "~__~";
	s_tail = "<---";
	
	
	string board[10][10];
	changeColour(WHITE);

//	Ladder tops: [1][6], [3][9], [3][2], [4][1], [6][6], [8][3], [9][9], [9][1], 
//	Ladder bottoms: [0][0], [0][3], [0][8], [2][0], [2][7], [5][9], [7][0], [7][8], 
//		
//	Snake heads: [1][3], [5][6], [6][1], [6][3], [8][6], [9][7], [9][5], [9][2], 
//	Snake tails: [0][6], [1][1], [3][4], [3][6], [5][0], [7][1], [7][5], [7][7], 

	for (int i = 0; i < num; i++) {
		int score = players[i].score;
		if (score > 0) {
			int row = 9 - (score - 1) / 10;
			int col = (score - 1) % 10;
			if (row % 2 == 0) {
				col = 9 - col;
			}
			
	for(int i=0;i<10;i++){	// Display numbers on board
		for(int j=0;j<10;j++){

			int pos;
			ostringstream temp;
			string square;
			
			if(i%2 == 0){
				pos = 100 - 10*i - j;
				temp << pos;
				square = temp.str();
			}
			else{
				pos = 100 - 10*i - (9 - j);
				temp << pos;
				square = temp.str();
			}
			
			board[i][j] = "|" + square + "|";
		}
	}
			
			
			board[row][col] = "|" + players[i].name + "|";
		}
	}
	
	board[8][6] = board[6][9] = board[6][2] = board[5][1] = board[3][6] = board[1][3] = board[0][9] = board[0][1] = l_top; // Ladder tops
	board[9][0] = board[9][3] = board[9][8] = board[7][0] = board[7][7] = board[4][9] = board[2][0] = board[2][8] = l_bottom; // Ladder bottoms

	board[8][3] = board[4][6] = board[3][1] = board[3][3] = board[1][6] = board[0][7] = board[0][5] = board[0][2] = s_head; // Snake heads
	board[9][6] = board[8][1] = board[6][4] = board[6][6] = board[4][0] = board[2][1] = board[2][5] = board[2][7] = s_tail; // Snake tails

	
	for (int i = 0; i < 10; i++) {
		cout << "\t\t\t\t\t\t";
		for (int j = 0; j < 10; j++) {
			if ((i + j) % 2 == 1){
				changeColour(c1);
			cout << board[i][j];
		}
			else {
				changeColour(c2);
				cout << board[i][j];
			}
		}
		cout << endl;
	}
}

void clearScreen(int characterLength) {
	for (int i = 0; i < characterLength; i++) {
		cout << "\b";
	}
}


void showLoadingScreen() {
	cout << "\t\t\t\t\t\t\t";
	int i;
	string closed = "_ _ _", open = "* * *";
	int colour[] = {RED, GREEN, BLUE };
	cout << closed;
	for (i = 0; i < 3; i++) {
		Sleep(500);
		clearScreen(5);
		changeColour(colour[i]);
		cout << open;
		Sleep(500);
		clearScreen(5);
		changeColour(WHITE);
		cout << closed;
	}
	clearScreen(5);
	changeColour(WHITE);
}
void showBlinkingLights() {
	showLoadingScreen();
	changeColour(RED);
	cout << "WELCOME TO";
	Sleep(500);

	changeColour(GREEN);
	cout << " SNAKES";
	Sleep(500);
	changeColour(YELLOW);
	cout << " AND";
	Sleep(500);

	changeColour(BLUE);
	cout << " LADDERS";
	Sleep(500);

	changeColour(PURPLE);
	cout << "!\t\t\t\t\t" << endl;
	Sleep(500);
	changeColour(WHITE);
}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	string Answer;
	string plays;
	do {
		showBlinkingLights();
		int num = 0;
		changeColour(AQUA);
		cout << "Would you like to play? (Enter yes or no) " << endl;
		changeColour(LightPurple);
		cin >> plays;
		Sleep(1000);
		if (plays == "Yes" || plays == "yes") {
			changeColour(AQUA);
			cout << "How many players would you like to register? ";
			Sleep(500);
			changeColour(LightPurple);
			cin >> num;
			player *pls = new player[num];
			create_players(pls, num);

			int turn = 0;
			int roll = 0;
			int wins = 0;
			string c;


			Graph g;
			
			int c1, c2;
			
			changeColour(AQUA);
	
			cout << "\nSelect 2 different colors for the board to be displayed in. Colors available: ";
			cout << "\nBLUE = 1 \nGREEN = 2; \nRED = 4; \nWHITE = 15; \nYELLOW = 6; \nPURPLE = 5; \nAQUA = 3; \nLightPurple = 13; \nLightBlue = 9; \nLightGreen = 10;" << endl;
		
			cin >> c1 >> c2;
			cout << endl;

			char l_top[4] = {char(218),'_','_',char(191)};	
			char l_bottom[4] = {char(195),'^','^',char(180)};
		
			
			changeColour(WHITE);
			
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
					changeColour(GREEN);
					cout << endl << "It is now " << pls[turn].name << "'s turn to roll." << endl;
					changeColour(RED);
						cout << "Press enter to roll the dice. \n\n";
						cin.ignore();
					roll = die_roll();
					changeColour(PURPLE);
					cout << "\t\t\t\t\t\t\t\t" << pls[turn].name << " rolled a " << roll << "." << endl;
					move_player(pls, turn, roll, wins, g, num);
					display_board(pls, num, c1, c2);
					turn = ++turn % num;
				}
			}
			changeColour(RED);
			cout << "Would you like to play again? (Enter Yes or No): " << endl;
			cin >> Answer;
		}
		else {

			changeColour(PURPLE);
			cout << "Hope you can play next time! " << endl;
			Sleep(1000); 
			return 0;
		}
		changeColour(WHITE);
	} while (((Answer == "Yes" && Answer != "No") || (Answer == "yes" && Answer != "no")));
	return 0;
}


