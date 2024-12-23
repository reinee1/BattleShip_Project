#include "../headerFile.h"
/*
requires: A reference to the current player (`currentPlayer`) and the opposing player (`opposingPlayer`).

effects: 
 handles artillery based on bot implementaion and
 Calls the `artilleryMove` function to perform the artillery action u
*/
void handleArtillery(PLAYER *currentPlayer, PLAYER *opposingPlayer)
{
    //no condition since its met throught the botThinking
    

    squareCoords squareCoord = getSquareCoord(currentPlayer->probGrid);

    INPUT input;
    input.row=squareCoord.maxCoords->row;
    input.column = squareCoord.maxCoords->col;
    
    printf("The bot plays Artillery %c%d \n", 97+input.column ,input.row+1);
    artilleryMove(currentPlayer,opposingPlayer,&input);

}
