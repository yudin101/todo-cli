#ifndef TODO_H
#define TODO_H

#include <stdio.h>

#define MAX_TEXT 256

extern char *FILEPATH;
extern char *TEMP_FILEPATH;

typedef struct Todo {
  int id;
  int is_complete;
  char text[256];
} td;

// todo.c
int list_tasks(void);
int add_task(char *text);
int edit_task(char *id_arg, char *text);
int change_status(char *id_arg);
int remove_task(char *id_arg);
void print_help(FILE *stream);

// utils.c
void init_todo_filepaths();
int check_file(FILE *fptr);
int init_src_dest(FILE **src, FILE **dest);
int is_valid_int(char *arg);
int is_found(int id, int found);
int check_text_limit(char *text);
int is_empty(FILE *fptr);

#endif
