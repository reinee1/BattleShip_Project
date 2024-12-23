#include "headerFile.h"
/*int getRow(char* input,int startCoord, int whiteSpaceIndex)
requires: input representing coordinates of type string, starting index of the coordinate of type int, index of the 1st space in the string
effects: returns the row number based on the extracted digits 
*/
int getRow(char* input,int startCoord, int whiteSpaceIndex)
{
    if(whiteSpaceIndex-startCoord ==0 || whiteSpaceIndex-startCoord >2) //check if no character entered or more than 2 characters
    {
        return -1;
    }else{
        int row  = 0;
        for(int i = startCoord ; i <whiteSpaceIndex;i++)
        {
            int digit = getDigit(input[i]); //get each digit seperately
            if(digit != -1) 
            {
                row +=digit; //get the row using complexe algorithm that took me 3 hours
                row *=10;
            }else return -1;
            
        }
        row = row/10;
        row--;
        return row;
    }
    

    
}
/*int getDigit(char c)
requires: a character representing the column
effects: returns an integer corresponding to the column
*/
int getDigit(char c)
{
    int digit = c-'0';
    for(int i = 0 ; i <= 9 ; i++)
    {
        if(digit ==i)
        {
            return i;
        }
    }
    return -1;
}
/*void clearInput(char* input, int size)
requires: input of type char*, int size of the input
effects: clear the input buffer
*/
void clearInput(char* input, int size) //removes any overflow in the input
{

    if(INPUTOVERFLOW==0)
    {
        return;
    }
    
    int hasNewLine = 0;
    for(int i = 0 ; i < size; i++) //check if the input has a newline charachter
    {
        if(input[i] =='\n')
        {
            hasNewLine=1;
            break;
        }

    }
    char charachter;
    if(hasNewLine==0)
    {
       
        while(charachter = getchar()!='\n' && charachter!=EOF);
    }
}
/*void printGrid(char grid[GRID_SIZE][GRID_SIZE])
requires: 2d array for the grid
effect: print the grid
*/
void printGrid(char grid[GRID_SIZE][GRID_SIZE])
{
    printf("    A B C D E F G H I J\n");

    for (int i = 0; i < GRID_SIZE; i++)
    {
        if (i != 9){
            printf("%d   ", i + 1);
        }
        else{
             printf("%d  ", i + 1);
        }
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if(difficulty==HARD)
            {
                if(grid[i][j]=='o')
                {
                    printf("~ ");
                }else 
                {
                    printf("%c ", grid[i][j]);
                }
            }else{
                 printf("%c ", grid[i][j]);
            }
           
        }
        printf("\n");
    }
}
/*void printGrid(char grid[GRID_SIZE][GRID_SIZE])
requires: 2d array for the grid
effect: print the grid
*/
void printGridInt(int grid[GRID_SIZE][GRID_SIZE])
{
    printf("    A B C D E F G H I J\n");

    for (int i = 0; i < GRID_SIZE; i++)
    {
        if (i != 9){
            printf("%d   ", i + 1);
        }
        else{
             printf("%d  ", i + 1);
        }
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if(difficulty==HARD)
            {
                if(grid[i][j]=='o')
                {
                    printf("~ ");
                }else 
                {
                    printf("%d ", grid[i][j]);
                }
            }else{
                 printf("%d ", grid[i][j]);
            }
           
        }
        printf("\n");
    }
}
/*int getColumn(char input)
requires: character representing the column (A-J)
effects: returns the integer corresponding to the column
*/
int getColumn(char input)
{
   
        if (input == 'A' || input == 'a') {
        return 0;
    } else if (input == 'B' || input == 'b') {
        return 1;
    } else if (input == 'C' || input == 'c') {
        return 2;
    } else if (input == 'D' || input == 'd') {
        return 3;
    } else if (input == 'E' || input == 'e') {
        return 4;
    } else if (input == 'F' || input == 'f') {
        return 5;
    } else if (input == 'G' || input == 'g') {
        return 6;
    } else if (input == 'H' || input == 'h') {
        return 7;
    } else if (input == 'I' || input == 'i') {
        return 8;
    } else if (input == 'J' || input == 'j'){
        return 9;  
    }else 
    {
        return -1;
    }

}
/*int getOrientation(char* input)
requires: a string representing the orientation of the ship
effects: returns if its horizontal or vertical
*/
int getOrientation(char* input)
 {

    if (strcmp(input, "horizontal") == 0) {
        return HORIZONTAL;
    } else if (strcmp(input, "vertical") == 0) {
        return VERTICAL;
    } else {
        printf("Please enter either 'horizontal' or 'vertical' for the orientation.\n");
        return -1;
    }


   
}
/*void getInputForPlacingShips(INPUT* input)
requires: input of type INPUT containing the row col and orientation
effects: stores the extracted values in the input object
*/
void getInputForPlacingShips(INPUT* input)
{
    char stringInput[20];

    fgets(stringInput,sizeof(stringInput),stdin);
    clearInput(stringInput,sizeof(stringInput));
    //each leading and trailing are the leading and trailing whitespaces respectively

    int leading1 = getLeadingCharachterIndex(stringInput,0);
    int trailing1 = getTrailingCharachterIndex(stringInput,leading1);

    input->column= getColumn(stringInput[leading1]);

    int leading2 = getLeadingCharachterIndex(stringInput, leading1+1);
    int trailing2 = getTrailingCharachterIndex(stringInput,leading2);

    
    input->row = getRow(stringInput, leading2, trailing2);
    
    int leading3 = getLeadingCharachterIndex(stringInput, trailing2);
    int trailing3 = getTrailingCharachterIndex(stringInput,leading3);
    
    for(int i = 0; i < trailing3-leading3;i++)
    {
        input->orientation[i]= stringInput[leading3+i];
        
    }
    input->orientation[trailing3-leading3] = '\0';
    

}

//input for placing ship is the opposit of that to make moves
/*void getInput(INPUT* input)
requires: input of type INPUT storing the name of move and coordinates
effect: extract the move name,row and col

*/
void getInput(INPUT* input)
{
    char stringInput[20];

    fgets(stringInput,sizeof(stringInput),stdin);
    clearInput(stringInput,sizeof(stringInput));

    int leading1 = getLeadingCharachterIndex(stringInput,0);
    int trailing1 = getTrailingCharachterIndex(stringInput,leading1);

    for(int i = 0; i < trailing1-leading1;i++)
    {
        input->moveName[i]= stringInput[leading1+i];
    }
    input->moveName[trailing1-leading1]='\0';

    int leading2 = getLeadingCharachterIndex(stringInput, trailing1);
    int trailing2 = getTrailingCharachterIndex(stringInput,leading2);

    if(strcmp(input->moveName,"torpedo")==0)
    {
        input->row = getRow(stringInput,leading2,trailing2);
        input->column = getColumn(stringInput[leading2]);
        return;
    }
    
    int leading3 = getLeadingCharachterIndex(stringInput, leading2+1);
    int trailing3 = getTrailingCharachterIndex(stringInput,leading3);
    
    input->column= getColumn(stringInput[leading2]);
    input->row = getRow(stringInput, leading3, trailing3);

}
/*int getLeadingCharachterIndex(char*input , int start)
requires: input of type char*, int representing the index which to start with
effects: skips the white spaces
*/
int getLeadingCharachterIndex(char*input , int start)
{
    while(input[start]== ' ')
    {
        start++;
    }

    return start;
}
/*int getTrailingCharachterIndex(char*input, int start)
requires: input of type char* and a int representing the index which to start with
effects: return the index where the first non word character is encountered
*/
int getTrailingCharachterIndex(char*input, int start)
{
    while(input[start]!= ' ' && input[start]!= '\n'&& input[start]!= EOF )
    {
        start++;
    }

    return start;
}

//function to check the validation of the given input
//function to check the validation of the given input
/*int isInBound(INPUT* input)
requires: input of type INPUT containing the row and col coordinates
effects: return 0 if row and col are out of bound, 1 if they are in bound

*/
int isInBound(INPUT* input)
{
     if (input->row < 0 || input->row >= GRID_SIZE) {
        return 0;
    }

    
    if (input->column < 0 || input->column >= GRID_SIZE) {
        return 0;
    }

    return 1;
}


//function to update the coordinates to move around the square area
/*void updateCoordBySquare(struct Input*input ,int iteration)
requires: reference to an INPUT struct, and iterator
effects: update the coordinates to move around the square area
*/
void updateCoordBySquare(struct Input*input ,int iteration)
{
    if(iteration ==0)
    {
        input->column++; //move right
    }else if(iteration ==1)
    { 
        input->row++; //down
    }else if(iteration ==2)
    {
        input->column--; //left

    }else if (iteration == 3) 
    {
        input->row--;    //up even though unecessary
    }
}
