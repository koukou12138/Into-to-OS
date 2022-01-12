////////////////////////////////////////////////////////////////////////////////
// File:             my-diff.c
// Semester:         CS 537 fall 2019
//
// Author:           Kerui Wang
// Email:            kwang392@wisc.edu
// CS Login:         kerui
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("my-diff: invalid number of arguments\n");
        exit(1);
    }

    FILE *fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        printf("my-diff: cannot open file\n");
        exit(1);
    }

    FILE *fp2 = fopen(argv[2], "r");
    if (fp2 == NULL) {
        printf("my-diff: cannot open file\n");
        exit(1);
    }

    char *line1 = NULL;
    char *line2 = NULL;

    size_t linecap1 = 0;
    size_t linecap2 = 0;

    ssize_t linelen1;
    ssize_t linelen2;

    int lineNumber = 1;

    int mismatch = 0;

    while (1) {
        linelen1 = getline(&line1, &linecap1, fp1);
        linelen2 = getline(&line2, &linecap2, fp2);

        if (linelen1 <= 0 && linelen2 <= 0)
            break;

        if (linelen1 > 0 && linelen2 > 0) {
            strtok(line1, "\n");
            strtok(line2, "\n");

            if (strcmp(line1, line2) != 0) {
                if (!mismatch) {
                    printf("%d\n", lineNumber);
                    mismatch = 1;
                }

                printf("< %s\n> %s\n", line1, line2);

            } else {
                mismatch = 0;
            }

            free(line1);
            free(line2);
            line1 = NULL;
            line2 = NULL;
        } else if (linelen1 > 0) {
            strtok(line1, "\n");

            if (!mismatch) {
                printf("%d\n", lineNumber);
                mismatch = 1;
            }
            printf("< %s\n", line1);
            free(line1);
            line1 = NULL;

        } else if (linelen2 > 0) {
            strtok(line2, "\n");
            if (!mismatch) {
                printf("%d\n", lineNumber);
                mismatch = 1;
            }
            printf("> %s\n", line2);
            free(line2);
            line2 = NULL;
        }
        lineNumber++;
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
