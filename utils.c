#include <errno.h>
#include <stdio.h>

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
