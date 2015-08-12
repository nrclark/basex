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
int basemain(int argc, char** argv) {
    WalkExitCode exit_code = WALK_OK;
    char hello[17] = "hello hello cuz\x00";
    int x;

    FileMatch *matches = FileMatchCreate();
    matches = FileMatchAdd(matches, hello, 16);
    matches = FileMatchAdd(matches, hello, 16);
    matches = FileMatchAdd(matches, hello, 16);
    matches = FileMatchAdd(matches, hello, 16);
    FileMatchFinish(matches);

    if(argc != 3) {
        fprintf(stderr, "Wrong number of arguments (%d)\n", argc);
        for (x = 0; x < argc; x++) {
            fprintf(stderr, "%d: %s\n", x,argv[x]);
        }
        return 99;
    }

    //exit_code = WalkRecursive(argv[1], argv[2], matches);

    if (exit_code != WALK_OK) {
        fprintf(stderr, "Returned %d\n", exit_code);
        return exit_code;
    }

    FileMatchRewind(&matches);

    while (matches != NULL) {
        if(matches->filename != NULL)
            printf("%s", matches->filename);

        printf(", %08X, %08X, %08X\n", matches->prev, matches, matches->next);
        matches = matches->next;
    }
    FileMatchRewind(&matches);

    //FileMatchDestroy(matches);
	return 0;
}
