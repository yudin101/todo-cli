#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "todo.h"

static int file_contains(char *expected_str) {
  FILE *fptr = fopen(FILEPATH, "r");

  td temp;

  while (fscanf(fptr, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (strcmp(temp.text, expected_str) == 0) {
      return 0;
    }
  }

  fclose(fptr);

  return 1;
}

static int check_status(int id, int expected_status) {
  FILE *fptr = fopen(FILEPATH, "r");

  td temp;

  while (fscanf(fptr, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id && temp.is_complete == expected_status) {
      return 0;
    }
  }

  fclose(fptr);

  return 1;
}

static int check_text(int id, char *text) {
  FILE *fptr = fopen(FILEPATH, "r");

  td temp;

  while (fscanf(fptr, " %d,%d,%255[^\n]", &temp.id, &temp.is_complete,
                temp.text) == 3) {
    if (temp.id == id && strcmp(temp.text, text) == 0) {
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
  assert(swap_tasks("3", "2") == 1);

  // Normal use
  // Add task
  assert(add_task("First Test Task") == 0);
  assert(check_text(1, "First Test Task") == 0);

  // Edit task
  assert(edit_task("1", "Edited first task") == 0);
  assert(check_text(1,"Edited first task") == 0);

  // Add second task
  assert(add_task("Second Test Task") == 0);
  assert(check_text(2, "Second Test Task") == 0);

  // Add third task
  assert(add_task("Third Test Task") == 0);
  assert(check_text(3, "Third Test Task") == 0);

  // Change status of task #2
  assert(change_status("2") == 0);
  assert(check_status(2, 1) == 0);

  assert(remove_cmp_task() == 0);
  assert(file_contains("Second Test Task") == 1);

  // Check renumbering
  assert(check_text(2, "Third Test Task") == 0); // Since #2 was removed, #3 becomes #2
  assert(add_task("Fourth Test Task") == 0);
  assert(check_text(3, "Fourth Test Task") == 0); // New numbering should start with 3

  // Check Swap
  assert(swap_tasks("3", "2") == 0);
  assert(swap_tasks("8", "2") == 1);
  assert(swap_tasks("3", "8") == 1);
  assert(check_text(2, "Fourth Test Task") == 0);
  assert(check_text(3, "Third Test Task") == 0);

  // Non existent tasks
  assert(edit_task("5", "Any text") == 1);
  assert(remove_task("4") == 1);
  assert(change_status("6") == 1);
  assert(swap_tasks("7", "8") == 1);

  // Clean Up
  assert(remove_task("3") == 0);
  assert(remove_task("2") == 0);
  assert(remove_task("1") == 0);
  assert(file_contains("First Test Task") == 1);
  assert(file_contains("Third Test Task") == 1);
  assert(file_contains("Fourth Test Task") == 1);

  return 0;
}
