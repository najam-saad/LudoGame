#include "initialize.h"
#include "helper.h"
#include "play.h"

int main()
{
    
    char board[SIZE][SIZE];
    Grid grids[52], houses[4][4];
    Player players[4][4];
    int gameOption, state = 0;

    initGrid(board);
    initGame(grids, houses, players, state);

    menu(gameOption, state);
    play(board, gameOption);

    return 0;
}
