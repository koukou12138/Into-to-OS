////////////////////////////////////////////////////////////////////////////////
// File:             my-look.c
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
 *  This function is used to compare if two strings are equal when 
 *  case-insensitive
 *
 *  @parameter char * & char &
 *
 *  @return int
 */

int strcmpi(const char *a, const char *b) {
    while (*a && *b && tolower(*a) == tolower(*b))
        ++a, ++b;
    return tolower(*a) - tolower(*b);
}

int main(int argc, char *argv[]) {
    if (argc == 1 || argc >= 4) {
        printf("my-look: invalid number of arguments\n");
        exit(1);
    }

    char *filename;

    if (argc == 2)
        filename = "/usr/share/dict/words";
    else
        filename = argv[2];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("my-look: cannot open file\n");
        exit(1);
    }

    int len = strlen(argv[1]);

    char line[64] = {""};

    while ( fgets(line, sizeof(line), fp) != NULL ) {
        if (strlen(line) < len) {
            continue;
        } else {
            char tmp[64] = {""};
            strncpy(tmp, line, len);

            if (strcmpi(tmp, argv[1]) == 0)
                printf("%s", line);
        }
    }
    fclose(fp);
    return 0;
}
