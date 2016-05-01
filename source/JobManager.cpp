#include "../header/JobManager.h"

#include <iostream>
#include <string>

using namespace std;

int JobManager::count;
vector<Job> JobManager::jobs;

int JobManager::getCount() {
    return JobManager::count;
}

void JobManager::init()
{
    JobManager::count = 0;
}
int JobManager::addJob(int client_no)
{
    int job_no = ++(JobManager::count);
    
    Job job = 
    {
        client_no,
        job_no
    };
    JobManager::jobs.push_back(job);
    
    return job_no;
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
string JobManager::getJobInfo(int job_no)
{
    string job_info = "";
    
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].job_no == job_no)
        {
            job_info.append("client_no : ");
            job_info.append(to_string(JobManager::jobs[i].client_no));
            job_info.append("\njob_no : ");
            job_info.append(to_string(JobManager::jobs[i].job_no));
            job_info.append("\npid : ");
            job_info.append(to_string(JobManager::jobs[i].pid));
        }
    }
    
    return job_info;
}