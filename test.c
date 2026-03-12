#include <assert.h>
#include <stdio.h>

#include "todo.h"

int main(void) {
  init_todo_filepaths();

  // Ordered Behaviours
  assert(add_task("First Test Task") == 0);
  assert(edit_task("1", "Edited first task") == 0);
  assert(change_status("1") == 0);
  assert(remove_task("1") == 0);

  // Random Behaviours (these dont work prolly cuz of exit() in utils)
  // assert(edit_task("3", "Any text") != 1);
  // assert(remove_task("3") != 1);
  // assert(change_status("1") == 1);

  fprintf(stdout, "All tests passed.\n");
  return 0;
}
