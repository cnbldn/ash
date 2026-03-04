// Currently loosely following "github.com/tokenrove/build-your-own-shell"
#include <sys/types.h>
#include <sys/wait.h>
#define DEBUG 1

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "/usr/bin/"

// parses line into an array of strings. Does in fact malloc.
void parseLine(char *line, char **tokenv, int *tokenc) {
    *tokenc = 0;

    char *tkn = NULL;
    tkn = strtok(line, " \n");
    while (tkn) {
        tokenv[*tokenc] = strdup(tkn);
        (*tokenc)++;
        tkn = strtok(NULL, " \n");
    }

#if DEBUG
    printf("c:%d\n", *tokenc);
    for (int i = 0; i < *tokenc; i++) {
        printf("[%d] %s\n", i, tokenv[i]);
    }
#endif /* if DEBUG */
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

        char **tokenv = malloc(ARG_MAX * sizeof(char *));
        int tokenc;

        parseLine(line, tokenv, &tokenc);

        // fork and execute program
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // child
            // BUG: i feel like there is some memory leak here
            char *programPath = strdup(PATH);
            realloc(programPath,
                    sizeof(char) * (strlen(programPath) + strlen(tokenv[0])));
            strcat(programPath, tokenv[0]);
            execve(programPath, tokenv, NULL);
        } else { // parent
            wait(NULL);
        }

        // free allocated tokens
        for (int i = 0; i < tokenc; i++) {
            free(tokenv[i]);
        }
    }
}
