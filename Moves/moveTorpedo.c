#include "../headerFile.h"
/*void torpedo(PLAYER* currentPlayer, PLAYER* opposingPlayer, INPUT* input)
requires: reference to the current player and the opposing player of type PLAYER, which each contains their grid and other information (hitsandMissesGrid, smoke grid...)
         the player must have unlocked the torpedo move
         input indicating the target (col of row)
effects: returns if the move on the specified row or col is a miss or a hit and updates the grids * if it is a hit and o if miss
*/
void torpedo(PLAYER* currentPlayer, PLAYER* opposingPlayer, INPUT* input) {
    // check if torpedo can be used: allow only if not used and condition met

    
    if (currentPlayer->torpedo!=2) {
        printf("conditions are not met.\n");
        return;
    }
    // handeling cases where row or column is -1
    if (input->row == -1 && input->column == -1) {
        printf(" row and column are out of bounds.\n");
        return;
    }

// Targeting an entire row if column = -1
if (input->column == -1) 
{
    if (input->row < 0 || input->row >= GRID_SIZE) {
        printf("Invalid row index.\n");
        return;
    }
    for (int col = 0; col < GRID_SIZE; col++) {  // Loop through each column
        if (opposingPlayer->grid[input->row][col] == 'X') { 
            
            if(currentPlayer->hitsAndMissesGrid[input->row][input->column]!='*') // so to avoid multiple hts and marks
            {
                    currentPlayer->hitsAndMissesGrid[input->row][input->column] = '*'; // Mark the location of the hit
                    addHitOnShip(currentPlayer, opposingPlayer,input); //update the hit count of the ship
               
            }
            // printf("Hit at row %d, col %d\n", input->row, col);
        } else {
            currentPlayer->hitsAndMissesGrid[input->row][col] = 'o'; // Mark miss
            // printf("Miss at row %d, col %d\n", input->row, col);
        }
    }
}
// Targeting an entire column if row = -1
else if (input->row == -1) 
{
    if (input->column < 0 || input->column >= GRID_SIZE) {
        printf("Invalid column index.\n");
        return;
    }
    for (int row = 0; row < GRID_SIZE; row++) { // Loop through each row
        if (opposingPlayer->grid[row][input->column] == 'X') {
            input->row=row;

            if(currentPlayer->hitsAndMissesGrid[input->row][input->column]!='*') // so to avoid multiple hts and marks
            {
                    currentPlayer->hitsAndMissesGrid[input->row][input->column] = '*'; // Mark the location of the hit
                    addHitOnShip(currentPlayer, opposingPlayer,input); //update the hit count of the ship
               
            }

            // printf("Hit at row %d, col %d\n", row, input->column);
        } else {
            currentPlayer->hitsAndMissesGrid[row][input->column] = 'o'; // Mark miss
            // printf("Miss at row %d, col %d\n", row, input->column);
        }
    }


    } else {
        printf("Invalid direction. Use 'R' for row or 'C' for column\n");
        return;
    }

}
/*void checkTorpedo(PLAYER* currentPlayer)
requires: reference to the current player of type PLAYER to check its torpedo
effects: returns if we unlock torpedo move or reset it
*/
void checkTorpedo(PLAYER* currentPlayer)
{
    if(currentPlayer ->torpedo==2)
    {
        currentPlayer->torpedo =0;
    }
   if(currentPlayer->torpedo ==1)
    {
        printf("Special move unlocked for 1 turn: torpedo!\n");
        currentPlayer->torpedo=2;
    }
}