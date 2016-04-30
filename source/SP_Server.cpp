#include "../header/SP_Server.h"

#include "../header/JobManager.h"

#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>

using namespace std;

SP_Server::SP_Server(int port_no)
{
    this->port_no = port_no;
    file_name = "";
    
    JobManager::init();
    openSocket();
}

void SP_Server::openSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setServ_addr();
    bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr));
    listen(sockfd, SP_Server::WAITING_QUEUE_SIZE);
    clilen = sizeof(cli_addr);    
}
void SP_Server::setServ_addr() {
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_no);
}
void SP_Server::acceptClient() {
    client_sockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);    
}
void SP_Server::receiveFile() {
    int BUFFER_SIZE = 100;
    
    char buffer[BUFFER_SIZE+1];

    memset(buffer, 0, sizeof buffer);
    while(read(client_sockfd,buffer,BUFFER_SIZE))
    {
        file.append(buffer, BUFFER_SIZE);
        memset(buffer, 0, sizeof buffer);
        
        /*
        read(client_sockfd,buffer,BUFFER_SIZE);
        cout << "buffer : " << buffer << endl;
        
        int buffer_str_length = strlen(buffer);
        cout << "buffer_str_length : " << buffer_str_length << endl; 
        
        cout << endl;
        */
    }
    
    close(client_sockfd);
}
void SP_Server::saveFile() {
    
    ofstream os(file_name, ios::out);
    os << file;
    os.close();
    
    //cout << file << endl;
}
void SP_Server::chmodFile() {
    chmod(file_name.c_str(), S_IRWXU|S_IRWXG|S_IRWXO);
}
void SP_Server::executeFile() { 
    string file_path = "./";
    
    file_path.append(file_name);
    int flag = execl(file_path.c_str(), file_path.c_str(), NULL);
    if(flag == -1)
    {
        cout << "execl() : error" << endl;
        cout << "file_name : " << file_name << endl;
        cout << "file_path : " << file_path << endl;
    }
}
int SP_Server::myFork() {
    pid_t pid;
    int job_no;

    cout << endl << "fork()" << endl;
    pid = fork();
    if (pid == 0)
    {
        // child process
        if(request == 'F')
        {
            receiveFile();
            setFile_name(JobManager::getCount());
            saveFile();
            chmodFile();
            executeFile();
        }
        else if(request == 'S')
        {
            sendJobInfo(extractJobNo());
        }
        else
            cout << "He want something we don't know." << endl;
        
        cout << endl << "-------------- mission complete -----------------" << endl;        
    }
    else if (pid > 0)
    {
        // parent process
        if(request == 'F')
        {
            job_no = JobManager::addJob(SP_Server::CLIENT_NO, pid);
            acceptClient();
            alertJobNo(job_no);
        }
    }
    else
    {
        // fork failed
        cout << "fork() failed!\n";
    }
    
    return pid;
}
void SP_Server::classifyRequest() {
    const char* SIGNAL_FILE_SEND = "|F|";
    const char* SIGNAL_STATE = "|S|";
    
    int BUFFER_SIZE = 3;
    char header[BUFFER_SIZE+1];

    memset(header, 0, sizeof header);
    read(client_sockfd,header,BUFFER_SIZE);
    cout << endl << "Header : " << header << endl;
    
    if(strcmp(header, SIGNAL_FILE_SEND) == 0)
    {
        cout << "He want to send file." << endl;
        request = 'F';
        JobManager::increaseCount();
    }
    else if(strcmp(header, SIGNAL_STATE) == 0)
    {
        cout << "He want to check his job." << endl;
        request = 'S';
    }
}
int SP_Server::extractJobNo() {
    int job_no = -1;
    int BUFFER_SIZE = 10;
    char job_no_str[BUFFER_SIZE+1];

    memset(job_no_str, 0, BUFFER_SIZE+1);
    read(client_sockfd,job_no_str,BUFFER_SIZE);    
    job_no = atoi(job_no_str);
    
    return job_no;
}
void SP_Server::sendJobInfo(int job_no) {
    string job_info = JobManager::getJobInfo(job_no);
    write(client_sockfd, job_info.c_str(), job_info.length());
}
void SP_Server::alertJobNo(int job_no) {
    string job_no_str = to_string(job_no);
    write(client_sockfd, job_no_str.c_str(), job_no_str.length());
}
void SP_Server::setFile_name(int job_no) {
    string file_name = "simulator_";
    file_name.append(to_string(job_no));
    file_name.append(".out");
    
    this->file_name = file_name;
}