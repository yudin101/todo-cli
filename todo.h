#ifndef TODO_H
#define TODO_H

#include <stdio.h>

#define FILENAME "list.txt"
#define TEMP_FILENAME "temp.txt"

#define MAX_TEXT 256

typedef struct Todo {
  int id;
  int is_complete;
  char text[256];
} td;

// todo.c
int list_tasks(void);
int add_task(char *text);
int edit_task(char *arg, char *text);
int change_status(char *arg);
int remove_task(char *arg);
void print_help(FILE *stream);

// utils.c
int check_file(FILE *fptr);
int init_src_dest(FILE **src, FILE **dest);
int is_valid_int(char *arg);
int is_found(int id, int found);
int check_text_limit(char *text);
int is_empty(FILE *fptr);

#endif
