#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "server.h"
#include "util.h"
#include "worker.h"

Node *start(int *argc, char ***argv);
void done(Node *node);

int main(int argc, char **argv) {
  Node *node = start(&argc, &argv);

  if (node->rank == SERVER_RANK) {
    runServer(node);
  } else {
    runWorker(node);
  }

  done(node);

  return 0;
}

Node *start(int *argc, char ***argv) {
  Node *node = (Node *)calloc(1, sizeof(Node));

  gethostname(node->host, 253);

  MPI_Init(argc, argv);
  MPI_Comm_size(MPI_COMM_WORLD, &node->numProcessors);
  MPI_Comm_rank(MPI_COMM_WORLD, &node->rank);

  return node;
}

void done(Node *node) {
  free(node);

  MPI_Finalize();
}
