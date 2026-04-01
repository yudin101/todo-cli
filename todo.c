#include <stdio.h>
#include <unistd.h>

#include "todo.h"

int list_tasks(void) {
  FILE *fptr = fopen(FILEPATH, "r");

  if (check_file(fptr) != 0) {
    return 1;
  }

  if (is_empty(fptr) != 0) {
    return 1;
  }

  int is_a_tty =
      isatty(STDOUT_FILENO); // Checking if the terminal supports colors
  char *color = "";
  char *reset = "";

  td temp;
  while (fscanf(fptr, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {

    if (is_a_tty) {
      color = temp.is_complete ? GRN : YLW;
      reset = RST;
    }

    fprintf(stdout, "%s%d [%c] %s%s\n", color, temp.id,
            temp.is_complete ? 'X' : ' ', temp.text, reset);
  }

  fclose(fptr);
  return 0;
}

int add_task(char *text) {
  int exists = access(FILEPATH, F_OK);

  FILE *fptr = fopen(FILEPATH, "a+");

  if (check_file(fptr) != 0) {
    return 1;
  }

  if (check_text_limit(text) != 0) {
    return 1;
  }

  int last_id = 0;
  int initial_is_complete = 0;
  td temp;

  if (exists == 0) {
    while (fscanf(fptr, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                  temp.text) == 3) {
      last_id = temp.id;
    }
  }

  fprintf(fptr, "%d,%d,%s\n", last_id + 1, initial_is_complete, text);

  fclose(fptr);

  return 0;
}

int edit_task(char *id_arg, char *text) {
  int id = is_valid_int(id_arg);
  if (id < 0) {
    return 1;
  }

  if (check_text_limit(text) != 0) {
    return 1;
  }

  FILE *flist, *ftemp;

  if (init_src_dest(&flist, &ftemp) != 0) {
    return 1;
  }

  td temp;
  int found = 0;

  while (fscanf(flist, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id) {
      fprintf(ftemp, "%d,%d,%s\n", temp.id, temp.is_complete, text);
      found = 1;
      continue;
    }

    fprintf(ftemp, "%d,%d,%s\n", temp.id, temp.is_complete, temp.text);
  }

  fclose(flist);
  fclose(ftemp);

  remove(FILEPATH);
  rename(TEMP_FILEPATH, FILEPATH);

  if (is_found(id, found) != 0) {
    return 1;
  }

  return 0;
}

int swap_tasks(char *id_1_arg, char *id_2_arg) {
  FILE *flist, *ftemp;

  if (init_src_dest(&flist, &ftemp) != 0) {
    return 1;
  }

  int id_1 = is_valid_int(id_1_arg);
  int id_2 = is_valid_int(id_2_arg);
  if (id_1 < 0 || id_2 < 0) {
    return 1;
  }

  td tasks[1000];

  int found_1 = 0;
  int found_2 = 0;

  int count = 0;

  while (fscanf(flist, " %d,%d,%255[^\n]", &tasks[count].id,
                &tasks[count].is_complete, tasks[count].text) == 3) {
    if (tasks[count].id == id_1) {
      found_1 = 1;
    } else if (tasks[count].id == id_2) {
      found_2 = 1;
    }

    count++;
  }

  if (is_found(id_1, found_1) != 0 || is_found(id_2, found_2) != 0) {
    fclose(flist);
    fclose(ftemp);
    remove(TEMP_FILEPATH);
    return 1;
  }

  int task_1_idx;
  int task_2_idx;

  for (int i = 0; i < count; i++) {
    if (tasks[i].id == id_1)
      task_1_idx = i;
    if (tasks[i].id == id_2)
      task_2_idx = i;
  }

  td temp;
  temp = tasks[task_1_idx];
  tasks[task_1_idx] = tasks[task_2_idx];
  tasks[task_2_idx] = temp;

  for (int i = 0; i < count; i++) {
    if (tasks[i].id == id_1) {
      fprintf(ftemp, "%d,%d,%s\n", id_2, tasks[i].is_complete, tasks[i].text);
      continue;
    } else if (tasks[i].id == id_2) {
      fprintf(ftemp, "%d,%d,%s\n", id_1, tasks[i].is_complete, tasks[i].text);
      continue;
    }

    fprintf(ftemp, "%d,%d,%s\n", tasks[i].id, tasks[i].is_complete,
            tasks[i].text);
  }

  fclose(flist);
  fclose(ftemp);

  remove(FILEPATH);
  rename(TEMP_FILEPATH, FILEPATH);

  return 0;
}

int change_status(char *id_arg) {
  FILE *flist, *ftemp;

  if (init_src_dest(&flist, &ftemp) != 0) {
    return 1;
  }

  int id = is_valid_int(id_arg);
  if (id < 0) {
    return 1;
  }

  td temp;
  int found = 0;

  while (fscanf(flist, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id) {
      int current_status = temp.is_complete;
      int new_status = current_status == 0 ? 1 : 0;
      fprintf(ftemp, "%d,%d,%s\n", temp.id, new_status, temp.text);
      found = 1;
      continue;
    }

    fprintf(ftemp, "%d,%d,%s\n", temp.id, temp.is_complete, temp.text);
  }

  fclose(flist);
  fclose(ftemp);

  remove(FILEPATH);
  rename(TEMP_FILEPATH, FILEPATH);

  if (is_found(id, found) != 0) {
    return 1;
  }

  return 0;
}

int remove_task(char *id_arg) {
  FILE *flist, *ftemp;

  if (init_src_dest(&flist, &ftemp) != 0) {
    return 1;
  }

  int id = is_valid_int(id_arg);
  if (id < 0) {
    return 1;
  }

  td temp;
  int found = 0;
  int i = 0;

  while (fscanf(flist, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id) {
      found = 1;
      continue; // Skip the task we want to delete
    }

    fprintf(ftemp, "%d,%d,%s\n", i + 1, temp.is_complete, temp.text);
    i++;
  }

  fclose(flist);
  fclose(ftemp);

  remove(FILEPATH);
  rename(TEMP_FILEPATH, FILEPATH);

  if (is_found(id, found) != 0) {
    return 1;
  }

  return 0;
}

int remove_cmp_task(void) {
  FILE *flist, *ftemp;

  if (init_src_dest(&flist, &ftemp) != 0) {
    return 1;
  }

  td temp;
  int i = 0;

  while (fscanf(flist, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.is_complete == 0) {
      fprintf(ftemp, "%d,%d,%s\n", i + 1, temp.is_complete, temp.text);
      i++;
    }
  }

  fclose(flist);
  fclose(ftemp);

  remove(FILEPATH);
  rename(TEMP_FILEPATH, FILEPATH);

  return 0;
}

void print_help(FILE *stream) {
  fprintf(stream, "Usage:  todo COMMAND\n");
  fprintf(stream, "Todo CLI - A simple task manager\n\n");
  fprintf(stream, "Commands:\n");
  fprintf(stream, "  %-12s List all tasks\n", "ls");
  fprintf(stream, "  %-12s Add a new task\n", "add");
  fprintf(stream, "  %-12s Edit existing task by ID\n", "ed");
  fprintf(stream, "  %-12s Swap two tasks by ID\n", "swp");
  fprintf(stream, "  %-12s Toggle task completion by ID\n", "cmp");
  fprintf(stream, "  %-12s Remove a task by ID\n", "rm");
  fprintf(stream, "  %-12s Remove completed tasks\n", "rmcmp");
  fprintf(stream, "  %-12s Show this menu\n", "help");
}
