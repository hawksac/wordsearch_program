#include <stdio.h>
#include <string.h>

#define MAX_MATRIX_SIZE 100
#define MAX_WORD_LENGTH 100

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

int countOccurrences(char matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int matrix_rows, int matrix_columns, const char *word, Direction direction) {
    int count = 0;
    int wordLength = strlen(word);

    // Iterate through the matrix
    for (int row = 0; row < matrix_rows; row++) {
        for (int col = 0; col < matrix_columns; col++) {
            if (matrix[row][col] == word[0]) {
                int matchLength = 1;
                int newRow = row;
                int newCol = col;
                
                // Try to match the rest of the word
                for (int i = 1; i < wordLength; i++) {
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

int findStartPosition(char matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int matrix_rows, int matrix_columns, const char *word, Direction direction, int *startRow, int *startCol) {
    int wordLength = strlen(word);

    for (int row = 0; row < matrix_rows; row++) {
        for (int col = 0; col < matrix_columns; col++) {
            if (matrix[row][col] == word[0]) {
                int matchLength = 1;
                int newRow = row;
                int newCol = col;
                
                for (int i = 1; i < wordLength; i++) {
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

char solutionMatrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

void clearSolutionMatrix() {
    for (int i = 0; i < MAX_MATRIX_SIZE; i++) {
        for (int j = 0; j < MAX_MATRIX_SIZE; j++) {
            solutionMatrix[i][j] = ' ';
        }
    }
}

void placeWordInSolutionMatrix(int row, int col, const char *word, Direction direction) {
    for (int i = 0; word[i] != '\0'; i++) {
        solutionMatrix[row][col] = word[i];
        row += direction.dx;
        col += direction.dy;
    }
}

int main() {
    char matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = {0};
    int matrix_rows = 0;
    int matrix_columns = 0;
    char line[MAX_WORD_LENGTH];
    int isMatrix = 1;

    // Reading matrix and words from stdin
    clearSolutionMatrix();  // Clear the solution matrix once, before processing words.

    // Reading matrix and words from stdin
    while (fgets(line, sizeof(line), stdin)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        if (isMatrix) {
            int col = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (line[i] != ' ') {
                    matrix[matrix_rows][col++] = line[i];
                }
            }
            
            if (matrix_columns == 0) {  // Only set matrix_columns once.
                matrix_columns = col;
            }
            
            if (col == matrix_columns) {
                matrix_rows++;
            } else {
                isMatrix = 0;
            }
        }


        if (!isMatrix) {
            // printf("%s\n", line);

            if (strlen(line) >= 2) {
                for (int dir = 0; dir < 8; dir++) {
                    int count = countOccurrences(matrix, matrix_rows, matrix_columns, line, directions[dir]);
                    if (count > 0) {
                        // printf("Occurrences of \"%s\" moving %s: %d\n", line, directions[dir].description, count);
                        int startRow, startCol;
                        if (findStartPosition(matrix, matrix_rows, matrix_columns, line, directions[dir], &startRow, &startCol)) {
                            placeWordInSolutionMatrix(startRow, startCol, line, directions[dir]);
                        }
                    }
                }
            }
        }
    }
    // Print solution matrix
    for (int i = 0; i < matrix_rows; i++) {
        for (int j = 0; j < matrix_columns; j++) {
            printf("%c", solutionMatrix[i][j]);
            
            // Add space after each character, except the last character in the row
            if (j < matrix_columns - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
