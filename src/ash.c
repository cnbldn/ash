#include <stdio.h>
#include <stdlib.h>

int printPrompt() {
    printf("[ash]%%: ");
    return 1;
}

void getInput() {
    char *input = NULL;
    size_t len; // idk what this does

    getline(&input, &len, stdin);

    free(input);
}

int main(int argc, char *argv[]) {
    while (1) {
        printPrompt();
        getInput();
    }
}
