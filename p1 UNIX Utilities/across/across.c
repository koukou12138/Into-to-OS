////////////////////////////////////////////////////////////////////////////////
// File:             across.c
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
#include <ctype.h>

/*
 *  This function is used to check if the word is valid
 *
 *  @parameter char *
 *
 *  @return int
 */
int valid(char *word) {
    char *ptr;

    for (ptr = word; *ptr; ptr++) {
        if (!isalpha(*ptr) || isupper(*ptr))
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc <= 3 || argc >= 6) {
        printf("across: invalid number of arguments\n");
        exit(1);
    }

    if (strlen(argv[1]) + atoi(argv[2]) > atoi(argv[3])) {
        printf("across: invalid position\n");
        exit(1);
    }

    char *filename;

    if (argc == 4)
        filename = "/usr/share/dict/words";
    else
        filename = argv[4];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("across: cannot open file\n");
        exit(1);
    }
    int len = strlen(argv[1]);

    char line[64] = {""};

    while ( fgets( line, sizeof( line), fp) != NULL ) {
        strtok(line, "\n");

        if (strlen(line) != atoi(argv[3])) {
            continue;
        } else if (!valid(line)) {
            continue;
        } else {
            char tmp[64] = {""};
            strncpy(tmp, line + atoi(argv[2]), len);
            if (strcmp(tmp, argv[1]) == 0) {
                printf("%s\n", line);
            }
        }
    }
    fclose(fp);
    return 0;
}
