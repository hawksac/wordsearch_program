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

int main() {
    char matrix[3][3] = {
        {'B', 'B', 'B'},
        {'B', 'A', 'B'},
        {'B', 'B', 'B'}
    };
    
    char word[] = "BA";

    char firstLetter = word[0];
    char secondLetter = word[1];

    // Iterate through the matrix
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (matrix[row][col] == firstLetter) {
                for (int dir = 0; dir < 8; dir++) {
                    int newRow = row + directions[dir].dx;
                    int newCol = col + directions[dir].dy;
                    if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                        if (matrix[newRow][newCol] == secondLetter) {
                            printf("Occurrences of \"%c%c\" moving %s: 1\n", firstLetter, secondLetter, directions[dir].description);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
