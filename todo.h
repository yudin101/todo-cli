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

int list_tasks(void);
int add_task(char *text);
int remove_task(int id);
int change_status(int id);
void print_help(FILE *stream);

#endif
