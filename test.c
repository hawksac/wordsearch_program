#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50
#define MAX_WORDS 100

int is_valid(int x, int y, int n) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

int search_direction(char square[MAX_SIZE][MAX_SIZE], int x, int y, const char *word, int dx, int dy, int n) {
    int l, len = strlen(word);

    for (l = 0; l < len; l++) {
        int newX = x + l * dx;
        int newY = y + l * dy;
        if (!is_valid(newX, newY, n) || square[newX][newY] != word[l]) {
            // Restore any overwritten characters before returning
            while (--l >= 0) {
                square[x + l * dx][y + l * dy] = word[l];
            }
            return 0;
        } else {
            square[newX][newY] = '_'; // mark as used
        }
    }
    return 1;
}

int main(void) {
    char square[MAX_SIZE][MAX_SIZE];
    char words[MAX_WORDS][MAX_SIZE];
    int n, num_words, i, j, k, dir;
    int directions[8][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};

    /* Read in the input file */
    scanf("%d", &n);
    printf("Size of the square: %d\n", n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf(" %c", &square[i][j]);
            printf("%c ", square[i][j]);
        }
        printf("\n");
    }

    num_words = 0;
    while(num_words < MAX_WORDS && scanf("%s", words[num_words]) != EOF) {
        num_words++;
    }

    printf("\nList of words:\n");
    for (i = 0; i < num_words; i++) {
        printf("%s\n", words[i]);
    }

    /* Search for words in the square */
    for (i = 0; i < num_words; i++) {
    int wordFound = 0;
    for (j = 0; j < n && !wordFound; j++) {
        for (k = 0; k < n && !wordFound; k++) {
            if (square[j][k] == words[i][0]) {
                for (dir = 0; dir < 8; dir++) {
                    if (search_direction(square, j, k, words[i], directions[dir][0], directions[dir][1], n)) {
                        printf("Word %s found at [%d][%d] in direction %d\n", words[i], j, k, dir);
                        wordFound = 1;
                        break; /* Breaks out of the direction loop */ 
                    }
                }
            }
        }
    }
}

    /* Print out the modified square with the unused letters replaced by spaces */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (square[i][j] == '_') {
                printf(" ");
            } else {
                printf("%c ", square[i][j]);
            }
        }
        printf(" \n");
    }
    return 0;
}
