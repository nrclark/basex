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
#include "list.h"

int main(int argc, char** argv) {
    WalkExitCode exit_code = WALK_OK;
    ListEntry *result = NULL;

    exit_code = WalkRecursive(argv[1], argv[2], &result);

    if (exit_code != WALK_OK) {
        fprintf(stderr, "Returned %d\n", exit_code);
    }

    while (result->next != NULL) {
        if(result->data != NULL)
            printf("%s", (char *)(result->data));

        printf(", %08X, %08X, %08X\n", result->prev, result, result->next);
        result = result->next;
    }
    
    if(result->data != NULL)
        printf("%s", (char *)(result->data));

    printf(", %08X, %08X, %08X\n", result->prev, result, result->next);
    return 0;
    ListDestroy(result);
	return 0;
}
