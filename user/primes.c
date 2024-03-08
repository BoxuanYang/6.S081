#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/**
 * Read all numbers passed from the p[2]
 * Retrieve the total number of numbers passed, n and filter index as index
 * If(n == 0){
 * exit(0);
 * }
 * Create another pipe
 * Print the first nubmer passed
 * Apply filter to all the numbers
 * Pass the filtered numbers to its child process through another pipe
 * 
 * 
*/
void next_sieve(int p[2]){
    int n, index;

    close(p[1]);

    read(p[0], &n, 4);
    read(p[0], &index, 4);

    if(n == 0){
        exit(0);
    }
    

    int first_num;
    read(p[0], &first_num, 4);
    printf("prime %d\n", first_num);


    // Create another pipe
    int new_pd[2];
    pipe(new_pd);

    int count = 0; // how many numbers in this list is not divisible by index
    
    // Apply filters to every number

    // Count how many numbers are divisible by index
    int number;
    int *filtered_numbers = (int *) malloc(n * sizeof(int));
    for(int i = 1; i < n; i++){ 
        read(p[0], &number, 4);  
        if(number % index != 0){
            filtered_numbers[count] = number;
            count++;
        }
    }

    if(count == 0){
        exit(0);
    }
    

    write(new_pd[1], &count, 4);
    index++;
    write(new_pd[1], &index, 4);

    // Pass the numbers through the new pipe
    for(int i = 0; i < count; i++){
        write(new_pd[1], filtered_numbers+i, 4);
    }
    close(new_pd[1]);
    close(p[0]);


    if(fork() != 0){ // parent process 
        close(p[1]);
        wait(0);
    }else{ // child process
        close(new_pd[1]);
        next_sieve(new_pd);
    }
    exit(0);

      
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
    close(p[1]);

    next_sieve(p);



    wait(0);
    printf("All done!\n");
    exit(0);

    return 0;
}