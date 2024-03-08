

int main(int argc, char *args[]){
    int second_index = 0; // stores the index to the second command line
    char *ptr = args[second_index];
    while(strcmp(*ptr, "|") != 0){
        second_index++;
        ptr = args[second_index];
    }

    second_index++;

    // Now, second_index points to the first char ptr on the right of '|'
    
    return 0;
}