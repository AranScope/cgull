#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "server_logger.h"
#include "server_constants.h"

/*
    Read a file into a character buffer, pretty simple.
*/
char *read_file(char *file_url) {

    // the web root is always . because we've used chdir previously
    char web_root[] = ".";

    char file_path[MAX_BUFFER_SIZE] = {0};

    strncat(file_path, web_root, sizeof(web_root));
    strncat(file_path, file_url, sizeof(file_path)); // TODO: Make sure we're using buffer sizes properly.

    debug("Reading file at path: %s", file_path);
    
    char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
 
    // read in binary, gives us the opportunity to add support for binary files like pngs.
    FILE *fp = fopen(file_path, "rb");

    if(!fp) {
        info("No such resource found at: %s", file_path);
        return NULL;
    }

    // find out the length of the file
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // read the whole thing into memory
    fread(buffer, fsize, 1, fp);
    fclose(fp);
    
    // null terminate the buffer
    buffer[fsize] = '\0';

    return buffer;
}
