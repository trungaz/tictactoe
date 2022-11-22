/* tictactoe.cpp : AI engine play tic tac toe
Input : Current game state
Output : Best possible moves
1. AI Engine:
	+ State representation
	+ Check if game is over
	+ Output winner or draw if game over
	+ render (text screen)
	+ valid moves
		- check current player
		- calculate valid moves
	+ calculate states scores
		- final states scores
		- not-final states scores
	+ calculate best moves
2. User interfaces:
	+ Asking X or O player
	+ Check legal team
	+ Input moves and report if illegal move
	+ Print current move and computer's move
	+ Response game result when game end
*/

#include<iostream>
#include<vector>

using namespace std;

//Create new type to store game states
typedef vector<vector<char> > States;
const int SIZE = 3;

//Game render in text
void GameRender(States s) 
{
	cout << "   |  1  |  2  |  3  |  " << endl;
	cout << "------------------------" << endl;
	for (int i = 0; i < 3; i++) {
		cout <<" " <<i+1 << " |  ";
		for (int j = 0; j < 3; j++) {
			cout << s[i][j] << "  |  ";
		}
		cout << endl;
	cout << "------------------------" << endl;
	}
	cout << endl;
}

//check if game is over
bool IsFinalStates (States s)
{
	//check row
	for (int i = 0; i < SIZE; i++)
	{
		if (s[i][0] == s[i][1] && s[i][1] == s[i][2] && s[i][0] != ' ') return true;
	}
	//check column
	for (int i = 0; i < SIZE; i++)
	{
		if (s[0][i] == s[1][i] && s[1][i] == s[2][i] && s[0][i] != ' ') return true;
	}
	//check diagonal
		if (s[0][0] == s[1][1] && s[1][1] == s[2][2] && s[0][0] != ' ') return true;
		if (s[0][2] == s[1][1] && s[1][1] == s[2][0] && s[0][2] != ' ') return true;
	//check full
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (s[i][j] == ' ') return false;
			}
		}
	return true;
}
//check final result
char getScoresFinalStates (States s)
{
	//check row for who wins
	for (int i = 0; i < SIZE; i++)
	{
		if (s[i][0] == s[i][1] && s[i][1] == s[i][2] && s[i][0] == 'X') return 'X';
		else if((s[i][0] == s[i][1] && s[i][1] == s[i][2] && s[i][0] == 'O')) return 'O';
	}
	//check column for who wins
	for (int i = 0; i < SIZE; i++)
	{
		if (s[i][0] == s[i][1] && s[i][1] == s[i][2] && s[i][0] == 'X') return 'X';
		else if((s[i][0] == s[i][1] && s[i][1] == s[i][2] && s[i][0] == 'O')) return 'O';
	}
	//check diagonal for who wins
		if (s[0][0] == s[1][1] && s[1][1] == s[2][2] && s[0][0] == 'X') return 'X';
		if (s[0][2] == s[1][1] && s[1][1] == s[2][0] && s[0][2] == 'X') return 'X';
		if (s[0][0] == s[1][1] && s[1][1] == s[2][2] && s[0][0] == 'O') return 'O';
		if (s[0][2] == s[1][1] && s[1][1] == s[2][0] && s[0][2] == 'O') return 'O';
	return 'D';
}

//detect current player
char nextPlayer(States s)
{
	int countX = 0, countO = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (s[i][j] == 'X') countX++;
			else if (s[i][j] == 'O') countO++;
		}
	}
	if (countX == countO) return 'X';
	else return 'O';
}

//check valid moves
bool IsValidMoves(States s, int inputR, int inputC)
{
	if (inputR < 0 || inputR > 2) return false;
	if (inputC < 0 || inputC > 2) return false;
	States newState = States(3, vector<char>(3, ' '));
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			newState[i][j] = s[i][j];
		}
	}
	if (newState[inputR][inputC] == ' ') return true;
	return false;
}

//Play move
States Move(States s, int i, int j, char player)
{
	States newState = States(3, vector<char>(3, ' '));
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++) {
			newState[i][j] = s[i][j];
		}
	}
	newState[i][j] = player;
	return newState;
}

//List of next legal states for AI
vector<States> getNextState(States s)
{
	char player = nextPlayer(s);
	vector<States> states;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (s[i][j] == ' ') {
				States nextState = Move(s, i, j, player);
				states.push_back(nextState);
			}
		}
	}
	return states;
}

//calculate best move
pair<int, States> getScore(States s)
{
	//return game final state and game result if game is over
	if (IsFinalStates(s)) {
		return make_pair(getScoresFinalStates(s), s);
	}
	char player = nextPlayer(s);
	vector<States> states = getNextState(s);
	int bestScore = -10;
	States bestState;
	for (States ns: states) {
		pair<int, States> p = getScore(ns);
		int score = p.first;
		if (player == 'X') {
			if (bestScore < score || bestScore == -10) {
				bestScore = score;
				bestState = ns;
			}
		} else {
			if (bestScore > score || bestScore == -10) {
				bestScore = score;
				bestState = ns;
			}
		}
	}
	return make_pair(bestScore, bestState);
}

//get computer moves
pair<int, int> getComputerMove(States s) 
{
    pair<int, States> p = getScore(s);
    int score = p.first;
    States newState = p.second;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (newState[i][j] != s[i][j]) return make_pair(i, j);
        }
    }
    return make_pair(-1, -1);
}

int main() 
{
	States start = States(3, vector<char>(3, ' ')); //Create board
	GameRender(start); //Render game first time
	char humanPlayer = ' ', currentPlayer = 'X';
	//Enter player and check if player is valid
	while (true) {
		cout << "Choose your player (X or O): ";
		cin >> humanPlayer;
		if (humanPlayer == 'X' || humanPlayer == 'O') {
			break;
		}
		else if (humanPlayer == 'x') {
			humanPlayer = 'X';
			break;
		}
		else if (humanPlayer == 'o') {
			humanPlayer = 'O';
			break;
		}
		cout << "Player not found!" << endl;
	}
	cout << "You are " << humanPlayer << " player." << endl;
	while (true) //Loop the game until game over
	{
		int i = -1, j = -1;
		if (humanPlayer == currentPlayer) //Get player moves
		{
			while (true) {
				cout << "Enter your play: " << endl; 
				cout << "Column: ";
				cin >> i;
				cout << "Row: ";
				cin >> j;
				if (IsValidMoves(start, i - 1, j - 1) == true) //Check if player moves is valid
				{
					cout << "You play: (" << i << " " << j << ")" << endl;
					start = Move(start, i - 1, j - 1, currentPlayer);
					break;
				}
				else {
					cout << "Illegal moves" << endl;
				}
			}
		}
		else //Get computer moves
		{
			pair<int, int> move = getComputerMove(start);
			i = move.first;
			j = move.second;
			cout << "I play: (" << i + 1 << " " << j + 1 << ")" << endl;
			start = Move(start, i, j, currentPlayer);
		}
		GameRender(start);
		currentPlayer = currentPlayer == 'X' ? 'O' : 'X'; //Switch between 2 player turn
		//Check and output result when a player won.
		if (IsFinalStates(start))
		{
			char score = getScoresFinalStates(start);
			if (score = 'X') {
				cout << "X won." << endl;
			}
			else if (score = 'O') {
				cout << "O won." << endl;
			}
			else if (score = 'D') {
				cout << "A draw" << endl;
			}
			break;
		}
	}	
	return 0;
}
