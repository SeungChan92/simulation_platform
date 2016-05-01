#include "../header/SP_Server.h"

#include "../header/JobManager.h"

#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <wait.h>

using namespace std;

SP_Server::SP_Server(int port_no)
{
    this->port_no = port_no;
    isMain = true;
    
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

bool SP_Server::getIsMain() {
    return isMain;
}

void SP_Server::processRequest() {
    //pid_t pid = -1;
    int job_no = -1, client_sockfd = -1;
    char request_type = 0;
    
    client_sockfd = acceptClient();
    request_type = classifyRequest(client_sockfd);
    if(request_type == 'F')
    {
        job_no = JobManager::addJob(SP_Server::CLIENT_NO);
        
        //pass job to new thread
        startThread(client_sockfd);
        cout << "-- main-thread : after start another --" << endl;

        client_sockfd = acceptClient();
        alertJobNo(client_sockfd, job_no);
        cout << endl << "-------------- mission complete : F - send job_no -----------------" << endl;
   
/*        
        cout << endl << "fork()" << endl;
        pid = fork();
        
        if(pid == 0) //child
        {
            isMain = false;
        }
        else if(pid > 0) //parent
        {
                     
        }
        else
        {
            cout << "fork() failed!\n";
        }
*/
    }
    else if(request_type == 'S') 
    {
        sendJobInfo(client_sockfd, extractJobNo(client_sockfd));
        cout << endl << "-------------- mission complete : S -----------------" << endl;
    }
    else
        cout << "He want something we don't know." << endl;
}
int SP_Server::acceptClient() {
    int client_sockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
                 
    return client_sockfd;
}
string SP_Server::receiveFile(int client_sockfd) {
    string file = "";
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
    
    return file;
}
void SP_Server::saveFile(string file, string file_name) {
    
    ofstream os(file_name, ios::out);
    os << file;
    os.close();
    
    //cout << file << endl;
}
void SP_Server::chmodFile(string file_name) {
    chmod(file_name.c_str(), S_IRWXU|S_IRWXG|S_IRWXO);
}
void SP_Server::executeFile(string file_name) { 
    int flag = execl(file_name.c_str(), file_name.c_str(), NULL);
    if(flag == -1)
    {
        cout << "execl() : error" << endl;
        cout << "file_name : " << file_name << endl;
    }
}
char SP_Server::classifyRequest(int client_sockfd) {
    const char* SIGNAL_FILE_SEND = "|F|";
    const char* SIGNAL_STATE = "|S|";
    char request_type = 0;
    
    int BUFFER_SIZE = 3;
    char header[BUFFER_SIZE+1];

    memset(header, 0, sizeof header);
    read(client_sockfd,header,BUFFER_SIZE);
    cout << endl << "Header : " << header << endl;
    
    if(strcmp(header, SIGNAL_FILE_SEND) == 0)
    {
        cout << "He want to send file." << endl;
        request_type = 'F';
    }
    else if(strcmp(header, SIGNAL_STATE) == 0)
    {
        cout << "He want to check his job." << endl;
        request_type = 'S';
    }
    
    return request_type;
}
int SP_Server::extractJobNo(int client_sockfd) {
    int job_no = -1;
    int BUFFER_SIZE = 10;
    char job_no_str[BUFFER_SIZE+1];

    memset(job_no_str, 0, BUFFER_SIZE+1);
    read(client_sockfd,job_no_str,BUFFER_SIZE);    
    job_no = atoi(job_no_str);
    
    return job_no;
}
void SP_Server::sendJobInfo(int client_sockfd, int job_no) {
    string job_info = JobManager::getJobInfo(job_no);
    write(client_sockfd, job_info.c_str(), job_info.length());
}
void SP_Server::alertJobNo(int client_sockfd, int job_no) {
    string job_no_str = to_string(job_no);
    write(client_sockfd, job_no_str.c_str(), job_no_str.length());
}
string SP_Server::getFile_name(int job_no) {
    string file_name = "simulator_";
    file_name.append(to_string(job_no));
    file_name.append(".out");
    
    return file_name;
}
void SP_Server::startThread(int client_sockfd) {
    void* argument = buildThread_argument(client_sockfd);
    pthread_create(&threads[0], NULL, &thread_main, argument);
}
void* SP_Server::thread_main(void* argument) {
    struct thread_argument* arg = (thread_argument*)argument;
    int client_sockfd = arg->client_sockfd, pid;
    string file = "", file_name = "";
    int* child_status = NULL;
    
    cout << "----- thread : start -----" << endl;
    
    file = receiveFile(client_sockfd);
    file_name = getFile_name(JobManager::getCount());
    saveFile(file, file_name);
    chmodFile(file_name);
    
    pid = fork();
    if(pid == 0) //child
    {
        executeFile(file_name);
    }
    else if(pid > 0) //parent
    {
        int ended_pid = waitpid(pid, child_status, 0);
        cout << "      child_pid : " << pid << endl;
        cout << "ended child_pid : " << ended_pid << endl;
        cout << endl << "-------------- mission complete : F - measure -----------------" << endl;
    
        cout << "----- thread : end -----" << endl;
        pthread_exit((void*)1);
    }
    else
    {
        cout << "fork() : fail" << endl;
    }
}
void* SP_Server::buildThread_argument(int client_sockfd) {
    struct thread_argument* thread_arg = new struct thread_argument;
    thread_arg->client_sockfd = client_sockfd;
    
    return (void*)thread_arg;
}
