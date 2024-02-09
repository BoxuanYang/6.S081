#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(){
    int fds[2];
    char buf[2];
    buf[0] = 'Y';

    pipe(fds);

    int pid = fork();

    if(pid < 0){
        printf("Failed to fork.");
        return 0;
    }

    if(pid > 0){ // parent
        int ppid = getpid();

        // parent sends a byte
        write(fds[1], buf, 1);
        close(fds[1]);

        wait(0);

        // read the byte from the child, print and exit
        char byte[1];
        read(fds[0], byte, 1);
        close(fds[0]);


        
        printf("%d: received pong\n", ppid);
        //printf("Parent exiting \n");
        exit(0);
    }
    else{ // child
        int ppid = getpid();
        

        // write the byte to parent and exit
        char byte[1];
        read(fds[0], byte, 1);

        close(fds[0]);
        printf("%d: received ping\n", ppid);


        write(fds[1], byte, 1);
        //printf("Child exiting \n");

        
        exit(0);
    }
    return 0;
}