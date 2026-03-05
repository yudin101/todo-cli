#include <stdio.h>
#include <unistd.h>

#include "todo.h"

int list_tasks(void) {
  FILE *fptr = fopen(FILENAME, "r");

  int res = check_empty(fptr);
  if (res != 0) {
    return res;
  }

  td temp;
  while (fscanf(fptr, " %d, %d, %[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    printf("%d [%c] %s\n", temp.id, temp.is_complete ? 'X' : ' ', temp.text);
  }

  fclose(fptr);
  return 0;
}

int add_task(char *text) {
  int exists = access(FILENAME, F_OK);

  FILE *fptr = fopen(FILENAME, "a+");

  if (fptr == NULL) {
    perror("Error opening data file");
    return -1;
  }

  int last_id = 0;
  int initial_is_complete = 0;
  td temp;

  if (exists == 0) {
    while (fscanf(fptr, " %d, %d, %[^\n]", &temp.id, &temp.is_complete,
                  temp.text) == 3) {
      last_id = temp.id;
    }
  }

  fprintf(fptr, "%d, %d, %s\n", last_id + 1, initial_is_complete, text);

  fclose(fptr);

  return 0;
}

int edit_task(char *arg, char *text) {
  FILE *flist, *ftemp;

  int res = init_src_dest(&flist, &ftemp);
  if (res != 0) {
    return res;
  }

  int id = is_valid_int(arg);

  td temp;
  int found = 0;

  while (fscanf(flist, " %d, %d, %[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id) {
      fprintf(ftemp, "%d, %d, %s\n", temp.id, temp.is_complete, text);
      found = 1;
      continue;
    }

    fprintf(ftemp, "%d, %d, %s\n", temp.id, temp.is_complete, temp.text);
  }

  fclose(flist);
  fclose(ftemp);

  remove(FILENAME);
  rename(TEMP_FILENAME, FILENAME);

  if (!found) {
    fprintf(stderr, "Error: Task ID %d not found.\n", id);
    return 1;
  }

  return 0;
}

int change_status(char *arg) {
  FILE *flist, *ftemp;

  int res = init_src_dest(&flist, &ftemp);
  if (res != 0) {
    return res;
  }

  int id = is_valid_int(arg);

  td temp;
  int found = 0;

  while (fscanf(flist, " %d, %d, %[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id) {
      int current_status = temp.is_complete;
      int new_status = current_status == 0 ? 1 : 0;
      fprintf(ftemp, "%d, %d, %s\n", temp.id, new_status, temp.text);
      found = 1;
      continue;
    }

    fprintf(ftemp, "%d, %d, %s\n", temp.id, temp.is_complete, temp.text);
  }

  fclose(flist);
  fclose(ftemp);

  remove(FILENAME);
  rename(TEMP_FILENAME, FILENAME);

  if (!found) {
    fprintf(stderr, "Error: Task ID %d not found.\n", id);
    return 1;
  }

  return 0;
}

int remove_task(char *arg) {
  FILE *flist, *ftemp;

  int res = init_src_dest(&flist, &ftemp);
  if (res != 0) {
    return res;
  }

  int id = is_valid_int(arg);

  td temp;
  int found = 0;

  while (fscanf(flist, " %d, %d, %[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id) {
      found = 1;
      continue; // Skip the task we want to delete
    }

    fprintf(ftemp, "%d, %d, %s\n", temp.id, temp.is_complete, temp.text);
  }

  fclose(flist);
  fclose(ftemp);

  remove(FILENAME);
  rename(TEMP_FILENAME, FILENAME);

  if (!found) {
    fprintf(stderr, "Error: Task ID %d not found.\n", id);
    return 1;
  }

  return 0;
}

void print_help(FILE *stream) {
  fprintf(stream, "Usage:  todo COMMAND\n");
  fprintf(stream, "Todo CLI - A simple task manager\n\n");
  fprintf(stream, "Commands:\n");
  fprintf(stream, "  %-12s List all tasks\n", "list");
  fprintf(stream, "  %-12s Add a new task\n", "add");
  fprintf(stream, "  %-12s Edit existing task by ID\n", "edt");
  fprintf(stream, "  %-12s Toggle task completion by ID\n", "cmp");
  fprintf(stream, "  %-12s Remove a task by ID\n", "rm");
  fprintf(stream, "  %-12s Show this menu\n", "help");
}
