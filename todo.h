#ifndef TODO_H
#define TODO_H

#include <stdio.h>

#define FILENAME "list.txt"
#define TEMP_FILENAME "temp.txt"

typedef struct Todo {
  int id;
  int is_complete;
  char text[100];
} td;

// todo.c
int list_tasks(void);
int add_task(char *text);
int edit_task(char *arg, char *text);
int change_status(char *arg);
int remove_task(char *arg);
void print_help(FILE *stream);

// utils.c
int check_empty(FILE *fptr);
int init_src_dest(FILE **src, FILE **dest);
int is_valid_int(char *arg);

#endif
