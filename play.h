#ifndef PLAY_H
#define PLAY_H

#include "initialize.h"  // Since it might need Player and Grid definitions
#include "helper.h"

void play(char[SIZE][SIZE], int);


void play(char board[SIZE][SIZE], int nbPlayer)
{

    Grid Grids[52];
    Grid houses[4][4];
    Player players[4][4];
    int turnn = 0;
    initGame(Grids, houses, players, turnn);

    displayCurrent(board, players);

    int iteration = 0;

    bool finished = false;
    int turn = turnn;
    while (!finished)
    {

        if (iteration > 0)
        {
            displayCurrent(board, players);
        }

        iteration++;
        cout << endl
             << ("It is player " + idToColor(turn)) << (turn + 1) << " turn to play." << RESET << endl;
        int result = (rand() % MAX_DE) + 1; // 1 to 6

        // Check if all tokens are in the yard
        bool allInYard = true;
        for (int i = 0; i < 4; i++)
        {
            if (players[turn][i].index != -1)
            {
                allInYard = false;
                break;
            }
        }

        if (allInYard && result != 6)
        {
            cout << "Dice roll....Result: " << result << endl;
            cout << "PASS TURN" << endl;
            sleep(2);
            turn = (turn + 1) % nbPlayer;
            continue; // Skip the rest of the loop for this turn
        }

        int choice = 0;
        char charChoice;

        cout << "Dice roll....Result: " << result << endl;

        cout << "Which token (goti) you want to move " << endl
             << endl;
        cout << ">";
        cin >> charChoice;

        choice = getTokenChoice(charChoice, turn);

        // cout << players[turn][choice-1].index;

        // if the player whose turn is now , if he has got a 6 as result of dice
        // and uski pichli goti bahir nahi ayi (index=-1)
        // CASE 1:   no token out
        if (players[turn][choice - 1].index == -1 && result == 6)
        {

            // usko bahir le kar ao and update its coordinates according to new position
            players[turn][choice - 1].index = getIndexByTurn(turn);
            players[turn][choice - 1].x = Grids[getIndexByTurn(turn)].x;
            players[turn][choice - 1].y = Grids[getIndexByTurn(turn)].y;
        }

        // CASE 2: there is a token outside
        else if (players[turn][choice - 1].index != -1)
        {
            // calculate the value,goti kitna aage jayegi
            int step = result;

            // move the goti to the required position
            while (step > 0)
            {
                // check kahin goti ghar tou nahi pohanch gayi (reached HOME)
                if (isHome(turn, players[turn][choice - 1].index))
                {

                    players[turn][choice - 1].index = 200;
                }

                // MAIN BOARD PE HAI
                if (players[turn][choice - 1].index < 52)
                {
                    players[turn][choice - 1].index = (players[turn][choice - 1].index + 1) % 52;
                    players[turn][choice - 1].x = Grids[players[turn][choice - 1].index].x;
                    players[turn][choice - 1].y = Grids[players[turn][choice - 1].index].y;
                }

                // ghar kay raastay main hai goti
                else
                {
                    //
                    players[turn][choice - 1].index = players[turn][choice - 1].index + 1;
                    wayToHome(players, turn, choice);
                    if (players[turn][choice - 1].x == 6 && players[turn][choice - 1].y == 6)
                    {
                        displayCurrent(board, players);
                        // return turn;
                    }
                }
                step--;
            }

            for (int i = 0; i < 4; i++)
            {
                if (i != turn)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        // jota tou nahin ban raha
                        if (players[i][j].x == players[turn][choice - 1].x && players[i][j].y == players[turn][choice - 1].y)
                        {
                            cout << "\nJOTA detected";
                            players[i][j].index = -1;
                            players[i][j].x = houses[i][j].x;
                            players[i][j].y = houses[i][j].y;
                        }
                    }
                }
            }
        }

        turn = (turn + 1) % nbPlayer;
    }
}

#endif