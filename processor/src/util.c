#include "util.h"

#include <stdio.h>

void greet(Node *node) {
  char *msg;

  if (node->rank == SERVER_RANK) {
    msg = "(%d) SERVER running on %s, %d total nodes\n";
  } else {
    msg = "(%d) WORKER running on %s, %d total nodes\n";
  }

  printf(msg, node->rank, node->host, node->numProcessors);
}
