#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <err.h>

#include "walk.h"
#include "stack.h"

int main(int argc, char** argv) {
    WalkExitCode exit_code = WALK_OK;
    Stack result = NULL;
    char *match;

    exit_code = WalkRecursive(argv[1], argv[2], &result);

    if (exit_code != WALK_OK) {
        fprintf(stderr, "Returned %d\n", exit_code);
    }

    while(result != NULL) {
        match = (char *)StackPop(&result);
        fprintf(stdout, "Found: %s\n", match);
        free(match);
    }
	return exit_code;
}
