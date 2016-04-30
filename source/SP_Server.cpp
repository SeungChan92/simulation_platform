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
        /*
        read(client_sockfd,buffer,BUFFER_SIZE);
        cout << "buffer : " << buffer << endl;
        
        int buffer_str_length = strlen(buffer);
        cout << "buffer_str_length : " << buffer_str_length << endl; 
        if(is_fileEnd(buffer, buffer_str_length))
        {
            file.append(buffer, buffer_str_length-17);
            break;
        }
        
        cout << endl;
        */
        
        file.append(buffer, BUFFER_SIZE);
        memset(buffer, 0, sizeof buffer);
    }
    
    close(client_sockfd);
}
void SP_Server::saveFile() {
    
    ofstream os("receivedFile.out", ios::out);
    os << file;
    os.close();
    
    //cout << file << endl;
}
void SP_Server::chmodFile() {
    chmod("receivedFile.out", S_IRWXU|S_IRWXG|S_IRWXO);
}
void SP_Server::executeFile() {    
    system("./receivedFile.out");
}
int SP_Server::myFork() {
    pid_t pid;

    cout << endl << "fork()" << endl;
    pid = fork();
    if (pid == 0)
    {
        // child process
        if(request == 'F')
        {
            receiveFile();
            saveFile();
            chmodFile();
            executeFile();
        }
        else if(request == 'S')
        {
            extractClientNo();
            cout << "client_no : " << client_no << endl;
            sendJobInfo(client_no);
        }
        else
            cout << "He want something not sending file." << endl;        
    }
    else if (pid > 0)
    {
        // parent process
        if(request == 'F')
        {
            JobManager::addJob(SP_Server::CLIENT_NO, pid);
            //JobManager::printAll();
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
    }
    else if(strcmp(header, SIGNAL_STATE) == 0)
    {
        cout << "He want to check his jobs." << endl;
        request = 'S';
    }
}
void SP_Server::extractClientNo() {
    int BUFFER_SIZE = 5;
    char clientNo[BUFFER_SIZE+1];

    memset(clientNo, 0, sizeof clientNo);
    read(client_sockfd,clientNo,BUFFER_SIZE);    
    client_no = atoi(clientNo);
}
void SP_Server::sendJobInfo(int client_no) {
    string job_info = JobManager::getJobInfo(client_no);
    write(client_sockfd, job_info.c_str(), job_info.length());
}
