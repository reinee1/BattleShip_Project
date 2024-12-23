#include "../headerFile.h"

//radar sweep function checks in a 2x2 area if it exists enemy ships and display result
//return 0 if move invalid, 1 if ships found, 2 if no ship found

/*int RadarSweep(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input)
requires:-reference for currentPlayer of type PLAYER containing the number of radarsweep used and opposingPlayer of type PLAYER containing the grid and smoke grid, reference to the input of type INPUT containing the coordinates of the 2x2 area to be scanned 
         -used radar sweep less than or 3 times
effects: returns 1 if there is a ship for the enemy not covered by smoke or 2 if not.
*/

int RadarSweep(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input){
    //every player is allowed 3 radar sweeps per entire game

    if (currentPlayer->radarSweep >= 3){
        printf("No radar sweeps remaining.\n");
            return ILLEGALMOVE;
    }
    //check the validation of the input
    int row = input->row;
    int col = input->column;
    if (isInBound(input)==0)
    {
        printf("Invalid coordinates\n");
            return ILLEGALMOVE;
    }
    int enemyFound = 0; //creating a boolean if we found it updates to 1
    //checking the 2x2 grid starting from the row and col provided
    // for (int i = row; i < row +2 && i < GRID_SIZE; i++)
    // {
    //     for (int j = col; j < col + 2 && j < GRID_SIZE; j++){
    for(int  i =0 ; i<NUMBEROFSHIPS;i++)
    {

        if(isInBound(input))
        {
            if (opposingPlayer->grid[input->row][input->column] == 'X')
            {
                if(opposingPlayer->smokeGird[input->row][input->column]!='X') //check if its not hidden by smoke
                {
                    enemyFound = 1;
                    break; //we exist the loop when we find an enemy
                }
                
            }
        }
        updateCoordBySquare(input,i);
    }
    //displaying the result of the move
    if (enemyFound)
    {
        printf("Enemy ships found\n");
        currentPlayer->radarSweep++; //adding to check after if it exceeds 3

        return SHIPSFOUND;


    }
    else
    {
        printf("No enemy ships found\n");
        currentPlayer->radarSweep++; //adding to check after if it exceeds 3

        return SHIPSNOTFOUND;
    }
    
}