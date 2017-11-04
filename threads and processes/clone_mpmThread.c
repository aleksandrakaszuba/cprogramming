#define _GNU_SOURCE  //for Ubuntu
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int x, y;
int child_func(){
    //child's function
    sleep(1);
    printf ("\nThis is process (thread) %d. \n", getpid());
    x = 7;
    printf("x + y = %d\n", x + y);
}

int main ( void ) {
    x = 0, y = 0;
    const int STACK_SIZE = 65536;  // note stack grows down
    char *stack, *stackTop;
    int cret;

    stack = malloc(STACK_SIZE);
    if (stack == NULL) {
        perror("malloc");
        exit(1);
    }
    stackTop = stack + STACK_SIZE;

    // with cloning - child_func will get executed
    cret = clone(child_func, stackTop, CLONE_VM, NULL);

    if (cret == -1) {
        perror("clone");
        exit(0);
    }

    //parents process
    printf ("\nThis is process (thread) %d.\n", getpid());
    y = 1;
    printf("x + y = %d\n", x + y);
    return 0;
}