#include "job.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

JobList *buildJobList(char *dataDir) {
  DIR *d;
  struct dirent *dir;
  int count = 0;
  int i = 0;
  JobList *jobList = NULL;
  Job **jobs = NULL;

  d = opendir(dataDir);

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_name[0] != '.') ++count;
    }

    jobs = (Job **)calloc(count, sizeof(Job *));

    rewinddir(d);

    while ((dir = readdir(d)) != NULL) {
      if (dir->d_name[0] != '.') {
        jobs[i] = initJob(dir->d_name);
      }
    }

    closedir(d);

    jobList = initJobList(jobs, count);
  } else {
    fprintf(stderr, "no such directory: '%s'", dataDir);
  }

  return jobList;
}

JobList *initJobList(Job **jobs, int length) {
  JobList *jobList = (JobList *)calloc(1, sizeof(JobList));

  jobList->jobs = jobs;
  jobList->length = length;

  return jobList;
}

JobList *freeJobList(JobList *jobList) {
  int i = 0;  

  for (i = 0; i < jobList->length; ++i) {
    jobList->jobs[i] = freeJob(jobList->jobs[i]);
  }

  return 0;
}

Job *initJob(char *filename) {
  Job* job = (Job *)calloc(1, sizeof(Job));
  int filenameLengh = strlen(filename);

  memcpy(job->filename, filename, filenameLengh);
  job->assignedWorker = 0;

  return job;
}

Job *freeJob(Job *job) {
  free(job);

  return 0;
}

