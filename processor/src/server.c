#include "server.h"

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "job.h"
#include "util.h"

typedef struct {
  int nextJobToDispatch;
  int completedWorkersCount;
  JobList *jobList;
  Job **workerToJobMap;
  int worldRank;
} Server;

void dispatchJob(Server *server, int workerRank);
void receiveResult(Server *server, int workerRank);
void releaseServerContents(Server *server);
void terminateWorker(Server *server, int workerRank);

// JobResult
//
// Anyway, once that is decided, I need to actually send the file names to the worker.
// Then the worker needs to send some result back
void runServer(Node *node) {
  Server server; // Our server's state

  int placeholder = 0; // We use this as a placeholder for our MPI comms
  MPI_Status status; // Another placeholder for dealing with MPI calls

  //greet(node);

  // Init server state.  This could be pulled into a different function.
  server.nextJobToDispatch = 0;
  server.completedWorkersCount = 0;
  server.jobList = buildJobList(DATA_DIR);
  server.workerToJobMap = (Job **)calloc(server.jobList->length, sizeof(Job *));
  server.worldRank = node->rank;

  //printf("(%d) Server has %d jobs\n", node->rank, server.jobList->length);

  // Begin the work of running
  while (server.completedWorkersCount < node->numProcessors - 1) {
    //printf("(%d) Server waiting for message\n", node->rank);

    MPI_Recv(
      &placeholder
    , 1
    , MPI_INT
    , MPI_ANY_SOURCE
    , MPI_ANY_TAG
    , MPI_COMM_WORLD
    , &status
    );
    
    switch (status.MPI_TAG) {
      case COMM_TAG_WORK_REQUEST:
        //printf("(%d) Server got work requeest from %d\n", node->rank, status.MPI_SOURCE);

        if (server.nextJobToDispatch < server.jobList->length) {
          dispatchJob(&server, status.MPI_SOURCE);
        } else {
          terminateWorker(&server, status.MPI_SOURCE);
          //printf("(%d) Server terminated worker %d. %d terminated.\n"
          //, node->rank
          //, status.MPI_SOURCE
          //, server.completedWorkersCount
          //);
        }
        break;
      case COMM_TAG_WORK_COMPLETE:
        //printf("(%d) Server got result request from %d\n", node->rank, status.MPI_SOURCE);

        // send the okay to proceeed
        receiveResult(&server, status.MPI_SOURCE);
        break;
      default:
        //printf("Received unknown tag: %d\n", status.MPI_TAG);
        break;
    }
  }

  releaseServerContents(&server);
  //printf("(%d) Server done\n", node->rank);
}

void releaseServerContents(Server *server) {
  server->jobList = freeJobList(server->jobList);
  
  free(server->workerToJobMap);
  server->workerToJobMap = NULL;
}

void dispatchJob(Server *server, int workerRank) {
  Job *job = server->jobList->jobs[server->nextJobToDispatch++];
  server->workerToJobMap[workerRank] = job;

  //printf(
  //  "(%d) Server dispatching job %s to %d. Next job will be %d.\n"
  //, server->worldRank
  //, job->filename
  //, workerRank
  //, server->nextJobToDispatch
  //);

  MPI_Send(
    job->filename
  , MAX_FILENAME_LENGTH
  , MPI_CHAR
  , workerRank
  , COMM_TAG_WORK_REQUEST
  , MPI_COMM_WORLD
  );
}

void receiveResult(Server *server, int workerRank) {
  int placeholder = 0;
  MPI_Status status;

  //printf(
  //  "(%d) Server sending go ahead to %d for job %s\n"
  //, server->worldRank
  //, workerRank
  //, server->workerToJobMap[workerRank]->filename
  //);
  // Tell the worker to go ahead and send the result
  MPI_Send(
    &placeholder
  , 1
  , MPI_INT
  , workerRank
  , COMM_TAG_PROCEED
  , MPI_COMM_WORLD
  );

  //printf(
  //  "(%d) Server receiving result from %d for job %s\n"
  //, server->worldRank
  //, workerRank
  //, server->workerToJobMap[workerRank]->filename
  //);

  // Receive the result
  MPI_Recv(
    &server->workerToJobMap[workerRank]->result.result
  , 1
  , MPI_INT
  , workerRank
  , COMM_TAG_WORK_RESULT
  , MPI_COMM_WORLD
  , &status
  );

  //printf(
  //  "%s:%d\n"
  //, server->workerToJobMap[workerRank]->filename
  //, server->workerToJobMap[workerRank]->result.result
  //);

  server->workerToJobMap[workerRank] = NULL;
}

void terminateWorker(Server *server, int workerRank) {
  char *terminateMessage = TERMINATION_MESSAGE;

  // Tell the worker to shut down
  MPI_Send(
    terminateMessage
  , strlen(TERMINATION_MESSAGE)
  , MPI_CHAR
  , workerRank
  , COMM_TAG_WORK_REQUEST
  , MPI_COMM_WORLD
  );

  server->completedWorkersCount++;
}
