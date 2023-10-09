#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 50

typedef struct {
    int dx;
    int dy;
    const char *description;
} Direction;

Direction directions[] = {
    {1, 0, "vertically downwards"},
    {-1, 0, "vertically upwards"},
    {0, 1, "horizontally to the right"},
    {0, -1, "horizontally to the left"},
    {1, 1, "diagonally down to the right"},
    {-1, -1, "diagonally up to the left"},
    {1, -1, "diagonally down to the left"},
    {-1, 1, "diagonally up to the right"}
};

int countOccurrences(char **matrix, int matrix_rows, int matrix_columns, const char *word, Direction direction) {
    int count = 0;
    int wordLength = strlen(word);
    int row, col, i;

    /* Iterate through the matrix */ 
    for (row = 0; row < matrix_rows; row++) {
        for (col = 0; col < matrix_columns; col++) {
            if (matrix[row][col] == word[0]) {
                int matchLength = 1;
                int newRow = row;
                int newCol = col;
                
                /* Try to match the rest of the word */ 
                for (i = 1; i < wordLength; i++) {
                    newRow += direction.dx;
                    newCol += direction.dy;
                    if (newRow < 0 || newRow >= matrix_rows || newCol < 0 || newCol >= matrix_columns) {
                        break;  
                    }
                    if (matrix[newRow][newCol] != word[i]) {
                        break;
                    }
                    matchLength++;
                }
                
                if (matchLength == wordLength) {
                    count++;
                }
            }
        }
    }
    return count;
}

int findStartPosition(char **matrix, int matrix_rows, int matrix_columns, const char *word, Direction direction, int *startRow, int *startCol) {
    int wordLength = strlen(word), row, col, i;

    for (row = 0; row < matrix_rows; row++) {
        for (col = 0; col < matrix_columns; col++) {
            if (matrix[row][col] == word[0]) {
                int matchLength = 1;
                int newRow = row;
                int newCol = col;
                
                for (i = 1; i < wordLength; i++) {
                    newRow += direction.dx;
                    newCol += direction.dy;
                    if (newRow < 0 || newRow >= matrix_rows || newCol < 0 || newCol >= matrix_columns) {
                        break; 
                    }
                    if (matrix[newRow][newCol] != word[i]) {
                        break;
                    }
                    matchLength++;
                }
                
                if (matchLength == wordLength) {
                    *startRow = row;
                    *startCol = col;
                    return 1; 
                }
            }
        }
    }
    return 0;
}

void clearSolutionMatrix(char **solutionMatrix, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            solutionMatrix[i][j] = ' ';
        }
    }
}

void placeWordInSolutionMatrix(char **solutionMatrix, int row, int col, const char *word, Direction direction) {
    int i;
    for (i = 0; word[i] != '\0'; i++) {
        solutionMatrix[row][col] = word[i];
        row += direction.dx;
        col += direction.dy;
    }
}

int main(void) {
    int matrix_rows = 0;
    int matrix_columns = 0;
    char line[MAX_WORD_LENGTH];
    int isMatrix = 1;
    int i, j, dir;

    /* Dynamically allocate memory */ 
    char **matrix = (char **)malloc(MAX_WORD_LENGTH * sizeof(char *));
    char **solutionMatrix = (char **)malloc(MAX_WORD_LENGTH * sizeof(char *));
    if (!matrix || !solutionMatrix) {
        fprintf(stderr, "Failed to allocate memory!\n");
        return -1;
    }

    for (i = 0; i < MAX_WORD_LENGTH; i++) {
        matrix[i] = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
        solutionMatrix[i] = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
        if (!matrix[i] || !solutionMatrix[i]) {
            fprintf(stderr, "Failed to allocate memory!\n");
            return -1;
        }
        memset(matrix[i], 0, MAX_WORD_LENGTH);
        memset(solutionMatrix[i], ' ', MAX_WORD_LENGTH); 
    }

    /* Reading matrix and words from stdin */ 
    while (fgets(line, sizeof(line), stdin)) {
        char *ptr = strchr(line, '\n');
        if (ptr) *ptr = '\0';

        ptr = strchr(line, '\r');
        if (ptr) *ptr = '\0';
            
        if (isMatrix) {
            int col = 0;
            for (i = 0; line[i] != '\0'; i++) {
                if (line[i] != ' ') {
                    matrix[matrix_rows][col++] = line[i];
                }
            }
            
            if (matrix_columns == 0) {  /* Only set matrix_columns once. */ 
                matrix_columns = col;
            }
            
            if (col == matrix_columns) {
                matrix_rows++;
            } else {
                isMatrix = 0;
            }
        }

        if (!isMatrix) {
            if (strlen(line) >= 2) {
                for (dir = 0; dir < 8; dir++) {
                    int count = countOccurrences(matrix, matrix_rows, matrix_columns, line, directions[dir]);
                    if (count > 0) {
                        int startRow, startCol;
                        if (findStartPosition(matrix, matrix_rows, matrix_columns, line, directions[dir], &startRow, &startCol)) {
                            placeWordInSolutionMatrix(solutionMatrix, startRow, startCol, line, directions[dir]);
                        }
                    }
                }
            }
        }
    }

    /* Print solution matrix */ 
    for (i = 0; i < matrix_rows; i++) {
        int lastCharIndex = matrix_columns - 1;
        
        /* Find the last non-space character in the row */ 
        while (lastCharIndex >= 0 && solutionMatrix[i][lastCharIndex] == ' ') {
            lastCharIndex--;
        }

        for (j = 0; j <= lastCharIndex; j++) {
            if (j < lastCharIndex) {
                printf("%c ", solutionMatrix[i][j]);
            } else {
                printf("%c", solutionMatrix[i][j]);
            }
        }
        printf("\n");
    }

    /* Free Memory */
    for (i = 0; i < MAX_WORD_LENGTH; i++) {
        free(matrix[i]);
        free(solutionMatrix[i]);
    }

    free(matrix);
    free(solutionMatrix);

    return 0;
}
