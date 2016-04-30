#pragma once

#include <vector>
#include <string>

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
    static int addJob(int client_no, int pid);
    static void printAll();
    static string getJobInfo(int job_no);
    static void increaseCount();
};