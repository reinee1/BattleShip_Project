#include "../headerFile.h"
#define MAX_COORD_SIZE 10

// Define the maxCoord structure
struct maxCoord {
    int isRow;             // 1 for rows, 0 for columns
    int coords[MAX_COORD_SIZE];    // Coordinates (row or column index)
    int sums[MAX_COORD_SIZE];      // Sum of values in the row or column
    int minusCounters[MAX_COORD_SIZE];  // Counter for negative values (such as -1)
};

/*
requires: A reference to the coord structure of type maxCoord, which contains the following fields:
        indicates if the coordinates are for rows (1) or columns (0).
        An array of coordinate indices.
        An array of sum values corresponding to each coordinate.
        minusCounter which is An array of counters for negative values (-1).
Effects: Prints all fields mentioned above
    
*/
void printCoord(struct maxCoord *coord) {
    if (coord == NULL) {
        printf("Null structure passed.\n");
        return;
    }

    printf("Is Row: %d\n", coord->isRow);  // Print if it's a row (1) or column (0)

    // Print the coordinates, sums, and -1 counters
    printf("Coordinates (Index): ");
    for (int i = 0; i < MAX_COORD_SIZE; i++) {
        if (coord->coords[i] != -1) {  // Assume -1 means unused position
            printf("%d ", coord->coords[i]);
        }
    }
    printf("\n");

    printf("Sums: ");
    for (int i = 0; i < MAX_COORD_SIZE; i++) {
        if (coord->sums[i] != -1) {  // Only print used sums
            printf("%d ", coord->sums[i]);
        }
    }
    printf("\n");

    printf("Minus One Counters: ");
    for (int i = 0; i < MAX_COORD_SIZE; i++) {
        if (coord->minusCounters[i] != -1) {  // Only print used counters
            printf("%d ", coord->minusCounters[i]);
        }
    }
    printf("\n");
}
/*
requires: A reference to the currentPlayer structure of type PLAYER, which contains the probGrid array representing the player's grid of probabilities.
          A reference to the rows structure of type maxCoord
effects: Iterates through each row in the player's grid (probGrid) and for each column in the row:
            - If the value is negative (-1), increments the minus counter for that row.
            - Otherwise, adds the value to the sum for that row.
           - Updates the rows structure with the computed values.
*/
void sumRows(PLAYER* currentPlayer, struct maxCoord *rows) {
    for (int i = 0; i < GRID_SIZE; i++) {
        rows->coords[i] = i;
        rows->sums[i] = 0;     // Initialize sum to 0
        rows->minusCounters[i] = 0;  // Initialize negative counter to 0

        for (int j = 0; j < GRID_SIZE; j++) {
            if (currentPlayer->probGrid[i][j] < 0) {
                rows->minusCounters[i]++;  // Count negative values
            } else {
                rows->sums[i] += currentPlayer->probGrid[i][j];  // Add to sum
            }
        }
    }
}

/*
requires: A reference to the currentPlayer structure of type PLAYER, which contains the probGrid array representing the player's grid of probabilities.
          A reference to the cols structure of type maxCoord, 
effects: Iterates through each column in the player's grid (probGrid) and and for each row in the column:
            - If the value is negative (-1), increments the minus counter for that column.
            - Otherwise, adds the value to the sum for that column.
          - Updates the cols structure with the computed values.
*/
void sumCols(PLAYER* currentPlayer, struct maxCoord *cols) {
    for (int i = 0; i < GRID_SIZE; i++) {
        cols->coords[i] = i;
        cols->sums[i] = 0;     // Initialize sum to 0
        cols->minusCounters[i] = 0;  // Initialize negative counter to 0

        for (int j = 0; j < GRID_SIZE; j++) {
            if (currentPlayer->probGrid[j][i] < 0) {
                cols->minusCounters[i]++;  // Count negative values
            } else {
                cols->sums[i] += currentPlayer->probGrid[j][i];  // Add to sum
            }
        }
    }
}

/*
requires: Two pointers to `maxCoord` structures (a and b) to compare.
          
effects: Compares the `maxCoord` structures and returns
            - A positive value if `a` should come after `b` in the sorted order.
            - A negative value if `a` should come before `b` in the sorted order.
            - Zero if both structures are considered equal.
*/
int compareCoord(const void *a, const void *b) {
    struct maxCoord *coordA = (struct maxCoord *)a;
    struct maxCoord *coordB = (struct maxCoord *)b;

    // Compare by the count of negative values first (descending order)
    if (coordA->minusCounters[0] != coordB->minusCounters[0]) {
        return coordB->minusCounters[0] - coordA->minusCounters[0]; 
    }
    // If the negative counters are the same, compare by sum (descending order)
    return coordB->sums[0] - coordA->sums[0]; 
}
/*
requires: A reference to a `maxCoord` structure (`coord`)
effects: Sorts the entries in the `maxCoord` structure by using a simple comparison and swapping mechanism.
*/
void sortMaxCoord(struct maxCoord *coord) {
    for (int i = 0; i < GRID_SIZE - 1; i++) {
        for (int j = i + 1; j < GRID_SIZE; j++) {
            // First, compare by minusCounters (descending)
            if (coord->minusCounters[i] < coord->minusCounters[j]) {
                // Swap coords, sums, and minusCounters
                int tempCoord = coord->coords[i];
                int tempSum = coord->sums[i];
                int tempMinus = coord->minusCounters[i];

                coord->coords[i] = coord->coords[j];
                coord->sums[i] = coord->sums[j];
                coord->minusCounters[i] = coord->minusCounters[j];

                coord->coords[j] = tempCoord;
                coord->sums[j] = tempSum;
                coord->minusCounters[j] = tempMinus;
            }
            // If the minusCounters are the same, compare by sum (ascending)
            else if (coord->minusCounters[i] == coord->minusCounters[j]) {
                if (coord->sums[i] > coord->sums[j]) {
                    // Swap coords, sums, and minusCounters
                    int tempCoord = coord->coords[i];
                    int tempSum = coord->sums[i];
                    int tempMinus = coord->minusCounters[i];

                    coord->coords[i] = coord->coords[j];
                    coord->sums[i] = coord->sums[j];
                    coord->minusCounters[i] = coord->minusCounters[j];

                    coord->coords[j] = tempCoord;
                    coord->sums[j] = tempSum;
                    coord->minusCounters[j] = tempMinus;
                }
            }
        }
    }
}

/*
requires: A reference to the current player and opposing player, a reference to the sorted row coordinates (`rows`), and a reference to the `input` structure.
         
effects: Sets the row value of the `input` to the first row in the sorted `rows` array.
         Sets the column value of `input` to -1 (indicating no column is selected).
         Prints the row where the torpedo will be played.
         Calls the `torpedo` function to execute the torpedo action using the `input` parameters.
*/
void playTorpedoRow(PLAYER* currentPlayer, PLAYER* opposingPlayer, struct maxCoord* rows, INPUT* input) {
    input->row = rows->coords[0];  // Select the row based on the sorted row coordinates
    input->column = -1;  // No column is selected
    printf("The bot plays torpedo at row %d\n", input->row);
    torpedo(currentPlayer, opposingPlayer, input);  // Call the torpedo function
}
/*
requires: A reference to the current player , opposing player , a reference to the sorted column coordinates (`cols`), and a reference to the `input` structure.
          .
effects: Sets the column value of the `input` to the first column in the sorted `cols` array.
         Sets the row value of `input` to -1 (indicating no row is selected).
         Prints the column where the torpedo will be played, converting the column index to a letter (a-j).
         Calls the `torpedo` function to execute the torpedo action using the `input` parameters.
*/
void playTorpedoColumn(PLAYER* currentPlayer, PLAYER* opposingPlayer, struct maxCoord* cols, INPUT* input) {
    input->row = -1;  // No row is selected
    input->column = cols->coords[0];  // Select the column based on the sorted column coordinates
    printf("The bot plays torpedo at column %c\n", cols->coords[0] + 97);  // Convert to 'a'-'j' range for column names
    torpedo(currentPlayer, opposingPlayer, input);  // Call the torpedo function
}

/*
requires: A reference to the current player, opposing player , a reference to the sorted row coordinates (`rows`), a reference to the sorted column coordinates (`cols`), and a reference to the `input` structure.
effects: Compares the negative counters (`minusCounters`) and sums (`sums`) of the rows and columns:
          - If the row has more negative counters than the column, calls `playTorpedoRow`.
          - If the column has more negative counters than the row, calls `playTorpedoColumn`.
          - If both row and column have the same number of negative counters, compares the sums:
              - If the row sum is higher, calls `playTorpedoRow`.
              - If the column sum is higher or equal, calls `playTorpedoColumn`.
*/
void decideTorpedoAction(PLAYER* currentPlayer, PLAYER* opposingPlayer, struct maxCoord* rows, struct maxCoord* cols, INPUT* input) {
    // If the row has more negative counters than the column
    if (rows->minusCounters[GRID_SIZE-1] > cols->minusCounters[GRID_SIZE-1]) {
        playTorpedoRow(currentPlayer, opposingPlayer, rows, input);
    }
    // If the column has more negative counters than the row
    else if (rows->minusCounters[GRID_SIZE-1] < cols->minusCounters[GRID_SIZE-1]) {
        playTorpedoColumn(currentPlayer, opposingPlayer, cols, input);
    }
    // If they are equal, compare sums
    else {
        if (rows->sums[GRID_SIZE-1] > cols->sums[GRID_SIZE-1]) {
            playTorpedoRow(currentPlayer, opposingPlayer, rows, input);
        } else {
            playTorpedoColumn(currentPlayer, opposingPlayer, cols, input);
        }
    }
}


/*
requires: A reference to the current player  and the opposing player.
effects: 
    - Calls `sumRows` and `sumCols` to calculate sums and track negative counters for rows and columns.
    - Sorts both `rows` and `cols` based on negative counters and then by sums
    - Prints the sorted row and column coordinates
   
*/

void handleTorpedo(PLAYER* currentPlayer, PLAYER* opposingPlayer) {
    struct maxCoord rows;
    rows.isRow = 1;
    
    struct maxCoord cols;
    cols.isRow = 0;

    // Sum the rows and columns and keep track of -1 
    sumRows(currentPlayer, &rows);
    sumCols(currentPlayer, &cols);

    //sort based on minusCounter then sums
    sortMaxCoord(&rows);
    sortMaxCoord(&cols);

    printCoord(&rows);
    printCoord(&cols);
    

    INPUT input;
    decideTorpedoAction(currentPlayer,opposingPlayer,&rows,&cols,&input);

}