#include "JobManager.h"

#include <iostream>
#include <string>

using namespace std;

int JobManager::count;
vector<Job> JobManager::jobs;

void JobManager::init()
{
    JobManager::count = 0;
}
void JobManager::addJob(int client_no, int pid)
{
    JobManager::count++;
    
    Job job = 
    {
        client_no,
        JobManager::count,
        pid        
    };
    JobManager::jobs.push_back(job);
}
void JobManager::printAll()
{
    for(int i=0;i<JobManager::count;i++)
    {
        cout << "client_no : " <<  JobManager::jobs[i].client_no << endl;
        cout << "job_no : " <<  JobManager::jobs[i].job_no << endl;
        cout << "pid    : " << JobManager::jobs[i].pid << endl << endl;
    }
}
string JobManager::getJobInfo(int client_no)
{
    string job_info = "";
    
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].client_no == client_no)
        {
            job_info.append("job_no : ");
            job_info.append(to_string(JobManager::jobs[i].job_no));
            job_info.append("\npid : ");
            job_info.append(to_string(JobManager::jobs[i].pid));
            job_info.append("\n\n");
        }
    }
    
    return job_info;
}