#include <stdlib.h>

int main(){
    char buf[512];
    int n;

    n = read(0, buf, sizeof(buf));

    printf("n is : %d ", &n);

    return 0;
}