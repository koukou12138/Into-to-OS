#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{

    if (argc <= 1) {
        printf(1, "usage: ofiletest N <list of file nums to close and delete>\n");
        exit();
    }

    int num = atoi(argv[1]);

    int i,fd;
    int array[num];
    char name[10] = "ofile";

    char num1,num2;

    for(i = 0; i < num; i++) {
        if (i < 10) {
            num1 = (char) '0' + i;
            name[5] = num1;
            name[6] = '\0';
        } else {
            num1 = (char) '0' + i/10;
            num2 = (char) '0' + i%10;
            name[5] = num1;
            name[6] = num2;
        }
        fd = open( name, O_RDWR|O_CREATE);
        if (fd == -1)
            unlink(name);
        array[i] = fd;
    }

    int toclose;
    for (i = 2; i < argc; i++) {
        toclose = atoi(argv[i]);
        if ( toclose >= num) {
            printf(1, "the file closed does not exist\n");
            continue;
        }

        if (toclose < 10) {
            num1 = (char) '0' + toclose;
            name[5] = num1;
            name[6] = '\0';
        } else {
            num1 = (char) '0' + toclose/10;
            num2 = (char) '0' + toclose%10;
            name[5] = num1;
            name[6] = num2;
        }
        fd = array[toclose];
        array[toclose] = -1;
        close(fd);
        unlink(name);
    }

    printf(1, "%d %d\n", getofilecnt(getpid()), getofilenext(getpid()));

    for (i = 0; i < num; i++) {
        if (array[i] != -1) {
            if (i < 10) {
                num1 = (char) '0' + i;
                name[5] = num1;
                name[6] = '\0';
            } else {
                num1 = (char) '0' + i/10;
                num2 = (char) '0' + i%10;
                name[5] = num1;
                name[6] = num2;
            }
            close(array[i]);
            unlink(name);
        }

    }

    exit();
}