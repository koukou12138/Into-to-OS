#include "types.h"
#include "user.h"
#include "stat.h"
#include "pstat.h"

int
is_digit(char c) {
    return c >= '0' && c <= '9';
}

int
is_num(char *c) {
    while (*c != '\0') {
        if (!is_digit(*c)) {
            return 0;
        }
        c++;
    }
    return 1;
}

int
main(int argc, char *argv[]) {
    if (argc != 5) {
        printf(1, "userRR: invalid number of arguments\n");
        exit();
    }

    if (!is_num(argv[1]) || !is_num(argv[2]) || !is_num(argv[4])) {
        printf(1, "userRR: invalid argument\n");
        exit();
    }

    int user_level_timeslice = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    int job_count = atoi(argv[4]);
    int jobs[job_count];

    struct pstat p_table;

    for (int i = 0; i < job_count; i++) { //create the child processes
        int c_pid = fork2(1);
        if (c_pid == 0) {
            if (exec(argv[3], argv) == -1) {
                printf(1, "userRR: exec error\n");
            }
            exit();
        } else {
            jobs[i] = c_pid;
        }
    }

    for (int i = 0; i < iterations; i++) {
        for (int j = 0; j < job_count; j++) {
            setpri(jobs[j], 2);
            sleep(user_level_timeslice);
            setpri(jobs[j], 1);
        }
    }

    getpinfo(&p_table);

    for (int i = 0; i < job_count; i++) {
        kill(jobs[i]);
    }

    return 0;
}

