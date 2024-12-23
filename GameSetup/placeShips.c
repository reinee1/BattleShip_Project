#include "../headerFile.h"

/*
  requires:
    - currentPlayer: a pointer to the PLAYER structure representing the current player.
    - input: a pointer to the INPUT structure containing the starting coordinates and orientation for placing the ship.
    - shipSize: an integer representing the size (length) of the ship to be placed.

  effects:
    - 1 if the placement is valid (within bounds and no overlap).
    - -1 if the placement is invalid due to being out of bounds or overlapping with another ship.
*/
int checkBounds2(PLAYER* currentPlayer,INPUT* input,int shipSize)
{
    int orientation = getOrientation(input->orientation);
   if(orientation==HORIZONTAL)
    {
        if(input->column + shipSize >GRID_SIZE)
        {
            printf("Ship is out of bound\n");
            return -1;
        }
    }else if(orientation ==VERTICAL)
    {
        if(input->row+shipSize > GRID_SIZE)
        {
            printf("Ship is out of bound\n");
            return -1;
        }
    }

    if(orientation==HORIZONTAL)
    {
        for(int  i = 0 ; i<shipSize;i++)
        {
            if(currentPlayer->grid[input->row][input->column+i] != '~')
            {
                printf("ships overlap\n");
                return -1;
            }
        }
    }else if(orientation==VERTICAL)
    {
        
        for(int  i = 0; i<shipSize;i++)
        {
            if(currentPlayer->grid[i+input->row][input->column] != '~')
            {
                printf("ships overlap\n");
                return -1;
            }
        }
    }

    return 1;



}
/*
  requires:
    - a pointer to the PLAYER current player.
    - Collects user input for the starting coordinates and orientation (horizontal or vertical) of each ship.

  effects: displays the added ships on the grid dependinding on their coordinates for human input .
*/
void placeShipsHuman(PLAYER* player)
{
    // Define the ship names and their respective sizes
    const char *shipsNames[] = {"Carrier", "Battleship", "Destroyer", "Submarine"};
    const int shipsSizes[] = {5, 4, 3, 2};  // Sizes for each ship

    printf("%s, please enter your ships coordinates.\n", player->name);
    printf("First, start with the square (e.g., A10), then the orientation (horizontal, vertical).\n");

    for (int i = 0; i < NUMBEROFSHIPS; i++) // 4 total ships to place
    {
        int currentShipSize = shipsSizes[i]; // Use the predefined sizes

        printf("Where would you like to place your %s (%d cells)?\n", shipsNames[i], currentShipSize);

        INPUT input;
        getInputForPlacingShips(&input); // Get the ship's coordinates and orientation

        // Validate the column coordinate
        if (input.column == -1)
        {
            i--; // Repeat the loop for invalid column
            printf("Please enter a valid column\n");
            continue;
        }

        // Validate the row coordinate
        if (input.row < 0 || input.row > 9)
        {
            printf("Please enter a valid row\n");
            i--; // Repeat the loop for invalid row
            continue;
        }

        // Validate the orientation
        int orientation = getOrientation(input.orientation); // 0 for horizontal, 1 for vertical
        if (orientation == -1)
        {
            printf("Please enter a valid orientation (horizontal or vertical)\n");
            i--; // Repeat the loop for invalid orientation
            continue;
        }

        // Check if the ship can be placed within bounds and doesn't overlap with other ships
        if (checkBounds2(player, &input, currentShipSize) == -1)
        {
            i--; // Repeat the loop for invalid placement
            continue;
        }

        // Add the ship to the player's grid
        addShip(player, shipsNames[i], currentShipSize,input.row,input.column, orientation);

        // Print the current grid after placing the ship
        printGrid(player->grid);
    }

    printf("\n");
}