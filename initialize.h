#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <limits>
#include <unistd.h>

#include <ctime>

#define SIZE 15
#define MAX_DE 6

using namespace std;


#define RESET "\u001B[0m"
#define RED "\u001B[31m"
#define GREEN "\u001B[32m"
#define YELLOW "\u001B[33m"
#define BLUE "\u001B[34m"
#define CYAN "\u001B[36m"

class Grid {
public:
    int x;
    int y;
    int value;
};

class Player {
public:
    int x;
    int y;
    int team;
    int index;
    char id;
};

void initGrid(char[SIZE][SIZE]);
void initGame(Grid[52], Grid[4][4], Player[4][4], int &);


// DEFINITION
void initGrid(char b[SIZE][SIZE])
{

    // 15x15 grid
    char newBoard[SIZE][SIZE] =
        {
            //   0      1    2    3    4    5    6    7    8    9      10   11   12   13   14
            {'A', ' ', ' ', ' ', ' ', 'B', 'O', 'O', 'O', 'E', ' ', ' ', ' ', ' ', 'F'}, // 0
            {' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '}, // 1
            {' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '}, // 2
            {' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '}, // 3
            {' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '}, // 4
            {'C', ' ', ' ', ' ', ' ', 'D', 'O', 'O', 'O', 'G', ' ', ' ', ' ', ' ', 'H'}, // 5
            {'O', 'O', 'O', 'O', 'O', 'O', '#', '#', '#', 'O', 'O', 'O', 'O', 'O', 'O'}, // 6
            {'O', 'O', 'O', 'O', 'O', 'O', '#', 'S', '#', 'O', 'O', 'O', 'O', 'O', 'O'}, // 7
            {'O', 'O', 'O', 'O', 'O', 'O', '#', '#', '#', 'O', 'O', 'O', 'O', 'O', 'O'}, // 8
            {'I', ' ', ' ', ' ', ' ', 'J', 'O', 'O', 'O', 'M', ' ', ' ', ' ', ' ', 'N'}, // 9
            {' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '}, // 10
            {' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '}, // 11
            {' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '}, // 12
            {' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' ', ' ', ' ', ' '}, // 13
            {'K', ' ', ' ', ' ', ' ', 'L', 'O', 'O', 'O', 'O', ' ', ' ', ' ', ' ', 'P'}  // 14
        };

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // copying newBoard into "b" array that will be passed as argument
            b[i][j] = newBoard[i][j];
        }
    }
}


void initGame(Grid Grids[52], Grid houses[4][4], Player players[4][4], int &turn)
{
    //{y,x}

    // which path the goti (token) will follow
    // in this case it starts from P1 home but it is not necessarily true that it will always start from P1 home
    // can start from any of the 4 homes
    // so P2,P3 and P4 kay home se bhi start hota hai toh we have to specify that

    char team0IDs[4] = {'A', 'B', 'C', 'D'};
    char team1IDs[4] = {'E', 'F', 'G', 'H'};
    char team2IDs[4] = {'I', 'J', 'K', 'L'};
    char team3IDs[4] = {'M', 'N', 'Q', 'P'};

    // Choose a random player to start from
    srand(time(0));
    turn = rand() % 4;

       //SUPPOSE it starts from P4 home then
       int newGrids[52][2] = 
    {
         {8, 14}, {8, 13}, {8, 12}, {8, 11}, {8, 10}, {8, 9},
         {9, 8}, {10, 8}, {11, 8}, {12, 8}, {13, 8}, {14, 8} ,  {14,7},
          {14, 6}, {13, 6}, {12, 6}, {11, 6}, {10, 6}, {9, 6}  ,
                  {8, 5}, {8, 4}, {8, 3}, {8, 2}, {8, 1}, {8, 0},   {7,0},
                  { 6,0 } , {6,1}, {6,2} ,{6,3}, {6,4}, {6,5},
                   { 5,6 },  {4,6}, {3,6}, {2,6}, {1,6}, {0,6},
          {0,7},
           {0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8},
           {6, 9}, {6, 10}, {6, 11}, {6, 12}, {6, 13}, {6, 14}, {7,14}
      };

      


    if (turn == 0)
    {
        cout << "\nStarting from Player1" << endl;
    
    }

    else if (turn == 1)
    {
        cout << "\nStarting from Player 2" << endl;
       
    }

    else if (turn == 2)
    {
        cout << "\nStarting from Player 3" << endl;

    }
    else
    {
        cout << "\nStarting from Player4" << endl;
    }

    
    

    // maxPlayer    //noOfToken   //x,y coordinate
    int newHouses[4][4][2] =
        {
            // gotiyan (tokens) ki placement on grid

            // A       //B     //C     //D
            {{0, 0}, {0, 5}, {5, 0}, {5, 5}}, // player 1

            // E     //F      //G      //H
            {{0, 9}, {0, 14}, {5, 9}, {5, 14}}, // player 2

            // i      //J      //K       //L
            {{9, 0}, {9, 5}, {14, 0}, {14, 5}}, // player 3

            // M      //N     //O      //P
            {{9, 9}, {9, 14}, {14, 9}, {14, 14}}, // player 4
        };

    for (int i = 0; i < 52; i++)
    {
        Grids[i].y = newGrids[i][0];
        Grids[i].x = newGrids[i][1];
        Grids[i].value = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            houses[i][j].y = newHouses[i][j][0];
            houses[i][j].x = newHouses[i][j][1];
            houses[i][j].value = (j + 1) + (i) * 10;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            players[i][j].x = houses[i][j].x;
            players[i][j].y = houses[i][j].y;
            players[i][j].index = -1;
            players[i][j].team = i;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            players[0][j].id = team0IDs[j]; // Assign IDs for team 0
            players[1][j].id = team1IDs[j]; // Assign IDs for team 1
            players[2][j].id = team2IDs[j]; // Assign IDs for team 2
            players[3][j].id = team3IDs[j]; // Assign IDs for team 3
        }
    }
}

#endif
