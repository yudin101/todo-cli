#ifndef TODO_H
#define TODO_H

#include <stdio.h>

#define MAX_TEXT 256

#define RED "\033[1;31m" // Bold Red
#define GRN "\033[0;32m"
#define YLW "\033[0;33m"
#define RST "\033[0m"

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
int swap_tasks(char *id_1_arg, char *id_2_arg);
int change_status(char *id_arg);
int remove_task(char *id_arg);
int remove_cmp_task(void);
void print_help(FILE *stream);

// utils.c
int init_todo_filepaths(char *env);
int check_file(FILE *fptr);
int init_src_dest(FILE **src, FILE **dest);
int is_valid_int(char *arg);
int is_found(int id, int found);
int check_text_limit(char *text);
int is_empty(FILE *fptr);
void log_error(char *fmt, ...);
void sys_error(char *msg);

#endif
