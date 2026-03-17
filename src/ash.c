// Currently loosely following "github.com/tokenrove/build-your-own-shell"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PATH "/usr/bin/"
#define TOKENV_SIZE (ARG_MAX * sizeof(char *))

void parseLine(char *line, char **tokenv, int *tokenc) {
    *tokenc = 0;
    memset(tokenv, 0, TOKENV_SIZE);

    char *tkn = NULL;
    tkn = strtok(line, " \n");
    while (tkn) {
        tokenv[*tokenc] = strdup(tkn);
        (*tokenc)++;
        tkn = strtok(NULL, " \n");
    }
}

int main(int argc, char *argv[]) {

    char **tokenv = malloc(TOKENV_SIZE);
    int tokenc = 0;

    while (1) {
        // print the prompt
        fputs("[ash]%: ", stdout);
        // printf("%s", "[ash]%: ");
        fflush(stdout);

        // read input
        char *line = NULL;
        size_t lineSize = 0;

        getline(&line, &lineSize, stdin);

        if (feof(stdin)) {
            puts("EOF, exiting...");
            return 0;
        }
        parseLine(line, tokenv, &tokenc);

        // TODO: check builtin

        pid_t pid = fork();
        switch (pid) {
        case -1: {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        case 0: { // child
            int exec_retval = execvp(tokenv[0], tokenv);
            return 0;
        }
        default: { // parent
            wait(NULL);
            break;
        }
        }

        // free stuff
        free(line);
        for (int i = 0; i < tokenc; i++) {
            free(tokenv[i]);
        }
    }
}
