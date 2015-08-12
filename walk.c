#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "walk.h"

static WalkExitCode recurse(char *target, regex_t *regex, Stack *result) {
    int target_length;
    int dname_length;
    int full_length;

    char *dname;
    char *output;
    char buffer[FILENAME_MAX + 1];

    WalkExitCode exit_code;
    struct dirent *entry;
    struct stat file_stat;
    DIR *dir;

    buffer[FILENAME_MAX] = 0;
    exit_code = WALK_OK;

    dir = opendir(target);
    target_length = strnlen(target, FILENAME_MAX);

    if (dir == NULL) {
        fprintf(stderr, "Can't open %s", target);
        return WALK_BADIO;
    }

    entry = readdir(dir);

    if(entry == NULL)
        return exit_code;

    memcpy(buffer, target, target_length);
    buffer[target_length] = '/';

    while (entry != NULL) {
        dname = entry->d_name;
        dname_length = strnlen(dname, (FILENAME_MAX-2) - target_length);

        if ((strcmp(dname, ".") == 0) || (strcmp(dname, "..") == 0)) {
            entry = readdir(dir);
            continue;
        }

        memcpy(buffer + target_length + 1, dname, dname_length);
        full_length = target_length + 1 + dname_length;
        buffer[full_length] = '\x00';

        if (stat(buffer, &file_stat) == -1) {
            fprintf(stderr, "Can't stat %s\n", buffer);
            exit_code = WALK_BADIO;
            entry = readdir(dir);
            continue;
        }

        if (S_ISDIR(file_stat.st_mode)) {
            exit_code = recurse(buffer, regex, result);
        } else {
            if (S_ISREG(file_stat.st_mode)) {
                if (regexec(regex, dname, 0, 0, 0) == 0) {
                    output = malloc(full_length + 1);
                    if(output == NULL) {
                        closedir(dir);
                        return WALK_NOMEM;
                    }
                    strncpy(output, buffer, full_length);
                    output[full_length] = 0x00;
                    StackPush(result, output); 
                    if(*result == NULL) {
                        closedir(dir);
                        return WALK_NOMEM;
                    }
                }
            }
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return exit_code;
}

WalkExitCode WalkRecursive(char *dname, char *pattern, Stack *result) {
	regex_t regex;
	WalkExitCode exit_code;

	if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB | REG_NEWLINE)) {
	    return WALK_BADPATTERN;
	}
	
    exit_code = recurse(dname, &regex, result);
    regfree(&regex);
	return exit_code;
}
