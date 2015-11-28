#ifndef NODE_H
#define NODE_H

// This captures the MPI information for a given process.  It's a "node" in the
// MPI Network
typedef struct NodeStruct {
  char host[256];
  int numProcessors;
  int rank;
} Node;

#endif

