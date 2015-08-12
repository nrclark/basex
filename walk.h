/*
 * walk.h
 *
 *  Created on: Aug 11, 2015
 *      Author: nrclark
 */

#ifndef WALK_H_
#define WALK_H_

typedef enum {
    WALK_OK = 0,
    WALK_BADPATTERN = 1,
    WALK_NAMETOOLONG = 2,
    WALK_BADIO = 3,
    WALK_NOMEM = 4,
    WALK_INVALID = 5
} WalkExitCode;

typedef struct FileMatch {
    char *filename;
    struct FileMatch *next;
    struct FileMatch *prev;
} FileMatch;

WalkExitCode WalkRecursive(char *dname, char *pattern, FileMatch **result);

FileMatch * FileMatchCreate();
FileMatch * FileMatchAdd(FileMatch * matches, char *name, int length);
void FileMatchFinish(FileMatch * matches);
void FileMatchDestroy(FileMatch *match_list);
void FileMatchRewind(FileMatch **match_list);
FileMatch * FileMatchIterate(FileMatch **match_list);

#endif /* WALK_H_ */
