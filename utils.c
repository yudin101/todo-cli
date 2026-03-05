#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "todo.h"

long get_file_size(FILE *fptr) {
  fseek(fptr, 0, SEEK_END);
  long size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);
  return size;
}

int check_file(FILE *fptr) {
  if (fptr == NULL) {
    if (errno == ENOENT) {
      fprintf(stdout, "Empty! Use 'todo add' to add tasks.\n");
      exit(0);
    } else {
      perror("Error opening data file");
      exit(1);
    }
  }

  if (get_file_size(fptr) == 0) {
    fprintf(stdout, "Empty! Use 'todo add' to add tasks.\n");
    exit(0);
  }

  return 0;
}

int init_src_dest(FILE **src, FILE **dest) {
  *src = fopen(FILENAME, "r");
  check_file(*src);

  *dest = fopen(TEMP_FILENAME, "w");

  if (*dest == NULL) {
    perror("Error creating temporary file");
    fclose(*src);
    exit(1);
  }

  return 0;
}

int is_valid_int(char *arg) {
  int id = atoi(arg);
  if (id == 0 && arg[0] != '0') {
    fprintf(stderr, "Error: '%s' is not a valid ID.\n", arg);
    exit(1);
  }

  return id;
}
