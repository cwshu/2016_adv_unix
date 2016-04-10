#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    printf("hello world!\n");
    write(1, "hello syscall!\n", 15);

    return 0;
}
