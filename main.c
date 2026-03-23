#include <stdio.h>
#include <string.h>

#include "todo.h"

int main(int argc, char *argv[]) {
  if (init_todo_filepaths("prod") != 0) {
    return 1;
  }

  if (argc < 2) {
    print_help(stderr);
    return 1;
  } else if (strcmp(argv[1], "list") == 0) {

    // List the tasks
    list_tasks();
  } else if (strcmp(argv[1], "add") == 0) {
    if (argc < 3) {
      fprintf(stderr, "Usage: todo add <text>\n");
      return 1;
    }

    // Append new task
    if (add_task(argv[2]) == 0) {
      list_tasks();
    }
  } else if (strcmp(argv[1], "edt") == 0) {
    if (argc < 4) {
      fprintf(stderr, "Usage: todo edt <id> <text>\n");
      return 1;
    }

    // Edit existing task
    if (edit_task(argv[2], argv[3]) == 0) {
      list_tasks();
    }
  } else if (strcmp(argv[1], "swap") == 0) {
    if (argc < 4) {
      fprintf(stderr, "Usage: todo swap <id> <id>\n");
      return 1;
    }

    if (swap_tasks(argv[2], argv[3]) == 0) {
      list_tasks();
    }
  }else if (strcmp(argv[1], "cmp") == 0) {
    if (argc < 3) {
      fprintf(stderr, "Usage: todo cmp <id>\n");
      return 1;
    }

    // Change task status
    if (change_status(argv[2]) == 0) {
      list_tasks();
    }
  } else if (strcmp(argv[1], "rm") == 0) {
    if (argc < 3) {
      fprintf(stderr, "Usage: todo rm <id>\n");
      return 1;
    }

    // Remove task with given id
    if (remove_task(argv[2]) == 0) {
      list_tasks();
    }
  } else if (strcmp(argv[1], "rmcmp") == 0) {
    // Remove completed task
    if (remove_cmp_task() == 0) {
      list_tasks();
    }
  } else if (strcmp(argv[1], "help") == 0) {
    // Print help
    print_help(stdout);
  } else {
    print_help(stderr);
    return 1;
  }

  return 0;
}
