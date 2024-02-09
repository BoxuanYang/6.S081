#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

/**
 * Read all numbers passed from the p[2]
 * Print the first nubmer passed
 * Apply filter to all the numbers
 * Pass the filtered numbers to its child process through another pipe
 * 
 * 
*/
void next_sieve(int p[2]){
    
    

    return;
}

int main(){
    int p[2];
    int n = 34;
    int multiple = 2;

    pipe(p);

    write(p[1], &n, 4);
    write(p[1], &multiple, 4);

    for(int i = 2; i <= 35; i++){
        write(p[1], &i, 4);
    }

    next_sieve(p);

    wait(0);
    exit(0);




    return 0;
}