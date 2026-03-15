#include <assert.h>

#include "todo.h"

int main(void) {
  if (init_todo_filepaths() != 0) {
    return 1;
  }

  // Before data file
  assert(edit_task("3", "Any text") == 1);
  assert(remove_task("2") == 1);
  assert(change_status("3") == 1);

  // Normal use
  assert(add_task("First Test Task") == 0);
  assert(add_task("Second Test Task") == 0);
  assert(edit_task("1", "Edited first task") == 0);
  assert(change_status("2") == 0);
  assert(remove_cmp_task() == 0);

  // Non existent tasks
  assert(edit_task("3", "Any text") == 1);
  assert(remove_task("2") == 1);
  assert(change_status("3") == 1);

  // Clean
  assert(remove_task("1") == 0);

  return 0;
}
