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

int countOccurrences(char matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int matrix_rows, int matrix_columns, char firstLetter, char secondLetter, Direction direction) {
    int count = 0;

    // Iterate through the matrix
    for (int row = 0; row < matrix_rows; row++) {
        for (int col = 0; col < matrix_columns; col++) {
            if (matrix[row][col] == firstLetter) {
                int newRow = row + direction.dx;
                int newCol = col + direction.dy;
                
                if (newRow >= 0 && newRow < matrix_rows && newCol >= 0 && newCol < matrix_columns && matrix[newRow][newCol] == secondLetter) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    char matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = {0};
    int matrix_rows = 0;
    int matrix_columns = 0;
    char line[MAX_WORD_LENGTH];
    int isMatrix = 1;

    // Reading matrix and words from stdin
    while (fgets(line, sizeof(line), stdin)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        if (isMatrix) {
    int col = 0;
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] != ' ') { // or check if it's an alphabetic character
            matrix[matrix_rows][col++] = line[i];
        }
    }
    if (col == 0) { // Handle empty lines or lines with only spaces as delimiters
        isMatrix = 0;
    } else if (matrix_columns == 0) {
        matrix_columns = col;
        matrix_rows++;
    } else if (col != matrix_columns) {
        isMatrix = 0;  // Change mode but don't process word here
    } else {
        matrix_rows++;
    }
}

if (!isMatrix) {  // Separate the logic for word processing
    printf("%s\n", line);

    if (strlen(line) >= 2) {
        char firstLetter = line[0];
        char secondLetter = line[1];

        for (int dir = 0; dir < 8; dir++) {
            int count = countOccurrences(matrix, matrix_rows, matrix_columns, firstLetter, secondLetter, directions[dir]);
            if (count > 0) {
                printf("Occurrences of \"%c%c\" moving %s: %d\n", firstLetter, secondLetter, directions[dir].description, count);
            }
        }
    }
}
}
    return 0;
}
