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
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * This strcut is an instance of background job
 *
 * @param the head of linked list
 */
struct JOB {
    int pid;                // process id
    int jid;                // job id
    char* command;          // command string
    struct JOB *next;       // the reference to next JOB
};

/**
 * This function frees all the jobs in the linkedlist
 *
 * @param the head of linked list
 */
void freeList(struct JOB *head) {
    struct JOB *p = head;
    struct JOB *p2;
    while (p != NULL) {
        free(p->command);
        p2 = p->next;
        free(p);
        p = p2;
    }
}

/**
 * This function checks if a string is numeric
 *
 * @param the string to check
 */
int isNumeric(const char *str) {
    while (*str != '\0') {
        if ( *str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

// clean the left side white spaces of a string
char *ltrim(char *s) {
    while (isspace(*s)) s++;
    return s;
}

// clean the right side white spaces of a string
char *rtrim(char *s) {
    char* back = s + strlen(s) - 1;
    while (isspace(*back)) back--;
    *(back+1) = '\0';
    return s;
}

// clean both sides white spaces of a string
char *trim(char *s) {
    return rtrim(ltrim(s));
}

/**
 * This function split the string by white space
 *
 * @param the string to split
          the array to store the string pieces
 */
void getArgv(char *str, char *array[]) {
        char delim[] = " ";
        int i = 0;
        char *ptr = strtok(str, delim);

        while (ptr != NULL) {
            array[i] = ptr;
            i++;
            ptr = strtok(NULL, delim);
        }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: mysh [batchFile]\n");
        fflush(stderr);
        exit(1);
    }

    FILE* in;
    int interactive; // determine which mode to run

    if (argc == 2) {
        in = fopen(argv[1], "r");
        interactive = 0;
        if (in == NULL) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
            fflush(stderr);
            return 1;
        }
    } else {
        in = stdin;
        interactive = 1;
    }

    char command[513] = {""};
    int jid = 0;
    int pid, i, back, cp;

    char *array[513]; // the string array to store the arguments of command

    struct JOB *head = NULL;
    struct JOB *ptr;

    while (1) {
        if (interactive) {
            fprintf(stdout, "mysh> ");
            fflush(stdout);
        }

        memset(command, 0 , 513);   //clean the command string
        if (fgets(command, sizeof(command), in) == NULL) {
            freeList(head);
            fclose(in);
            break;
        }
        if (!interactive) {
            fprintf(stdout, "%s", command);
            fflush(stdout);
        }

        trim(command);
        if (command[0] == '\0') {
            continue;
        }

        memset(array, 0, 512);
        getArgv(command, array);

        i = 0;
        while (array[i] != NULL)
            i++;
        // check if the command is background pr foreground job
        if (strcmp(array[i-1], "&") == 0) {
            back = 1;
            array[i-1] = NULL;
            if (i == 1)
                continue;
        } else {
            back = 0;
        }
        if (strcmp(array[0], "exit") == 0  && array[1] == NULL) {
            freeList(head);
            fclose(in);
            exit(0);

        } else if (strcmp(array[0], "jobs") == 0 && array[1] == NULL) {
            ptr = head;
            while (ptr != NULL) {
                cp = waitpid(ptr->pid, NULL, WNOHANG);
                if (cp == 0) {
                    printf("%d : %s\n", ptr->jid, ptr->command);
                    fflush(stdout);
                }

                ptr = ptr->next;
            }
            continue;

        } else if (strcmp(array[0], "wait") == 0) {
            if (array[1] == NULL)
                continue;

            if (isNumeric(array[1]) && array[2] == NULL) {
                int id_to_wait = atoi(array[1]);
                ptr = head;
                int jid_existed = 0;
                while (ptr != NULL) {
                    if (ptr->jid == id_to_wait) {
                        jid_existed = 1;
                        cp = waitpid(ptr->pid, NULL, WNOHANG);

                        if (cp == 0)
                            waitpid(ptr->pid, NULL, 0);
                        fprintf(stdout, "JID %d terminated\n", ptr->jid);
                        fflush(stdout);
                    }
                    ptr = ptr->next;
                }
                if (!jid_existed) {
                    fprintf(stderr, "Invalid JID %d\n", id_to_wait);
                    fflush(stderr);
                }
            }
            continue;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            return -1;
        } else if (pid == 0) {  // if this is child process
            int fd = 0;
            int oldstdout = 0;
            int oldstderr = 0;
            int redirected = 0;

            for (i = 0; array[i] != NULL; i++) {
                if (strcmp(array[i], ">") == 0) {
                    redirected = 1;
                    if (array[i+1] == NULL) {
                        fprintf(stderr, "redirect file does not exist!\n");
                        fflush(stderr);
                        continue;
                    }
                    fd = open(array[i+1], O_WRONLY|O_CREAT|O_TRUNC, 0600);

                    oldstdout = dup(STDOUT_FILENO);
                    oldstderr = dup(STDERR_FILENO);
                    dup2(fd, STDOUT_FILENO);
                    dup2(fd, STDERR_FILENO);
                    array[i] = NULL;
                }
            }

            if (execvp(array[0], array) < 0) {
                fprintf(stderr, "%s: Command not found\n", array[0]);
                fflush(stderr);
            }
            if (redirected) {
                dup2(oldstdout, STDOUT_FILENO);
                dup2(oldstderr, STDERR_FILENO);

                close(fd);
                close(oldstdout);
                close(oldstderr);
            }
            exit(0);
        }
        // parent process
        char cmd[513];

        if (back) {
            struct JOB *job = malloc(sizeof(struct JOB));
            job->jid = jid;
            job->pid = pid;

            if (head == NULL) {
                head = job;
            } else {
                ptr = head;
                while (ptr->next != NULL)
                    ptr = ptr->next;
                ptr->next = job;
            }
            memset(cmd, 0, 513);

            int j;

            for (j = 0;  j < i-1; j++) {
                strcat(cmd, array[j]);
                if (j != i-2)
                    strcat(cmd, " ");
            }
            job->command = malloc((strlen(cmd)+1)*sizeof(char));
            strcpy(job->command, cmd);
        } else {
            waitpid(pid, NULL, 0);
        }
        jid++;
    }
    return 0;
}
