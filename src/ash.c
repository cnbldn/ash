#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char *PATH = "/usr/bin";

void printPrompt() {
    char *promptStr = "[ash]%: ";
    printf("%s", promptStr);
}

void getInput() {
    char *input = NULL;
    size_t len; // idk what this does

    getline(&input, &len, stdin);

    free(input);
}

void executeProgram() {
    // TODO: check if program is in PATH

    // TODO: handle fork failing
    if (fork()) {
        // parent
        // waits for child to finish
        // (waits for something in the pipe)
        // print the output of child
    } else {
        // child
        // execute the program
    }
    // fork
    // program runs, pipes the output back to parent
    // parent prints output
}

int main(int argc, char *argv[]) {
    while (1) {
        printPrompt();
        getInput();
        executeProgram();
    }
}
