#ifndef HELPER_H
#define HELPER_H

#include "initialize.h"

#include <iostream>
#include <string>

using namespace std;

int getTokenChoice(char, int);
void menu(int &, int &);
void verifyInput();
void displayCurrent(char[SIZE][SIZE], Player[4][4]);
string idToColor(int);



void verifyInput()
{
    if (!cin)
    {
        cout << "ERROR - Enter a valid number";

        cin.clear();

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


void displayCurrent(char board[SIZE][SIZE], Player players[4][4])
{
    char currentBoard[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            currentBoard[i][j] = board[i][j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            currentBoard[players[i][j].y][players[i][j].x] = players[i][j].id; // Display alphabetic IDs
        }
    }

    cout << endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << " ";
        for (int j = 0; j < SIZE; j++)
        {
            string s = "";
            s = s + currentBoard[i][j] + " ";

            switch (currentBoard[i][j])
            {
            case '1':
            case '2':
            case '3':
            case '4':
                s = "";
                s = s + currentBoard[i][j] + " ";
                for (int a = 0; a < 4; a++)
                {
                    for (int b = 0; b < 4; b++)
                    {
                        if (i == players[a][b].y && j == players[a][b].x)
                        {
                            s = idToColor(a) + s + RESET; // Apply color based on team
                        }
                    }
                }
                break;
            default:
                // Check for specific IDs and apply color
                switch (currentBoard[i][j])
                {
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                    s = RED + s + RESET;
                    break;
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                    s = GREEN + s + RESET;
                    break;
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                    s = CYAN + s + RESET;
                    break;
                case 'M':
                case 'N':
                case 'Q':
                case 'P':
                    s = YELLOW + s + RESET;
                    break;
                }
                break;
            }
            cout << s;
        }
        cout << endl;
    }
    cout << endl;
}

string idToColor(int id)
{
    switch (id)
    {
    case 0:
        return RED;
    case 1:
        return GREEN;
    case 2:
        return CYAN;
    case 3:
        return YELLOW;
    default:
        return "";
    }
    return "";
}


int getTokenChoice(char charChoice, int turn)
{
    charChoice = toupper(charChoice);

    if (turn == 0)
    {
        if (charChoice == 'A' || charChoice == 'B' || charChoice == 'C' || charChoice == 'D')
        {
            return charChoice - 'A' + 1;
        }
    }
    else if (turn == 1)
    {
        if (charChoice >= 'E' && charChoice <= 'H')
        {
            return charChoice - 'E' + 1;
        }
    }
    else if (turn == 2)
    {
        if (charChoice >= 'I' && charChoice <= 'L')
        {
            return charChoice - 'I' + 1;
        }
    }
    else if (turn == 3)
    {
        if (charChoice >= 'M' && charChoice <= 'P')
        {
            return charChoice - 'M' + 1;
        }
    }

    return -1; // Return -1 if input is invalid
}

void menu(int &gameOption, int &state) {
    cout << "Choose an option:\n";
    cout << "1. Start New Game\n";
    cout << "2. Load Game\n";
    cout << "3. View Instructions\n";
    cout << "4. Exit\n";
    cin >> gameOption;

    // Verify input
    if (cin.fail() || gameOption < 1 || gameOption > 4) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to next line
        cout << "Invalid input, please try again.\n";
        state = -1; // Indicating an error or invalid state
    } else {
        state = 0; // Indicating everything is fine
    }
}



bool isHome(int turn, int index)
{
    switch (turn)
    {
    // player 1
    case 0:
    {
        if (index == 25)
            return true;
        return false;
        break;
    }

        // player 2
    case 1:
    {
        if (index == 38)
            return true;
        return false;
        // player 3
    case 2:
        if (index == 12)
            return true;
        return false;
    }

    // player 4
    case 3:
    {
        if (index == 51)
            return true;
        return false;
    }
        return false;
    }
}

void wayToHome(Player players[4][4], int turn, int choice)
{
    switch (turn)
    {
    case 0:
        players[turn][choice - 1].x += 1;
        break;
    case 2:
        players[turn][choice - 1].x -= 1;
        break;
    case 1:
        players[turn][choice - 1].y += 1;
        break;
    case 3:
        players[turn][choice - 1].y -= 1;
        break;
    }
}

int getIndexByTurn(int turn)
{
     //player 1
     if (turn==0)
     {
          return  27;
        
     }

     //player 2
    else if (turn==1)
     {
          return  40;
        
     }

     //player 3
    else if (turn==2)
     {
          return  14;
        
     }

     //player 4
    else if (turn==3)
     {
          return  1;
        
     }

     else
       return -1;

 
 }

#endif
