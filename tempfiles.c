#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

char tempdir[PATH_MAX + 1];

int find_tmpdir(char *result) {
    char *temp_candidates[] = {"TMPDIR", "TMP", "TEMP"};
    char *temp;
    int x;
    int exit_code = EXIT_FAILURE;
    
    for(x = 0; x < 3; x++) {
        temp = getenv(temp_candidates[x]);
        if (temp != NULL) {
            exit_code = EXIT_SUCCESS;
            break;
        }
    }
    
    if (exit_code == EXIT_SUCCESS) {
        x = errno;
        realpath(temp, result);
        errno = x;
        if(result[0] != '\x00') {
            return EXIT_SUCCESS;
        }
    }

    strcpy(result, "/tmp");
    return EXIT_SUCCESS;
}


int cleanup(char *target_dir) {
    char command[PATH_MAX + sizeof("rm -rf ") + ];
    strcpy(command, "rm -rf ");
    strncat(command, target_dir, PATH_MAX);
    return system(command);
}

int main(void) {
    char buffer[PATH_MAX + 1];
    buffer[PATH_MAX] = '\x00';

    find_tmpdir(buffer);
    strncpy(tempdir, buffer, (PATH_MAX - 16));
    strcat(tempdir,"/basex-XXXXXX");
    
    printf("errno: %d\n", errno);

    mkdtemp(tempdir);
    printf("Name: %s\n", tempdir);
    printf("errno: %d\n", errno);
    printf("Cleanup: %d\n", cleanup(tempdir));
    return 0;
}

