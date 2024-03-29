#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){  
    if(argc <= 1){
        fprintf(2, "There should be at least one argument");
    }

    if(argc > 2){
        fprintf(2, "There should only be 1 argument");
    }

    int seconds = atoi(argv[1]);

    sleep(seconds);

   exit(0);
}