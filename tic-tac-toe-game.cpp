#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef vector<vector<char>> State;

double ratio1 = 0, ratio2 = 0;
int round = 1;
double percentWin;
char question;

struct Move 
{
	int x;
	int y;
	Move (int _x, int _y) {
		x = _x;
		y = _y;
	}
};

void board(State s) 
{
    cout << "ROUND: " << round << endl;
    cout << s[0][0] << "  | " << s[0][1] <<" |  " << s[0][2] << endl;
    cout << "--- --- ---" << endl;
    cout << s[1][0] << "  | " << s[1][1] <<" |  " << s[1][2] << endl;
    cout << "--- --- ---" << endl;
    cout << s[2][0] << "  | " << s[2][1] <<" |  " << s[2][2] << endl;
}

State play(State s, char number, char value) 
{
	if (number == '1') s[0][0] = value;
	else if (number == '2') s[0][1] = value;
	else if (number == '3') s[0][2] = value;
	else if (number == '4') s[1][0] = value;
	else if (number == '5') s[1][1] = value;
	else if (number == '6') s[1][2] = value;
	else if (number == '7') s[2][0] = value;
	else if (number == '8') s[2][1] = value;
	else s[2][2] = value;
	return s;
}

// check when is endgame
bool checkFinal(State s) {
	for (int i = 0; i < 3; i++) 
	{
	//rows check
		if (s[i][0] != ' ' && s[i][0] == s[i][1] && s[i][1] == s[i][2]) 
            return true;
	
    //cols check cols
		if (s[0][i] != ' ' && s[0][i] == s[1][i] && s[1][i] == s[2][i]) 
            return true;
	}
	
    //diagonals check 
	if (s[0][0] != ' ' && s[0][0] == s[1][1] && s[1][1] == s[2][2]) 
        return true;
	if (s[0][2] != ' ' && s[0][2] == s[1][1] && s[1][1] == s[2][0]) 
        return true;
	
    //check all
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) 
		{
			if (s[i][j] == ' ')
				return false;
		}	
	}
	return true;
}

int getScoreFinal(State s, char machine, char person) 
{
	for (int i = 0; i < 3; i++) 
	{
		if (s[i][0] != ' ' && s[i][0] == s[i][1] && s[i][1] == s[i][2])
		{ 
			if (s[i][0] == machine) 
				return 1; 
			else 
				return -1;
		}
		if (s[0][i] != ' ' && s[0][i] == s[1][i] && s[1][i] == s[2][i]) 
		{
			if (s[0][i] == machine) 
				return 1; 
			else 
				return -1;
		}
	}
	if (s[0][0] != ' ' && s[0][0] == s[1][1] && s[1][1] == s[2][2]) 
	{
		if (s[0][0] == machine) 
			return 1; 
		else 
			return -1;
	}
	if (s[0][2] != ' ' && s[0][2] == s[1][1] && s[1][1] == s[2][0]) 
	{
		if (s[0][2] == machine) 
			return 1;
		else 
			return -1;
		return 0;
	}
}

int getScore (State s, bool isMax, char machine, char person) 
{
	if ( checkFinal(s) ) 
    {
        return getScoreFinal ( s, machine, person );
    }
	if ( isMax ) 
	{
		int best = -10;
		for ( int i = 0; i < 3; i++ ) 
		{
			for ( int j = 0; j < 3; j++ ) 
			{
				if ( s[i][j] == ' ' ) 
				{
					s[i][j] = machine;
					best = max(best, getScore(s, !isMax, machine, person));
					s[i][j] = ' ';
				}
			}
		}
		return best;
	} 
	else 
	{
		int best = 10;
		for ( int i = 0; i < 3; i++ ) 
		{
			for ( int j = 0; j < 3; j++ ) 
			{
				if ( s[i][j] == ' ' ) 
				{
					s[i][j] = person;
					best = min(best, getScore(s, !isMax, machine, person));
					s[i][j] = ' ';
				}
			}
		}
		return best;
	}
}

Move findMove ( State s, char machine, char person ) 
{
	int bestScore = -10;
	Move bestMove(-1,-1);
	for ( int i = 0; i < 3; i++ ) 
	{
		for ( int j = 0; j < 3; j++ )  
		{
			if ( s[i][j] == ' ' ) 
			{
				s[i][j] = machine;
				int Score = getScore(s, false, machine, person);
				if ( Score > bestScore ) 
				{
					bestScore = Score;
					bestMove.x = i;
					bestMove.y = j;
				}
				s[i][j] = ' ';
			}
		}
	}
	return bestMove;
}

void returnAndAsk()
{
	cout << fixed << setprecision(0) << "Score of the match: " << ratio1 << " - " << ratio2 << endl;
	percentWin = (ratio1/(ratio1 + ratio2)) * 100;
	cout << "Your win percentage is " << fixed << setprecision(2) << percentWin << "%" << endl;
	cout << "Do you want to try again? (y/n)" << endl;
	cin >> question;
}

void checkPercentWin()
{
	if (percentWin > 50)
	{
		cout << "You are 'dang's cap'!" << endl;
	}
	else if ( percentWin == 50)
	{
		cout << "You are like a computer!" << endl;
	}
	else
	{
		cout << "You don't play well, need more practice!" << endl;
	}
}

int main() 
{
	bool appear[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	char machine, person, number;
	State s = {
			{'1','2','3'},
			{'4','5','6'},
			{'7','8','9'} };
	board(s);
	s = {
		{' ',' ',' '},
		{' ',' ',' '},
		{' ',' ',' '} };
	cout << "Let's choose the number on the broad!!!" << endl << "---------------" << endl;
	cout << "Do you want play with X or O: ";
	cin >> person;
	while( person != 'X' && person != 'x' && person != 'O' && person != 'o' ) 
	{
		cout << endl;
		cout << "You just can choose X or O!" << endl << "---------------" << endl;
		cout << "Choose again : ";
		cin >> person;
	}
	cout << endl;
	if ( person == 'X' || person == 'x' ) // if the player wants to choose X
	{
		machine = 'O';
		cout << "You play first!" << endl << "---------------" << endl;
		cout << "You choose : " ;
		cin >> number;
		while ( number < '1' || number > '9' ) 
		{
			cout << "You just can choose 1 to 9!";
			cout << "Choose again: ";
			cin >> number;
		}
		appear[number - '1'] = 1;
		s = play(s, number, person);
		cout << endl;
		board(s);
	}
	else // if the player wants to choose O
	{
		machine = 'X';
	}
	cout << endl;
	while (true) // if the player wants to choose O and machine is the first
	{
		Move bestMove = findMove(s, machine, person);
		s[bestMove.x][bestMove.y] = machine;
		cout << "Machine choose: " << 3*bestMove.x + bestMove.y + 1 << endl << "---------------" << endl;
		appear[3*bestMove.x + bestMove.y] = 1;
		board(s);
		if (checkFinal(s)) // give game results and scores
		{
			int score = getScoreFinal(s, machine, person);
			// int ratio1 = 0, ratio2 = 0;
			if (score == -1)
			{
				ratio1++;
				cout << "Congatulations. You wins!" << endl;
				returnAndAsk();
				if (question == 'y' || question == 'Y')
				{
                    round++;
					main();
				}
				else if( question == 'n' || question == 'N')
				{
					checkPercentWin();
				}
				else if( question == 'n' || question == 'N')
				{
					break;
				}
			}
			else if (score == 1)
			{
				ratio2++;
				cout << "Machine wins!" << endl;
				returnAndAsk();
				if (question == 'y' || question == 'Y')
				{
                    round++;
					main();
				}
				else if( question == 'n' || question == 'N')
				{
					checkPercentWin();
				}
				else if( question == 'n' || question == 'N')
				{
					break;
				}
			}
			else if (score == 0)
			{
				ratio1++;
				ratio2++;
				cout << "Tie!" << endl;
				returnAndAsk();
				if (question == 'y' || question == 'Y')
				{
                    round++;
					main();
				}
				else if( question == 'n' || question == 'N')
				{
					checkPercentWin();
				}
				else if( question == 'n' || question == 'N')
				{
					break;
				}
			}
			break;
		}
		cout << "Choose: ";
		while (true) // if player choose X and play first
		{
			cin >> number;
			if (number < '1' || number > '9') 
			{
				cout << "You can't choose this! " ;
				cout << "Choose again : ";
				continue;
			} 

			else if (appear[number - '1'] == 1) 
			{
				cout << "You can't choose this! " ;
				cout << "Choose again : ";
				continue;
			}
			break;
		}
		appear[number - '1'] = 1;
		cout << endl;
		s = play(s, number , person);
		board(s);
		if (checkFinal(s)) // give game results and scores
		{
			int score = getScoreFinal(s, machine, person);
			// int ratio1 = 0, ratio2 = 0;
			if (score == -1) // if you win
			{
				ratio1++;
				cout << "Congatulations. You wins!" << endl;
				returnAndAsk();
				if (question == 'y' || question == 'Y') // The program asks if the player wants to continue playing, if so, move on to the next round
				{
                    round++;
					main();
				}
				else if( question == 'n' || question == 'N')
				{
					checkPercentWin();
				}
				else if( question == 'n' || question == 'N')
				{
					break;
				}
			}
			else if (score == 1)
			{
				ratio2++;
				cout << "Machine wins!" << endl;
				returnAndAsk();
				if (question == 'y' || question == 'Y')
				{
                    round++;
					main();
				}
				else if( question == 'n' || question == 'N')
				{
					checkPercentWin();
				}
				else if( question == 'n' || question == 'N')
				{
					break;
				}
			}
			else if (score == 0)
			{
				ratio1++;
				ratio2++;
				cout << "Tie!" << endl;
				returnAndAsk();
				if (question == 'y' || question == 'Y')
				{
                    round++;
					main();
				}
				else if( question == 'n' || question == 'N')
				{
					checkPercentWin();
				}
				else if(question == 'n' || question == 'N')
				{
					break;
				}
			}
			break;
		}
	}
	return 0;
}