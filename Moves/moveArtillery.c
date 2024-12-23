#include "../headerFile.h"
/*void artilleryMove(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input)
requires: reference to the current player of type PLAYER containing if the artillery move is available and the hitsAndMissesGrid,
        a reference to the player being targeted of type PLAYER containing his grid,
        a reference to the input of type INPUT containing the target coordinates for the artillery move
        the move should be unlocked if the current player has sinked at least one ship
effects: returns if the target is hit and mark the hits and misses grid with "*" or miss and mark the hits and misses grid with "o"
*/
void artilleryMove(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input)
{
    if (currentPlayer->artillery!=2) { // i can only access this move if at least 1 ship is sunk
        printf("Artillery conditions are not met.\n");
        return;
    }
    //check the validation of the input
    if (isInBound(input)==0)
    {
        printf("Invalid coord\n");
        return;
    }
    

    for (int i = 0; i < NUMBEROFSHIPS; i++)
    {
        
            // Make sure I dont go out of bounds
            if (isInBound(input)==1)
            {
                // Check for a hit in the grid
                if (opposingPlayer->grid[input->row][input->column] == 'X')
                {
                    printf("Hit!\n");
                    if(currentPlayer->hitsAndMissesGrid[input->row][input->column]!='*')
                    {
                        currentPlayer->hitsAndMissesGrid[input->row][input->column] = '*'; // Mark the location of the hit
                        addHitOnShip(currentPlayer, opposingPlayer,input); //update the hit count of the ship
               
                    }
                }
                else
                {
                    printf("Miss.\n");
                    currentPlayer->hitsAndMissesGrid[input->row][input->column] = 'o';
                    
                }
            }

            updateCoordBySquare(input,i);
    }

    
//printGrid(opposingPlayer->hitsAndMissesGrid);
}

//checking if we can use this move
//first when artillery can be used , it is set to one, the first iteration its updated to 2 so that the second itert=ation its back to 0 so ca't be used again
/*void checkArtillery(PLAYER* currentPlayer) 
requires: a reference to the current player of type PLAYER to indicate if the artillery move is available or not.abort
          the artillery of the player should be 1 or 2
effects: unlocks the artillery move and returns that it has been unlocked, or reset it to 0
*/
void checkArtillery(PLAYER* currentPlayer) 
{
    if(currentPlayer->artillery==2 )
    {
        currentPlayer->artillery=0;
    }

     if(currentPlayer->artillery==1)
    {
        printf("Special move unlocked for 1 turn: artillery!\n");
        currentPlayer->artillery=2;

    }
}
