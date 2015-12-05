#include "worker.h"

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "job.h"
#include "util.h"
#include "calculate.h"

JobResult *process(char *filename, char *phrase);
void sendResult(JobResult *jobResult);

void runWorker(Node *node) {
  char filename[MAX_FILENAME_LENGTH]; // my current job
  int placeholder = 0; // We use this as a placeholder for our MPI comms
  MPI_Status status;
  int keepGoing = 1;
  JobResult *jobResult;

 // greet(node);

  while (keepGoing) {
    // Must reset the filename so we don't get left without a terminating
    // null character.
    memset(filename, 0, MAX_FILENAME_LENGTH);

    // Request work
    //printf("(%d) Worker asking for work\n", node->rank);
    MPI_Send(
      &placeholder
    , 1
    , MPI_INT
    , 0
    , COMM_TAG_WORK_REQUEST
    , MPI_COMM_WORLD
    );
  
    //printf("(%d) Worker waiting for work request answer\n", node->rank);
    MPI_Recv(
      filename
    , MAX_FILENAME_LENGTH
    , MPI_CHAR
    , 0
    , COMM_TAG_WORK_REQUEST
    , MPI_COMM_WORLD
    , &status
    );

    //printf("(%d) Told to work on %s\n", node->rank, filename);

    if (strcmp(filename, TERMINATION_MESSAGE)) {
      //printf("(%d) Working on %s\n", node->rank, filename);
      // work on it
      sendResult(process(filename, "and it came to pass"));
    } else {
      // terminate
      //printf("(%d) Told to terminate\n", node->rank);
      keepGoing = 0;
    }
  }

  //printf("(%d) terminating\n", node->rank);
}

// TODO: Landen's sequential function goes here
JobResult *process(char *filename, char *phrase) {
  JobResult *jobResult = (JobResult *)calloc(1, sizeof(JobResult));

  jobResult->result = calculate(filename, phrase);

  return jobResult;
}

void sendResult(JobResult *jobResult) {
  int placeholder;
  MPI_Status status;

  // Let the server know we have some finished work
  MPI_Send(
    &placeholder
  , 1
  , MPI_INT
  , 0
  , COMM_TAG_WORK_COMPLETE
  , MPI_COMM_WORLD
  );

  // Wait for the server to tell us to send the results
  MPI_Recv(
    &placeholder
  , 1
  , MPI_INT
  , 0
  , COMM_TAG_PROCEED
  , MPI_COMM_WORLD
  , &status
  );
  
  // Then send the results
  MPI_Send(
    &jobResult->result
  , 1
  , MPI_INT
  , 0
  , COMM_TAG_WORK_RESULT
  , MPI_COMM_WORLD
  );

  // TODO: Write a better function for this.  JobResult will soon have more
  // than just an int.
  free(jobResult);
}
