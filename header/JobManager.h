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
    static vector<Job> jobs;
    static int count;
public:
    static int getCount();
    static int get_pid(int job_no);
    static int get_jobNo(int index);
    static char get_pstatus(int job_no);

    static void init();
    static int addJob(int client_no);
    static void add_job(int job_no);
    static string getJobInfo(int job_no);
    static void updateElapsed_time(int job_no, timeval tv_elapsed);
    static void updatePid(int job_no, int pid);
    static void update_pstatus(int job_no, char pstatus);
    static void printAll();
    static void print_jobNos();
    static void print_statuses();
    
    static bool all_is_over();
};