// Currently loosely following "github.com/tokenrove/build-your-own-shell"

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define NOCOLOR "\x1b[0m"

char **parseLine(char *line) {
    char **tokenv = malloc(sizeof(char *) * ARG_MAX);
    size_t tokenc = 0;

    char *tkn = NULL;
    tkn = strtok(line, " \n");
    if (tkn == NULL)
        return tokenv;
    tokenv[tokenc++] = tkn;

    while ((tkn = strtok(NULL, " \n"))) {
        tokenv[tokenc++] = tkn;
    }

    return tokenv;
}

int main(int argc, char *argv[]) {
    while (1) {
        // print the prompt
        printf("%s", "[ash]%: ");
        fflush(stdout);

        // read input
        char *line = NULL;
        size_t lineSize = 0;

        getline(&line, &lineSize, stdin);
        int tokenc = 3;
        char **tokenv = parseLine(line);
    }
}
