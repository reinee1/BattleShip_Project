#include "../headerFile.h"
/*void fireMove(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input)
requires: reference to the current player of type Player containing the hitsAndMissesGrid and the opposing player of type PLAYER containing the grid, input of type INPUT containing the coordinaes of the target to fire at 
effects: returns if it is hit twice or once, or missed twice or once
*/
void fireMove(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input)
{
 
    //extracting the row and col from input
    int row = input->row;
    int col = input->column;
  //  printf("%d", row); debug line
    
    //checking validation
    if (isInBound(input)==0)
    {
        printf("Invalid coordinates\n");
            return;
    }

    // Check hit or miss
    if (opposingPlayer->grid[row][col] == 'X')
    {
        if(currentPlayer->hitsAndMissesGrid[row][col]=='*')
        {
            printf("congrats on hitting the same place twice!\n");
            return;
        }
        printf("Hit!\n");
        currentPlayer->hitsAndMissesGrid[row][col] = '*'; // Mark the location of the hit
        currentPlayer->lastHit.row = row;
        currentPlayer->lastHit.col = col;
        addHitOnShip(currentPlayer,opposingPlayer,input);
    }
    else
    {
        if(currentPlayer->hitsAndMissesGrid[row][col]=='o')
        {
            if(difficulty=EASY)
            {
                printf("why?\n");
                return;
            }
        }
        printf("Miss.\n");
       currentPlayer->hitsAndMissesGrid[row][col] = 'o'; // Mark the miss
    }
}

//function to register a hit on the ship for the player
/*void addHitOnShip(PLAYER* currentPlayer,PLAYER* opposingPlayer, INPUT* input)
requires: reference to the current player who is firing the shot of type PLAYER, reference to the opposing player who is being attacked of type PLAYER, input of type INPUT containing the coordinates for the shot
effects: increament the hit count for the shotten ship, and return if it has fallen
*/
void addHitOnShip(PLAYER* currentPlayer,PLAYER* opposingPlayer, INPUT* input)
{

    int hitCoord = input->row*10+input->column; //converting coordinates to integers
    SHIP* currentShip ;
    //loop over each ship 
    for(int  i =0;i< NUMBEROFSHIPS; i++)
    {
        currentShip= &opposingPlayer->ships[i];
        if(currentShip->hasFallen==1) //skip if the ship has fallen
        {
            continue;
        }

        for(int  j = 0 ; j < currentShip->size;j++)
        {

            if(currentShip->coord[j]==hitCoord)
            {
                currentShip->hits++;

                if(currentShip->hits == currentShip->size)
                {
                    for (int i = 0; i < currentShip->size; i++) {
                    int coord = currentShip->coord[i];  // Get the coordinate in row * 10 + col format
                    
                    int row = coord / 10;  // Extract the row (integer division)
                    int col = coord % 10;  // Extract the column (modulo 10)

                    // Update the shipsSunkGrid to mark this cell as part of the sunk ship
                    currentPlayer->shipSunkGrid[row][col] = 1;  // Mark as sunk
                    
                    }
                    printf("%s has fallen!\n",currentShip->name); //ship is destroyed
                    currentShip->hasFallen=1;
                    shipFallen(currentPlayer,opposingPlayer,input); //reprecussions of a fallenSHIP


                }
                
            }
        }

        
    }
}

/*void shipFallen(PLAYER* currentPlayer,PLAYER* opposingPlayer, INPUT* input)
requires: reference to the current player who is firing the shot of type PLAYER, reference to the opposing player who is being attacked of type PLAYER, input of type INPUT containing the coordinates for the shot, the ship should be sunk
effects: decremente the number of ships left, unlock artillery moves, and if the opponent has only 1 ship left, toperdo becomes available
*/
void shipFallen(PLAYER* currentPlayer,PLAYER* opposingPlayer, INPUT* input)
{
    
    opposingPlayer->shipsLeft--;
    currentPlayer->artillery =1;

    if(opposingPlayer->shipsLeft==1)
    {
        currentPlayer->torpedo=1;
    }
}