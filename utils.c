#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

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

  return 0;
}

int is_empty(FILE *fptr) {
  fseek(fptr, 0, SEEK_END);
  long size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  if (size == 0) {
    fprintf(stdout, "Empty! Use 'todo add' to add tasks.\n");
    exit(0);
  }

  return 0;
}

int init_src_dest(FILE **src, FILE **dest) {
  *src = fopen(FILENAME, "r");
  check_file(*src);

  is_empty(*src);

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

int is_found(int id, int found) {
  if (!found) {
    fprintf(stderr, "Error: Task ID %d not found.\n", id);
    exit(1);
  }

  return 0;
}

int check_text_limit(char *text) {
  if (strlen(text) >= MAX_TEXT) {
    fprintf(stderr, "Error: Task too long. Max %d characters.\n", MAX_TEXT - 1);
    exit(1);
  }

  return 0;
}
