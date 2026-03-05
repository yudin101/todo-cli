#include <errno.h>
#include <stdio.h>

#include "todo.h"

long get_file_size(FILE *fptr) {
  fseek(fptr, 0, SEEK_END);
  long size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);
  return size;
}

int check_empty(FILE *fptr) {
  if (fptr == NULL) {
    if (errno == ENOENT) {
      fprintf(stdout, "Empty! Use 'todo add' to add tasks.\n");
      return 1;
    } else {
      perror("Error reading data file");
      return -1;
    }
  }

  if (get_file_size(fptr) == 0) {
    fprintf(stdout, "Empty! Use 'todo add' to add tasks.\n");
    return 1;
  }

  return 0;
}

int init_src_dest(FILE **src, FILE **dest) {
  *src = fopen(FILENAME, "r");
  int res = check_empty(*src);
  if (res != 0) {
    return res;
  }

  *dest = fopen(TEMP_FILENAME, "w");

  if (*dest == NULL) {
    perror("Error creating temporary file");
    fclose(*src);
    return -1;
  }

  return 0;
}
