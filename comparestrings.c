#include <stdio.h>
#include <string.h>

void printASCIIValue(const char ch) {
    printf("%d ", (int)ch);
}

void compareStrings(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int minLen = len1 < len2 ? len1 : len2;

    for (int i = 0; i < minLen; ++i) {
        if (str1[i] != str2[i]) {
            printf("Difference at position %d: '%c' vs '%c' (", i, str1[i], str2[i]);
            printASCIIValue(str1[i]);
            printf("vs ");
            printASCIIValue(str2[i]);
            printf(")\n");
        }
    }
    if (len1 != len2) {
        printf("Strings have different lengths: %d vs %d\n", len1, len2);
        if (len1 > len2) {
            printf("Extra characters in first string: %s\n", &str1[minLen]);
        } else {
            printf("Extra characters in second string: %s\n", &str2[minLen]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    char string1[1000];
    char string2[1000];

    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");

    if (!file1 || !file2) {
        perror("Error opening files");
        return 1;
    }

    fgets(string1, sizeof(string1), file1);
    fgets(string2, sizeof(string2), file2);

    compareStrings(string1, string2);

    fclose(file1);
    fclose(file2);

    return 0;
}
