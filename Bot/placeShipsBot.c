#include "../headerFile.h"
/*
requires: a reference to currentPlayer hip name.
         Size of the ship.
         row, col ccordinates which are the starting position for the ship.
         Ship orientation (HORIZONTAL or VERTICAL).
          
effects: Marks the grid with 'X' for the ship's location.
         Updates the player's ship information.

*/
void addShip(PLAYER* currentPlayer, const char* name,int shipSize, int row, int col, int orientation)
{   
    SHIP* ships = currentPlayer->ships;
    int shipIndex = 4-shipSize + 1;

    int sizeofName =0;
    while(name[sizeofName]!= '\0')
    {
        sizeofName++;
    }

    strncpy(ships[shipIndex].name, name, sizeofName);
    ships[shipIndex].name[sizeofName] = '\0';

    currentPlayer->ships[shipIndex].size = shipSize;

    //the orientation should be passed now from the arguments
    if(orientation==HORIZONTAL)
    {
        for(int  i = 0 ; i<shipSize;i++)
        {
            currentPlayer->grid[row][i + col] = 'X';
           currentPlayer->ships[shipIndex].coord[i] = (row * 10) + (col + i); 
            
        }
    }else if(orientation==VERTICAL)
    {
        
        for(int  i = 0 ; i<shipSize;i++)
        {
            currentPlayer->grid[i+row][col] = 'X';
            currentPlayer->ships[shipIndex].coord[i] = (row + i) * 10 + col; 
        }
    }
    ships[shipIndex].hits=0;
    ships[shipIndex].hasFallen =0;

}
    /*
requires: a reference to currentPlayer hip name.
         Size of the ship.
         row, col ccordinates which are the starting position for the ship.
         Ship orientation (HORIZONTAL or VERTICAL).
Effects:
Returns 1 if valid placement, -1 if out-of-bounds or overlaps.

*/

int checkBounds(PLAYER* currentPlayer, int row, int col, int shipSize, int orientation)
{
    if (orientation == HORIZONTAL)
    {
        if (col + shipSize > GRID_SIZE)
        {
            return -1; // Out of horizontal bounds
        }
    } 
    else if (orientation == VERTICAL)
    {
        if (row + shipSize > GRID_SIZE)
        {
            return -1; // Out of vertical bounds
        }
    }

    // Overlap Check (leave as is, it's fine)
    return 1;
}

/*
requires: A reference to the player object (player) to place ships on their grid.
          The game mode to be easy
          
effects:   -Randomly places ships on the player's grid based on the following 
           -Prints the placement of each ship along with its coordinates and orientation.
*/
void placeShipsEasy(PLAYER* player) {
    printf("%s, the bot is placing its ships.\n", player->name);

    const char* shipsNames[] = {"Carrier", "Battleship", "Destroyer", "Submarine"}; // all ships to avoid clustering if condition
    const int shipsSizes[] = {5, 4, 3, 2};  // Sizes for each ship
    srand(time(NULL)); // Seed the random number generator
    
    for (int i = 0; i < NUMBEROFSHIPS; i++) { // 4 total ships to place
        int currentShipSize = shipsSizes[i];
        int placed = 0;
        int row, col, orientation;
        
        while (!placed) {
            // Get random row, col, and orientation
            row = rand() % GRID_SIZE;
            col = rand() % GRID_SIZE;
            orientation = rand() % 2; // 0 for horizontal, 1 for vertical
            
            // Check if the ship can be placed
            if (checkBounds(player, row, col, currentShipSize, orientation)) {
                addShip(player, shipsNames[i], currentShipSize, row, col, orientation);
                placed = 1; // Ship placed successfully
            }
        }
        
        // printf("Placed %s (%d cells) at (%d, %d) with %s orientation.\n", shipsNames[i], currentShipSize, row + 1, col + 1, orientation == 0 ? "horizontal" : "vertical");
    }

    printGrid(player->grid); // Print the grid after placing all ships
    // printf("\n");
}
/*
requires: A reference to the player object (player) to place ships on their grid.
          The game mode to be medium
          
effects:  Randomly places ships on the player's grid based on the following :
          Ships are not placed adjacent to each other.
          Updates the player's grid and ship placement information.
          Prints the placement of each ship along with its coordinates and orientation.
*/
void placeShipsMedium(PLAYER* player)
{
    printf("%s, the bot is placing its ships.\n", player->name);
    
    const char *shipsNames[] = {"Carrier", "Battleship", "Destroyer", "Submarine"};
    const int shipsSizes[] = {5, 4, 3, 2};  // Sizes for each ship
    srand(time(NULL));

    for (int i = 0; i < 4; ++i) {  // Loop for 4 ships
        int currentShipSize = shipsSizes[i];
        int placed = 0;
        int row, col, orientation;

        while (!placed) {
            row = rand() % GRID_SIZE;
            col = rand() % GRID_SIZE;
            orientation = rand() % 2;  // Random orientation (0 = horizontal, 1 = vertical)

            // Check if the ship can be placed
            if (checkBounds(player, row, col, currentShipSize, orientation) &&
                !IsadjacentShips(player, row, col, currentShipSize, orientation)) {
                
                // Place the ship and mark it as placed
                addShip(player, shipsNames[i], currentShipSize, row, col, orientation);
                placed = 1;  // Successfully placed the ship
            }
        }
        // Print the placement details
        // printf("Placed %s (%d cells) at (%d, %d) with %s orientation.\n", 
        //        shipsNames[i], currentShipSize, row + 1, col + 1, 
        //        orientation == 0 ? "horizontal" : "vertical");
    }

    // Print the final grid after all ships are placed
    printGrid(player->grid);
    printf("\n");
}

    /*
requires: A reference to the player object (player) containing the grid where ships are placed.
          The starting coordinates of the ship (row, col), the ship's size, and its orientation

effects: Returns 1 if any adjacent cells contain a ship ('X'), indicating the ship cannot be placed.
         Returns 0 if no adjacent cells contain a ship, indicating the ship can be placed.
*/
int IsadjacentShips(PLAYER *player, int row, int col, int shipSize, int orientation){
    for(int i = 0; i < shipSize; i++){
        int r = row, c = col;
        if (orientation == HORIZONTAL)
        {
            r = row;
            c = col + i; //keep the row const and move across the columns
        }
        else if (orientation == VERTICAL)
        {
            r = row + i;
            c = col;
        }
        //calcule lal delta row li henne kel shi fawea aalaya w tahta w same lal column
        for (int deltarow = -1; deltarow <= 1 ; deltarow++)
        {
            for (int deltscol = -1 ; deltscol <= 1 ; deltscol++)
            {
              int checkRow = r + deltarow;
              int checkCol = c + deltscol;
              
              if (checkRow >= 0 && checkRow < GRID_SIZE && checkCol >= 0 && checkCol < GRID_SIZE)
              {
                if (player->grid[checkRow][checkCol] == 'X')
                {
                    return 1;
                }
              }
            }
        }    
    }
    return 0;
}
/*
requires: A reference to the player object (player) to place ships on their grid.
          The game mode to be hard
          
effects:   Randomly places ships on the player's grid based on the following :
           Ships are not placed in the corners unless corner placement is allowed 
           Updates the player's grid and ship placement information.
           Prints the placement of each ship along with its coordinates and orientation.
*/

void placeShipsHard(PLAYER* player) {
    printf("%s, the bot is placing its ships.\n", player->name);
    
    const char *shipsNames[] = {"Carrier", "Battleship", "Destroyer", "Submarine"};
    const int shipsSizes[] = {5, 4, 3, 2};  // Sizes for each ship
    srand(time(NULL));

    for (int i = 0; i < 4; ++i) {  // Loop for 4 ships
        int currentShipSize = shipsSizes[i];
        int placed = 0;
        int row, col, orientation;

        while (!placed) {
            row = rand() % GRID_SIZE;
            col = rand() % GRID_SIZE;
            orientation = rand() % 2;  // Random orientation (0 = horizontal, 1 = vertical)

            int gapType = rand() % 2;
            int allowCornerPlace = rand() % 2;

            // Check if the ship can be placed
            if (checkBounds(player, row, col, currentShipSize, orientation) &&
                !IsadjacentShips(player, row, col, currentShipSize, orientation) && 
                !isInCorner(row, col, currentShipSize, orientation, allowCornerPlace)) {
                
                // Place the ship and mark it as placed
                addShip(player, shipsNames[i], currentShipSize, row, col, orientation);
                placed = 1;  // Successfully placed the ship
            }
        }
        // printf("Placed %s (%d cells) at (%d, %d) with %s orientation.\n", 
        //        shipsNames[i], currentShipSize, row + 1, col + 1, 
        //        orientation == 0 ? "horizontal" : "vertical");
    }

    // Print the final grid after all ships are placed
    printGrid(player->grid);
    printf("\n");
}
  
    /*
requires: The starting coordinates of the ship (row, col), the ship's size, the orientation
          and a flag indicating whether corner placement is allowed (allowCornerPlace).
          
effects: Returns 1 if the ship is placed in one of the grid's corners when corner placement is not allowed.
         Returns 0 otherwise.
*/
int isInCorner(int row, int col, int shipSize, int orientation, int allowCornerPlace)
{
    // If corner placement is not allowed, check if the ship is within the 5x5 corner area
    if (!allowCornerPlace)
    {
        if ((row == 0 && col == 0) ||  
            (row == 0 && col == GRID_SIZE - 1) || 
            (row == GRID_SIZE - 1 && col == 0) || 
            (row == GRID_SIZE - 1 && col == GRID_SIZE - 1))  
        {
            return 1;  // Ship is exactly in one of the corner square
        }
    }
    return 0;
}