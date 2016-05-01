#pragma once

#include <vector>
#include <string>
#include <sys/time.h>

#include "Job.h"

using namespace std;

class JobManager
{
private:
    //static JobManager jobManager();
    static vector<Job> jobs; // save pid
    static int count;
public:
    static int getCount();

    static void init();
    static int addJob(int client_no);
    static void printAll();
    static string getJobInfo(int job_no);
    static void updateElapsed_time(int job_no, timeval tv_elapsed);
    static void updatePid(int job_no, int pid);
};