#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <limits>
#include <unistd.h>

using namespace std;

#define RESET "\u001B[0m"
#define RED "\u001B[31m"
#define GREEN "\u001B[32m"
#define YELLOW "\u001B[33m"
#define BLUE "\u001B[34m"
#define CYAN "\u001B[36m"

#define SIZE 15
#define MAX_DE 6

class Grid
{
public:
    int x;
    int y;
    int value;
};

class Player
{
public:
    int x;
    int y;
    int team;
    int index;
    char id;
};

int getTokenChoice(char charChoice, int turn);

// prototypes
void initGame(char[SIZE][SIZE]);
void initGame(Grid Grids[52], Grid houses[4][4], Player players[4][4], int &);

void menu(int &, int &);
void play(char[SIZE][SIZE], int);

void verifyInput();
void displayCurrent(char[SIZE][SIZE], Player[4][4]);
string idToColor(int);

// DEFINITION
void initGame(char b[SIZE][SIZE])
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

void verifyInput()
{
    if (!cin)
    {
        cout << "ERROR - Enter a valid number";

        cin.clear();

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void menu(int &choice, int &players)
{

    while (choice > 2 || choice < 1)
    {
        cout << endl
             << "Press 1 To Play" << endl;
        cout << "Press 2 To Quit " << endl
             << endl
             << "Enter your choice: ";
        cin >> choice;
    }

    players = 4;
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

int main()
{
    cout << " ********************WELCOME TO MY LUDO *****************" << endl;
    srand(time(NULL));

    char board[15][15];
    initGame(board);

    while (true)
    {
        int choice = -1;
        int players = -1;
        menu(choice, players);

        if (choice == 2)
        {
            cout << endl
                 << "Exiting ..." << endl;
            return 0;
        }

        play(board, players);
    }

    return 0;
}
