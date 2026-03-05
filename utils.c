#include <errno.h>
#include <stdio.h>

int check_exists(FILE *fptr) {
  if (fptr == NULL) {
    if (errno == ENOENT) {
      fprintf(stdout, "Empty! Use 'todo add' to add tasks.\n");
      return 1;
    } else {
      perror("Error reading data file");
      return -1;
    }
  }

  return 0;
}
