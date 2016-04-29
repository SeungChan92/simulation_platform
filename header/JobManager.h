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
    static void init();
    static void addJob(int client_no, int pid);
    static void printAll();
    static string getJobInfo(int client_no);
};