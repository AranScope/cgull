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
    Returns the length of the buffer
*/
int read_file(char *file_url, char *buffer) {

    // the web root is always . because we've used chdir previously
    char web_root[] = ".";

    char file_path[MAX_URI_SIZE] = {0};

    strncat(file_path, web_root, sizeof(web_root));
    strncat(file_path, file_url, sizeof(file_path)); // TODO: Make sure we're using buffer sizes properly.

    debug("Reading file at path: %s", file_path);
 
    // read in binary, gives us the opportunity to add support for binary files like pngs.
    FILE *fp = fopen(file_path, "rb");

    if(!fp) {
        info("No such resource found at: %s", file_path);
        return -1;
    }

    // find out the length of the file
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    debug("File length is: %ld", fsize);

    // read the whole thing into memory
    fread(buffer, fsize, 1, fp);
    fclose(fp);
    
    // null terminate the buffer
    buffer[fsize] = '\0';

    return fsize;
}
