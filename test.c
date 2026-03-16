#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "todo.h"

int file_contains(char *expected_str) {
  FILE *fptr = fopen(FILEPATH, "r");

  td temp;

  while (fscanf(fptr, " %d, %d, %255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (strcmp(temp.text, expected_str) == 0) {
      return 0;
    }
  }

  fclose(fptr);

  return 1;
}

int check_status(int id, int expected_status) {
  FILE *fptr = fopen(FILEPATH, "r");

  td temp;

  while (fscanf(fptr, " %d, %d, %255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id && temp.is_complete == expected_status) {
      return 0;
    }
  }

  fclose(fptr);

  return 1;
}

int main(void) {
  if (init_todo_filepaths("test") != 0) {
    return 1;
  }

  // Before data file
  assert(edit_task("3", "Any text") == 1);
  assert(remove_task("2") == 1);
  assert(change_status("3") == 1);

  // Normal use
  // Add task
  assert(add_task("First Test Task") == 0);
  assert(file_contains("First Test Task") == 0);

  // Edit task
  assert(edit_task("1", "Edited first task") == 0);
  assert(file_contains("Edited first task") == 0);

  // Add second task
  assert(add_task("Second Test Task") == 0);
  assert(file_contains("Second Test Task") == 0);

  // Change status of task #2
  assert(change_status("2") == 0);
  assert(check_status(2, 1) == 0);

  assert(remove_cmp_task() == 0);
  assert(file_contains("Second Test Task") == 1);

  // Non existent tasks
  assert(edit_task("3", "Any text") == 1);
  assert(remove_task("2") == 1);
  assert(change_status("3") == 1);

  // Clean
  assert(remove_task("1") == 0);
  assert(file_contains("First Test Task") == 1);

  return 0;
}
