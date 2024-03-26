#ifndef TARSAU_H
#define TARSAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_FILES 32
#define MAX_SIZE_PERMITTED 200 * 1024 * 1024

typedef struct {
    char filename[256];
    mode_t permissions;
    off_t size;
} FileRecord;

void merge_files(int argc, char *argv[], const char *output_file);
void create_archive(int argc, char *argv[], const char *archive_file);
void print_usage();

#endif /* TARSAU_H */
