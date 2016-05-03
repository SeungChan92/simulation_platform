#pragma once

#include <time.h>

struct Job
{
    int client_no;
    int job_no;
    int pid;
    double elapsed_time;
    char pstatus;
};