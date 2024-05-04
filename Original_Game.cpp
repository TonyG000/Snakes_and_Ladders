// Author: Youssef Aboushady
// Snakes and Ladders

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

struct player{
	string name = "";
	int score = 0;
	bool win = 0;
};

int die_roll(){
	return 1 + (rand() % 6);
}

void create_players(player *players, int num){
	for(int i=0;i<num;i++){
		cout << "Enter name of player " << i << ": "; 
		cin >> players[i].name;
	}
}

void display_players(player *players, int num){
	for(int i=0;i<num;i++){
		cout << endl;
		cout << "PLAYER " << i << endl;
		cout << "Name: " << players[i].name << endl;
		cout << "Score: " << players[i].score << endl << endl;
	}
}

void move_player(player *players, int turn, int roll, int &wins){
	if((players[turn].score + roll) > 100){
		cout << players[turn].name << "'s score has exceeded 100. Their turn will be skipped." << endl;
	}
	
	else{
		players[turn].score += roll;
		cout << players[turn].name << "'s score is now " << players[turn].score << "." << endl;
		
		int prev = players[turn].score;
		
		if(players[turn].score >= 1 && players[turn].score <= 20){
			if(players[turn].score == 1){
				players[turn].score = 38;
			}
			
			else if(players[turn].score == 4){
				players[turn].score = 14;
			}
			
			else if(players[turn].score == 9){
				players[turn].score = 31;
			}
			
			else if(players[turn].score == 17){
				players[turn].score = 7;
			}						
		}
		
		else if(players[turn].score >= 21 && players[turn].score <= 40){
			if(players[turn].score == 21){
				players[turn].score = 42;
			}
			
			else if(players[turn].score == 28){
				players[turn].score = 84;
			}
		}
		
		else if(players[turn].score >= 41 && players[turn].score <= 60){
			if(players[turn].score == 51){
				players[turn].score = 67;
			}
			
			else if(players[turn].score == 54){
				players[turn].score = 34;
			}						
		}
		
		else if(players[turn].score >= 61 && players[turn].score <= 80){
			if(players[turn].score == 62){
				players[turn].score = 19;
			}
			
			else if(players[turn].score == 64){
				players[turn].score = 60;
			}
			
			else if(players[turn].score == 72){
				players[turn].score = 91;
			}
			
			else if(players[turn].score == 80){
				players[turn].score = 99;
			}						
		}
		
		else if(players[turn].score >= 81 && players[turn].score <= 100){
			if(players[turn].score == 87){
				players[turn].score = 36;
			}
			
			else if(players[turn].score == 93){
				players[turn].score = 73;
			}
			
			else if(players[turn].score == 95){
				players[turn].score = 75;
			}
			
			else if(players[turn].score == 98){
				players[turn].score = 79;
			}						
		}
		
		if(prev != players[turn].score){
			string s = (prev < players[turn].score) ? "ladder" : "snake";
			cout << endl << players[turn].name << " landed on a " << s << "! \nTheir score is now " << players[turn].score << ".\n\n";			
		}

	}
	
	if(players[turn].score == 100){
		players[turn].win = 1;
		wins++;
		cout << players[turn].name << " has won!" << endl << endl;
	}
}

int main(){
	srand(time(0));	

	int num = 0;
	cout << "How many players would you like to register? ";
	cin >> num;

	player pls[num];
	create_players(pls, num);
	
	int turn = 0;
	int roll = 0;
	int wins = 0;
	bool play;
	string c;
	
	cout << "Would you like to simulate or play? (0 for sim, 1 for play) ";
	cin >> play;
	
	while(wins < num){
		if(pls[turn].win == 1){
			turn = ++turn % num;
			continue;
		}
		
		else{
			cout << endl << "It is now " << pls[turn].name << "'s turn to roll." << endl;
			
			if(play){
				cout << "Press enter to roll the dice. \n\n";	
				getline(cin, c, '\n');			
			}
			
			roll = die_roll();
			cout << pls[turn].name << " rolled a " << roll << "." << endl;	
			
			move_player(pls, turn, roll, wins);
			turn = ++turn % num;
		}	
	}
}
