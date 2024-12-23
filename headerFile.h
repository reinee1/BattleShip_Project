#ifndef HEADERFILE_H
#define HEADERFILE_H

//FOR ALL FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// TO REMOVE CLEARING INPUT OVERFLOW CHANGE TO 0
#define INPUTOVERFLOW 1


//for INPUT.C
#define INPUT struct Input
struct Input
{
    char orientation[10];
    char moveName[10];

    int column;
    int row;
    int valid;
};
void getInput(struct Input*);
void getInputForPlacingShips(struct Input*);
int getColumn(char);
int getOrientation(char*);
int getDigit(char);
int getRow(char*, int,int);
int getTrailingCharachterIndex(char*, int );
int getLeadingCharachterIndex(char* , int );
void clearInput(char* , int);
int isInBound(INPUT*);
void updateCoordBySquare(struct Input* input ,int iteration);



//for initialize_game
#define MAX_COORDS 100 // Maximum possible number of coordinates (for 10x10 grid)
#define GRID_SIZE 10
#define NUMBEROFSHIPS 4
#define EASY 0
#define HARD 1
#define SHIP struct Ship
#define PLAYER struct Player
extern int difficulty ;

typedef struct {
    int row;
    int col;
} Coord;

typedef struct {
    Coord maxCoords[MAX_COORDS];
    int size;
} squareCoords; 

struct Ship
{
    char name[15];
    int coord[6];
    int hits;
    int size;
    int hasFallen;
};


struct Player
{
    char grid[GRID_SIZE][GRID_SIZE]; 
    char hitsAndMissesGrid[GRID_SIZE][GRID_SIZE];
    int shipSunkGrid[GRID_SIZE][GRID_SIZE];
    char smokeGird[GRID_SIZE][GRID_SIZE];
    int probGrid[GRID_SIZE][GRID_SIZE];
    
    char name[50];
    SHIP ships[NUMBEROFSHIPS];
    int shipsLocations[NUMBEROFSHIPS][4];
    
    int shipsLeft;
    int smokeScreenCounter;
    int radarSweep;

    int torpedo;
    int artillery;

    int isBot;
    Coord lastHit;
    int hitsBeforeShipSunk; //counts the number of consecutive hits before we sink an opponent ship
};


int game(PLAYER* player1, PLAYER* player2,int turnNumber);
void initializePlayer(PLAYER* player);
void initializeProbGrid(int probGrid[GRID_SIZE][GRID_SIZE]);
void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]);
void assignStartingPlayer(PLAYER*,PLAYER*);
int getDifficultyLevel();
void getName(char*, int);
void initializeGridHelper(char[GRID_SIZE][GRID_SIZE],char[GRID_SIZE][GRID_SIZE],char[GRID_SIZE][GRID_SIZE]);






//for place_ships.C
#define HORIZONTAL 0
#define VERTICAL 1
void placeShips(PLAYER* );
void printGrid(char grid[GRID_SIZE][GRID_SIZE]);
void printGridInt(int grid[GRID_SIZE][GRID_SIZE]);

int checkBounds2(PLAYER* ,INPUT*,int );
void placeShipsHuman(PLAYER* player);
int isInCorner(int row, int col, int shipSize, int orientation, int allowCornerPlace);
int IsadjacentShips(PLAYER *player, int row, int col, int shipSize, int orientation);
void placeShipsMedium(PLAYER* player);
void placeShipsEasy(PLAYER* player);
void placeShipsHard(PLAYER* player);
int checkBounds(PLAYER* currentPlayer,int row, int col,int shipSize, int orientation);
void addShip(PLAYER* currentPlayer, const char* name,int shipSize, int row, int col, int orientation);


//for firemove.c

void fireMove(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input);
void addHitOnShip(PLAYER*, PLAYER* , INPUT*);
void shipFallen(PLAYER* currentPlayer,PLAYER* opposingPlayer, INPUT* input);


//for smoke_screen.C
void smokeScreen(PLAYER*,PLAYER*,INPUT*);

// for radarSweep.c
#define ILLEGALMOVE 0
#define SHIPSFOUND 1
#define SHIPSNOTFOUND 2
int RadarSweep(PLAYER*,PLAYER*,INPUT*);

//for torpedo.c
void torpedo(PLAYER*,PLAYER*,INPUT*);

//for arilleryMove.c
void checkArtillery(PLAYER* currentPlayer);
void artilleryMove(PLAYER* currentPlayer, PLAYER* opposingPlayer,INPUT* input);


//FOR BOT

//for handleTorpedo
void handleTorpedo(PLAYER* currentPlayer, PLAYER* opposingPlayer);

//for handleArtillery
void handleArtillery(PLAYER *currentPlayer, PLAYER *opposingPlayer);

//for botThinking.c
void botThinking(PLAYER *currentPlayer, PLAYER *opposingPlayer);


//FOR  probabilityGrid.c

int isInBound2(int row,int column);
void calculateProbability(PLAYER* currentPlayer, PLAYER* opposingPlayer);
int calculateSum(int grid[GRID_SIZE][GRID_SIZE], int i, int j) ;
int findMaxSumCoords(int grid[GRID_SIZE][GRID_SIZE], Coord coords[MAX_COORDS]);
squareCoords getSquareCoord(int probGrid[GRID_SIZE][GRID_SIZE]) ;

//FOR HandleRadar
int handleRadar(PLAYER *currentPlayer, PLAYER *opposingPlayer);

//for handleFire
// Coord getHighestProbSquare(PLAYER* currentPlayer, PLAYER* opposingPlayer);
// Coord* findHighestProbCoords(PLAYER* currentPlayer, int* count);
// void processSurroundingCell(PLAYER currentPlayer, INPUT input) ;
// void hitOutcome(PLAYER currentPlayer,PLAYER opposingPlayer, INPUT* input,int* opposingShipsStatus,Coord* lastHit);
// void updateCoordByCross(INPUT* input ,int iteration);
// void handleFire(PLAYER* currentPlayer, PLAYER* opposingPlayer);

Coord* countAndSortNegativeCells(PLAYER* currentPlayer, int* negativeCount);
Coord getHighestPositiveProbSquare(PLAYER* currentPlayer);
Coord getHighestProbSquare(PLAYER* currentPlayer, PLAYER* opposingPlayer);
Coord* findHighestProbCoords(PLAYER* currentPlayer, int* count);
void updateProbabilityCross(PLAYER* currentPlayer, int row, int col);
void updateProbOfHit(PLAYER* currentPlayer, int row, int col);
void updateProbabilityGridAroundShip(PLAYER* currentPlayer, INPUT* input, int lastHitRow, int lastHitCol, int SHIPSUNKSIZE);

int checkShipStatusChange(PLAYER* opposingPlayer, int* opposingShipsStatus);
void printShipInfo(PLAYER* opposingPlayer);
void hitOutcome(PLAYER *currentPlayer, PLAYER* opposingPlayer, INPUT* input, int* opposingShipsStatus, Coord* lastHit);

void processSurroundingCell(PLAYER *currentPlayer, INPUT* input);
void updateCoordByCross(INPUT* input, int iteration);
void saveOpposingShipsStatus(PLAYER* opposingPlayer, int* opposingShipsStatus);
void handleFire(PLAYER* currentPlayer, PLAYER* opposingPlayer);


#endif
