#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct player {
	string name = "";
	int score = 0;
	bool win = 0;
};

class Graph {
	vector<pair<int, int>> adj[100];

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

	int getDest(int src) {
		for (vector<pair<int, int>>::iterator it = adj[src].begin(); it != adj[src].end(); ++it) {
			pair<int, int>& edge = *it;
			if (edge.first == src) { //may be a logical error here
				return edge.second;
			}
		}
		return src;
	}
};

int die_roll() {
	return 1 + (rand() % 6);
}

void create_players(vector <player>& players, int num) {
	for (int i = 0; i < num; i++) {
		player p;
		cout << "Enter name of player " << i << ": ";
		cin >> p.name;
		players.push_back(p);
	}
}

void display_players(const vector <player>& players, int num) {
	for (int i = 0; i < num; i++) {
		cout << endl;
		cout << "PLAYER " << i << endl;
		cout << "Name: " << players[i].name << endl;
		cout << "Score: " << players[i].score << endl << endl;
	}
}

void move_player(vector <player>& players, int turn, int roll, int& wins, Graph& g) {
	if ((players[turn].score + roll) > 100) {
		cout << players[turn].name << "'s score has exceeded 100. Their turn will be skipped." << endl;
	}
	else {
		players[turn].score += roll;
		players[turn].score = g.getDest(players[turn].score);
		cout << players[turn].name << "'s score is now " << players[turn].score << "." << endl;
	}

	if (players[turn].score == 100) {
		players[turn].win = 1;
		wins++;
		cout << players[turn].name << " has won!" << endl << endl;
	}
}

void display_board(vector<player>& players, int num) { //might need to be changed but just a general idea to show how the output should look like :)
	string board[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = "|__|";
		}
	}

	for (int i = 0; i < num; i++) {
		int score = players[i].score;
		if (score > 0) {
			int row = 9 - (score - 1) / 10;
			int col = (score - 1) % 10;
			if (row % 2 == 0) {
				col = 9 - col;
			}
			board[row][col] = "|" + players[i].name + "|";
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	string Answer;
	do {
		int num = 0;
		cout << "How many players would you like to register? ";
		cin >> num;

		vector <player> pls;
		create_players(pls, num);

		int turn = 0;
		int roll = 0;
		int wins = 0;
		bool play;
		string c;

		cout << "Would you like to simulate or play? (0 for sim, 1 for play) ";
		cin >> play;

		Graph graph;

		while (wins < num) {
			if (pls[turn].win == 1) {
				turn = ++turn % num;
				continue;
			}

			else {
				cout << endl << "It is now " << pls[turn].name << "'s turn to roll." << endl;
				if(play){
				cout << "Press enter to roll the dice. \n\n";
					getline(cin, c, '\n');
					}
				roll = die_roll();
				cout << pls[turn].name << " rolled a " << roll << "." << endl;

				move_player(pls, turn, roll, wins, graph);
				display_board(pls, num);
				turn = ++turn % num;
			}
		}
		cout << "Would you like to play again? (Enter Yes or No): " << endl;
		cin >> Answer;
	} while (((Answer == "Yes" && Answer != "No") || (Answer == "yes" && Answer != "no")));
}
