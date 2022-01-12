#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char*argv[]){
   int frames[20];
   int pids[20];
   frames[0] = 15;
   pids[0] = 15;
   int numframes = 20;
    int i = dump_physmem(frames,pids,numframes);
    for(int j = 0 ; j < numframes; j++){
         printf(1, "frames[%d] = %d; pids[%d] = %d\n", i, *(frames+i), i, *(pids+i));
    }
    wait();
    printf(1,"return value of dumpmem: %d \n",i);
    exit();
}
