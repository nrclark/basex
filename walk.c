#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "walk.h"

static WalkExitCode recurse(char *target, regex_t *regex, FileMatch *result) {
    int target_length;
    int dname_length;
    int full_length;

    char *dname;
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
            fprintf(stderr, "Can't stat %s", buffer);
            exit_code = WALK_BADIO;
            entry = readdir(dir);
            continue;
        }

        if (S_ISDIR(file_stat.st_mode)) {
            exit_code = recurse(buffer, regex, result);
        } else {
            if (S_ISREG(file_stat.st_mode)) {
                if (regexec(regex, dname, 0, 0, 0) == 0) {
                    result = FileMatchAdd(result, buffer, full_length);
                    if(result == NULL) {
                        return WALK_NOMEM;
                    }
                }
            }
        }
        entry = readdir(dir);
    }
    return exit_code;
}

WalkExitCode WalkRecursive(char *dname, char *pattern, FileMatch **result) {
	regex_t regex;
	WalkExitCode exit_code;

	FileMatch *matches = FileMatchCreate();
	*result = matches;

	if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB | REG_NEWLINE)) {
	    return WALK_BADPATTERN;
	}

	exit_code = recurse(dname, &regex, matches);
	regfree(&regex);

	return exit_code;
}

void FileMatchFinish(FileMatch * matches) {
    if(matches->next != NULL) {
        free(matches->next);
    }

    if(matches->filename != NULL) {
        free(matches->filename);
    }

    matches = matches->prev;
    free(matches->next);
    matches->next = NULL;
}

FileMatch * FileMatchAdd(FileMatch * matches, char *name, int length) {
    matches->filename = malloc(length + 1);
    matches->next = calloc(1,sizeof(FileMatch));

    if((matches->filename == NULL) || (matches->next == NULL)) {
        return NULL;
    }

    strncpy(matches->filename, name, length);
    matches->filename[length] = '\x00';
    matches->next->prev = matches;

    return matches->next;
}

void FileMatchRewind(FileMatch **match_list) {
    while((*match_list)->prev != NULL) {
        *match_list = (*match_list)->prev;
    }
}

FileMatch * FileMatchIterate(FileMatch **match_list) {
    FileMatch *result = *match_list;

    if((*match_list)->next != NULL)
        *match_list = (*match_list)->next;
    return result;
}

void FileMatchDestroy(FileMatch *match_list) {
    FileMatch *temp;
    FileMatchRewind(&match_list);

    while(match_list != NULL) {
        temp = match_list->next;

        if(match_list->filename != NULL) {
            free(match_list->filename);
        }

        free(match_list);
        match_list = temp;
    }
}

FileMatch * FileMatchCreate() {
    FileMatch * result;
    result = calloc(1,sizeof(FileMatch));

    return result;
}
