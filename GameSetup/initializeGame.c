#include "../headerFile.h"
/*void assignStartingPlayer(PLAYER * player1, PLAYER * player2)
requires: reference to player1 and player2 of type PLAYER containing the name of each player
effects: returns the name of the player who will start
*/
void assignStartingPlayer(PLAYER * player1, PLAYER * player2)
{

    char temp[50];
    
    srand(time(NULL));
    int randomNumber=rand()%2; //create random number 
    if(randomNumber==0) //chooses randoml which player to start
    {
        printf("The first player is %s\n",player2->name);
        strcpy(temp,player1->name);
        strcpy(player1->name,player2->name);
        strcpy(player2->name,temp);

        //switch if bot
        player1->isBot = player2->isBot;
        player2->isBot = 0;
        
        
        
        
    }else
    {
        printf("The first player is %s\n", player1->name);
    }
}

/*void initializeProbGrid(int probGrid[GRID_SIZE][GRID_SIZE])
requires: probgrid of type int
effects: set all elements in the grid to 0
*/
void initializeProbGrid(int probGrid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            probGrid[i][j] = 0;  // Set all elements to 0
        }
    }
}

/*void initializeGrid(char grid[GRID_SIZE][GRID_SIZE])
requires: grid of type char
effects: set each element in the grid to '~'
*/
void initializeGrid(char grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = '~';
        }
    }
}


/*int getDifficultyLevel()
requires: nothing
effects: return 0 if its easy, 1 if it is hard
*/
int getDifficultyLevel()
{
   INPUT input;
   

    while(1)
    {
        printf("Enter a difficulty level:");
        getInput(&input);
    
        if(strcasecmp(input.moveName, "easy") == 0){
            return 0;
        }else if(strcasecmp(input.moveName, "hard")==0) {
            return 1;
        }else if(strcasecmp(input.moveName, "medium")==0) {
            return 2;
        }
        else{
        printf("difficulty level unknow, try again.\n");
        }

    }

    printf("\n");
}


/*
requires: array of character to indicates the name, size of it and number to indicates if the player is 1 or 2
effects: take the name of the player from the input
*/
void getName(char* name, int size)
{
    printf("Please enter name of Player 1 (%d max characters): ", size);
    fgets(name, size, stdin);
    clearInput(name, size);

    for (int i = 0; i < size; i++) // Remove newline character if present
    {
        if (name[i] == '\n')
        {
            name[i] = '\0';
        }
    }
}
/*
requires: player of type PLAYER, number to know if he is player 1 or 2
effect: initialize grids of the player
*/
void initializePlayer(PLAYER* player)
{
    initializeGrid(player->grid);
    initializeGrid(player->hitsAndMissesGrid);
    initializeGrid(player->smokeGird);

    initializeProbGrid(player->shipSunkGrid);
    initializeProbGrid(player->probGrid);

    
    getName(player->name, sizeof(player->name));
    
    

    player->shipsLeft = NUMBEROFSHIPS;
    player->smokeScreenCounter = 0;
    player->radarSweep = 0;
    player->artillery = 0;
    player->torpedo = 0;
    player->isBot =0;
    player->hitsBeforeShipSunk = 0;

    player->lastHit.row = -1;
    player->lastHit.col = -1;
}
