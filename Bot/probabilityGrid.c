#include "../headerFile.h"


/************************************
    To calculate the probabilty GRID
*************************************/

/*
requires: two integer parameters row and column, representing the coordinates to be checked.
        
effects:  Returns 1 if the coordinates (`row`, `column`) are within the bounds of the grid.
          Returns 0 if the coordinates are out of bounds.
*/
int isInBound2(int row, int column) {
    if (row < 0 || row >= GRID_SIZE) {
        return 0;
    }

    if (column < 0 || column >= GRID_SIZE) {
        return 0;
    }

    return 1;
}

/*
requires: reference to the current player of type PLAYER which includes the `hitsAndMissesGrid` representing the game grid.
          a reference to the input of type INPUT containing the target coordinates
          the size of the ship to check for, which includes how many consecutive cells to check horizontally or vertically.
effects: Returns  1 if a hit is detected horizontally  or if the check goes out of bounds or a miss is detected in EASY mode.
         Returns  0 if no hit or miss is detected after checking the full horizontal length of the ship.

*/
int foundHitHorizontal(int row, int col, int shipSize, PLAYER* currentPlayer) {
    for (int colShift = 0; colShift < shipSize; ++colShift) {
        if (!isInBound2(row, col + colShift)) {
            return 1;  // Out of bounds, stop checking
        }
        if (currentPlayer->hitsAndMissesGrid[row][col + colShift] == '*') {
            return 1;  // A hit is detected
        }
        if(difficulty==EASY)
        {
            if(currentPlayer->hitsAndMissesGrid[row][col+colShift]=='o')
            {
                return 1; //there was a miss
            }
        }
    }
    return 0;  // No hit detected
}

/*
requires: reference to the current player of type PLAYER which includes the `hitsAndMissesGrid` representing the game grid.
          a reference to the input of type INPUT containing the target coordinates 
          the size of the ship to check for, which includes how many consecutive cells to check horizontally or vertically.
effects: Returns  1 if a hit is detected vertically or if the check goes out of bounds or a miss is detected in EASY mode.
         Returns  0 if no hit or miss is detected after checking the full vertical length of the ship.

*/
int foundHitVertical(int row, int col, int shipSize, PLAYER* currentPlayer) {
    for (int rowShift = 0; rowShift < shipSize; ++rowShift) {
        if (!isInBound2(row + rowShift, col)) {
            return 1;  // Out of bounds, stop checking
        }
        if (currentPlayer->hitsAndMissesGrid[row + rowShift][col] == '*') {
            return 1;  // A hit is detected
        }

        if(difficulty==EASY)
        {
            if(currentPlayer->hitsAndMissesGrid[row+rowShift][col]=='o')
            {
                return 1; //there was a miss
            }
        }
    }
    return 0;  // No hit detected
}
/*
requires: a reference to currentPlayer  which includes the probability grid.
          probabilty grid of current player represents the probility of having an opponent's ship in each square
          a reference to opposingPlayer which includes the list of ships .
          
effects:   Iterates through each potential grid position for horizontal and vertical placements of ships.
           If a position does not contain a hit or miss for that ship's placement, the function updates the `probGrid` of the current player to increase the probability of a ship being placed at that location.       
*/
void calculateProbability(PLAYER* currentPlayer, PLAYER* opposingPlayer) {
    // printf("Calculating probability...\n");
    // printf("BEFOOOOOOOOOOR");
    printGridInt(currentPlayer->probGrid);

    int currentProbGrid[GRID_SIZE][GRID_SIZE] ={0};

    // initializeProbGrid(currentPlayer->probGrid);
    for (int shipIndex = 0; shipIndex < NUMBEROFSHIPS; ++shipIndex) {
        SHIP currentShip = opposingPlayer->ships[shipIndex];

        // Only consider ships that have not fallen
        if (currentShip.hasFallen == 0) {
            int currentShipSize = currentShip.size;

            // Loop through every possible cell in the grid
            for (int row = 0; row < GRID_SIZE; ++row) {
                for (int col = 0; col < GRID_SIZE; ++col) {
                    
                    
                    if(currentPlayer->probGrid[row][col]<0) //to make sure not to overwrite that i am sure a ship might be there can be there
                    {
                        currentProbGrid[row][col]==-1;
                        continue;
                    }
                    int foundHit = 0;

                    // Check for horizontal placement
                    if (!foundHitHorizontal(row, col, currentShipSize, currentPlayer)) {
                        // Update probability grid if no hit was found
                        if (isInBound2(row, col + currentShipSize - 1)) {  // Ensure horizontal ship can fit
                            for (int colShift = 0; colShift < currentShipSize; ++colShift) {
                                ++currentProbGrid[row][col + colShift];
                            }
                        }
                    }

                    // Reset found hit for vertical check
                    foundHit = 0;

                    // Check for vertical placement
                    if (!foundHitVertical(row, col, currentShipSize, currentPlayer)) {
                        // Update probability grid if no hit was found
                        if (isInBound2(row + currentShipSize - 1, col)) {  // Ensure vertical ship can fit
                            for (int rowShift = 0; rowShift < currentShipSize; ++rowShift) {
                                ++currentProbGrid[row + rowShift][col];
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if(currentPlayer->probGrid[i][j]!=-1)
            {
            currentPlayer->probGrid[i][j] = currentProbGrid[i][j];
            }
        }
    }



  
}



/*
requires: grid representing the  the sum is to be calculated.
          int i which is the starting row index of the 2x2 grid.
          int  j which is the starting column index of the 2x2 grid.

effects:  returns an the sum of the values of the 2x2 grid starting at the position `(i, j)`.
*/

int calculateSum(int grid[GRID_SIZE][GRID_SIZE], int i, int j) {
    int sum = 0;

    // Iterate through the 2x2 grid
    for (int row = i; row < i + 2; row++) {
        for (int col = j; col < j + 2; col++) {
            // Only add values if they are within bounds
            if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
                sum += grid[row][col];
            }
        }
    }
    return sum;
}
/*
requires: grid on which the sum of 2x2 sub-grids will be calculated.
          an array of `Coord` structures that will store the coordinates of the 2x2 sub-grids with the maximum sum
effects: The function rthe number of coordinates in the `coords` array that have the maximum sum. This value is stored in `count`.
*/

int findMaxSumCoords(int grid[GRID_SIZE][GRID_SIZE], Coord coords[MAX_COORDS]) {
    int maxSum = -1;  // To store the maximum sum found
    int count = 0;    // To track the number of coordinates with the max sum

    // Iterate over all possible starting coordinates for the 2x2 grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int sum = calculateSum(grid, i, j);  // Calculate sum of 2x2 grid starting at (i, j)

            // If the sum is greater than the current max, update the max and reset the list of coordinates
            if (sum > maxSum) {
                maxSum = sum;
                count = 0;  // Reset the list of coordinates
                coords[count].row = i;
                coords[count].col = j;
                count++;
            }
            // If the sum is equal to the current max, add the coordinate to the list
            else if (sum == maxSum) {
                coords[count].row = i;
                coords[count].col = j;
                count++;
            }
        }
    }

    return count;  // Return the number of coordinates with the maximum sum
}


/*
requires: probability grid where each element holds a value that will be used to calculate the sum for 2x2 sub-grids.
effects: The function returns a `squareCoords` structure, which includes the size of the maximum sum coordinates and the coordinates themselves in the maxCoords array.
*/
squareCoords getSquareCoord(int probGrid[GRID_SIZE][GRID_SIZE]) {
    
    squareCoords squareCoord;  // Create a squareCoords structure
    squareCoord.size = 0;      // Initialize size to 0

    // Call the function to find all coordinates with the max sum
    squareCoord.size = findMaxSumCoords(probGrid, squareCoord.maxCoords);

    return squareCoord;
}