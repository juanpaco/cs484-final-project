#include "server.h"

#include <stdio.h>

#include "job.h"
#include "util.h"

// JobResult
//
// Anyway, once that is decided, I need to actually send the file names to the worker.
// Then the worker needs to send some result back
void runServer(Node *node) {
  JobList *jobList = buildJobList(DATA_DIR);

  greet(node);

  jobList = freeJobList(jobList);
}
