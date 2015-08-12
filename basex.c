#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "walk.h"
#include "stack.h"

int main(int argc, char** argv) {
    WalkExitCode exit_code = WALK_OK;
    Stack result = NULL;
    unsigned int count = 0;
    char *match;

    exit_code = WalkRecursive(argv[1], argv[2], &count, &result);

    if (exit_code != WALK_OK) {
        fprintf(stderr, "Returned %d\n", exit_code);
    }

    while(result != NULL) {
        match = (char *)StackPop(&result);
        fprintf(stdout, "Found: %s\n", match);
        free(match);
    }
    fprintf(stdout, "%d matches.\n", count);
	return exit_code;
}
