#include "../headerFile.h"
//this function hide a 2x2 area on the player's grid
/*void smokeScreen(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input )
requires: reference to the current player containing the smokeGrid and opposing player of type PLAYER containing the number of ships left, reference to the input containing the coordinates for the top-left corner of the 2x2 to be obscured
          smoke screen should be used less than the number of ships the player has sunk
effects: obscure the area of the indicated coordinates
*/
void smokeScreen(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input )
{   //calculating the number of lost ships
    int shipsSunk = NUMBEROFSHIPS- opposingPlayer->shipsLeft;
    //check if the player has used this function >= to the number of sunk ships
    if(currentPlayer->smokeScreenCounter>= shipsSunk)
    {
        printf("You cannot hide more than you have sunk ships!Stand Strong\n!");
        return;
    }
    else if (isInBound(input)==0)
    {
        printf("Invalid coord\n");
        return;
    }
    else
    {

        int hiddenSquares = 0; // counter for squares that are hidder successfully
         //looping from the given coordinates
        for(int i = 0 ; i < NUMBEROFSHIPS ; i++)
        {
            if(isInBound(input))
            {
                currentPlayer->smokeGird[input->row][input->column]='X';
                hiddenSquares++;
            }

            updateCoordBySquare(input, i);
        }
        //check if no squares were hidden
        if(hiddenSquares==0)
        {
            printf("let it be known that you have hidden absolutely no square, great job!\n");
            return;
        }
        
    }
    system("cls");
    printf("\n");

    //increament the counter to track the number of times this move has been used
    currentPlayer->smokeScreenCounter++;

    
}