#ifndef JOB_H
#define JOB_H

#include "util.h"

typedef struct {
  int result; // TODO: Make this something meaningful
} JobResult;

typedef struct {
  char filename[MAX_FILENAME_LENGTH];
  JobResult result;
} Job;

typedef struct {
  Job **jobs;
  int length;
} JobList;

// Reads the dataDir to get all the files we need to process and returns
// a JobList.
JobList *buildJobList(char *dataDir);

JobList *initJobList(Job **jobs, int length);

// Releases the memory used by a job list;
JobList *freeJobList(JobList *jobList);

// Sort of like a constructor, but we're not sucky OOP here.
Job *initJob(char *filename, char *location);

// Releases the memory for a single job.
Job *freeJob(Job *job);

#endif
