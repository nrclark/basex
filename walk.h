/*
 * walk.h
 *
 *  Created on: Aug 11, 2015
 *      Author: nrclark
 */

#ifndef WALK_H_
#define WALK_H_

#include "stack.h"

typedef enum {
    WALK_OK = 0,
    WALK_BADPATTERN = 1,
    WALK_NAMETOOLONG = 2,
    WALK_BADIO = 3,
    WALK_NOMEM = 4,
    WALK_INVALID = 5
} WalkExitCode;

WalkExitCode WalkRecursive(char *dname, char *pattern, Stack *result);

#endif /* WALK_H_ */
