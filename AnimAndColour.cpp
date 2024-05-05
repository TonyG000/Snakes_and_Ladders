#include "AnimAndColour.h"

void AnimAndColour::changeColour(int colour) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}
void AnimAndColour::clearScreen(int characterLength) {
	for (int i = 0; i < characterLength; i++) {
		cout << "\b";
	}
}


void AnimAndColour::showLoadingScreen() {
	cout << "\t\t\t\t\t\t\t";
	int i;
	string closed = "_ _ _", open = "* * *";
	int colour[] = { RED, GREEN, BLUE };
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
void AnimAndColour::showBlinkingLights() {
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
