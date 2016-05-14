#include "../header/JobManager.h"

#include <iostream>
#include <string>

using namespace std;

int JobManager::count;
vector<Job> JobManager::jobs;
double JobManager::average_elapsedTime;
double JobManager::max_elapsedTime;

int JobManager::getCount() {
    return JobManager::count;
}
int JobManager::get_pid(int job_no) {
    int pid = -1;
    
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].job_no == job_no)
        {
            pid = JobManager::jobs[i].pid;
            break;
        }
    }
    
    return pid;
}
int JobManager::get_jobNo(int index) {
    return JobManager::jobs[index].job_no;
}
char JobManager::get_pstatus(int job_no) {
    char pstatus = 0;
    
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].job_no == job_no)
        {
            pstatus = JobManager::jobs[i].pstatus;
            break;
        }
    }
    
    //cout << "JobManager::get_pstatus() - job_no : " << job_no << endl;
    //cout << "JobManager::get_pstatus() - pstatus : " << pstatus << endl;
    
    return pstatus;
}
double JobManager::get_elapsedTime(int job_no) {
    double elapsed_time = -1;
    
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].job_no == job_no)
        {
            elapsed_time = JobManager::jobs[i].elapsed_time;
            break;
        }
    }
    
    return elapsed_time;
}
double JobManager::get_averageElapsedTime() {
    return JobManager::average_elapsedTime;
}
double JobManager::get_maxElapsedTime() {
    return JobManager::max_elapsedTime;
}

void JobManager::init()
{
    JobManager::count = 0;
    JobManager::average_elapsedTime = -1;
}
int JobManager::addJob(int client_no) {
    int job_no = ++(JobManager::count);
    
    Job job = 
    {
        client_no,
        job_no,
        -1,
        -1,
        'R'
    };
    JobManager::jobs.push_back(job);
    
    return job_no;
}
void JobManager::add_job(int job_no) {
    JobManager::count++;
    Job job = 
    {
        -1,
        job_no,
        -1,
        -1,
        0
    };
    JobManager::jobs.push_back(job);
}
void JobManager::printAll()
{
    Job* job;
    
    for(int i=0;i<JobManager::count;i++)
    {
        job = &(JobManager::jobs[i]);
        
        cout << "client_no      : " <<  job->client_no << endl;
        cout << "job_no         : " <<  job->job_no << endl;
        cout << "pid            : " << job->pid << endl;
        cout << "elapsed_time   : " << job->elapsed_time << endl;
    }
}
string JobManager::getJobInfo(int job_no)
{
    string job_info = "";
    Job* job;
    
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].job_no == job_no)
        {
            job = &(JobManager::jobs[i]);
            
            job_info.append("client_no      : ");
            job_info.append(to_string(job->client_no));
            job_info.append("\njob_no         : ");
            job_info.append(to_string(job->job_no));
            job_info.append("\npid            : ");
            job_info.append(to_string(job->pid));
            job_info.append("\nelapsed_time   : ");
            job_info.append(to_string(job->elapsed_time));
            job_info.append(" s");
            
            break;
        }
    }
    
    return job_info;
}
void JobManager::update_elapsedTime(int job_no, double elapsed_time) {
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].job_no == job_no)
        {
            JobManager::jobs[i].elapsed_time = elapsed_time;
            break;
        }
    }
}
void JobManager::updatePid(int job_no, int pid) {
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].job_no == job_no)
        {
            JobManager::jobs[i].pid = pid;
            break;
        }
    }
}
void JobManager::update_pstatus(int job_no, char pstatus) {
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].job_no == job_no)
        {
            JobManager::jobs[i].pstatus = pstatus;
            break;
        }
    }
}

void JobManager::print_jobNos() {
    cout << endl << "job numbers : " << endl;
    for(int i=0; i<JobManager::count; i++)
    {
        cout << JobManager::jobs[i].job_no << '\t';
        if((i+1)%5 == 0)
            cout << endl;
    }
    cout << endl;
}
void JobManager::print_statuses() {
    cout << endl << "job number - process status : " << endl;
    for(int i=0; i<JobManager::count; i++)
    {
        cout << JobManager::jobs[i].job_no << "-" << JobManager::jobs[i].pstatus << '\t';
        if((i+1)%5 == 0)
            cout << endl;
    }
    cout << endl;
}
void JobManager::print_result() {
    cout << endl;
    
    cout << "job no :      ";
    for(int i=0; i<JobManager::count; i++)
    {
        cout << '\t' << JobManager::jobs[i].job_no;
    }
    cout << endl;
    
    cout << "elapsed time :";
    for(int i=0; i<JobManager::count; i++)
    {
        cout << '\t' << JobManager::jobs[i].elapsed_time;
    }
    cout << endl;
    
    cout << endl;
    cal_averageElapsedTime();
    cout << "average elapsed time : " << get_averageElapsedTime() << endl;
    cal_maxElapsedTime();
    cout << "max elapsed time : " << get_maxElapsedTime() << endl;
    
    cout << endl;
}


void JobManager::process_result(int job_no, char *result) {
    double elapsed_time = -1;
    
    elapsed_time = atof(result);
    update_elapsedTime(job_no, elapsed_time);
}
void JobManager::cal_averageElapsedTime() {
    double average_elapsedTime = 0;
    
    for(int i=0; i<JobManager::count; i++)
    {
        average_elapsedTime += JobManager::jobs[i].elapsed_time;
    }
    average_elapsedTime /= JobManager::count;
    
    JobManager::average_elapsedTime = average_elapsedTime;
}
void JobManager::cal_maxElapsedTime() {
    double max_elapsedTime = -1;
    
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].elapsed_time > max_elapsedTime)
        {
            max_elapsedTime = JobManager::jobs[i].elapsed_time;
        }
    }
    
    JobManager::max_elapsedTime = max_elapsedTime;
}

bool JobManager::all_is_over() {
    bool all_is_over = true;
    
    for(int i=0; i<JobManager::count; i++)
    {
        if(JobManager::jobs[i].pstatus != 'E')
        {
            all_is_over = false;
            break;
        }
    }
    
    return all_is_over;
}