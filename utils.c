#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"

char *FILEPATH = NULL;
char *TEMP_FILEPATH = NULL;

static char *build_path(const char *home, const char *suffix) {
  int len = snprintf(NULL, 0, "%s%s", home, suffix) + 1; // Adding 1 for \0

  char *path = malloc(len);
  if (!path) {
    perror("Failed allocating memory");
    exit(1);
  }

  snprintf(path, len, "%s%s", home, suffix);

  return path;
}

void init_todo_filepaths() {
  char *home = getenv("HOME");

  if (!home) {
    fprintf(stderr, "Error: Could not find HOME environment variable.\n");
    exit(1);
  } 

  FILEPATH = build_path(home, "/.local/share/todo/list.txt");
  TEMP_FILEPATH = build_path(home, "/.local/share/todo/temp.txt");

  // Create the directory if it does not exist
  char mkdir_cmd[1024];
  snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s/.local/share/todo", home);
  system(mkdir_cmd);
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
  *src = fopen(FILEPATH, "r");
  check_file(*src);

  is_empty(*src);

  *dest = fopen(TEMP_FILEPATH, "w");

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
