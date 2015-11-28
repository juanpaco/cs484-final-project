#ifndef UTIL_H
#define UTIL_H

#include "node.h"

// DATA_DIR could be pulled into an env var instead
#define DATA_DIR "../extractor/data/"
#define SERVER_RANK 0
#define MAX_FILENAME_LENGTH 256
#define TERMINATION_MESSAGE "TERMINATE"

// Tags for our MPI communication
enum {
  COMM_TAG_PROCEED
, COMM_TAG_WORK_COMPLETE
, COMM_TAG_WORK_REQUEST
, COMM_TAG_WORK_RESULT
};  

void greet(Node *node);

#endif
