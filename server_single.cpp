#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

#include <fstream>
#include <sys/stat.h>

#include "JobManager.h"

using namespace std;

int WAITING_QUEUE_SIZE = 5;
int CLIENT_NO = 1;

int sockfd, portno, client_sockfd, job_count, client_no;
struct sockaddr_in serv_addr, cli_addr;
socklen_t clilen;
string file = "";
pid_t pid;
char request;

void openSocket();
void acceptClient();
void error(const char *msg);
void setServ_addr();
void receiveFile();
void saveFile();
void chmodFile();
void executeFile();
void myFork();
void classifyRequest();
void extractClientNo();
void sendJobInfo(int client_no);
  
//bool is_fileEnd(char* buffer, int buffer_str_length);

int main(int argc, char *argv[])
{
    portno = atoi(argv[1]);
    
    JobManager::init();
    openSocket();
    
    while(true)
    {
        acceptClient();
        classifyRequest();  
        myFork();
        
        if(pid == 0) break;
    }
    
    //cout << "--end of program-- pid : " << pid << endl << endl;
    
    return 0;
}

void openSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setServ_addr();
    bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr));
    listen(sockfd, WAITING_QUEUE_SIZE);
    clilen = sizeof(cli_addr);    
}
void acceptClient() {
    client_sockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);    
}
void setServ_addr() {
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
}
void receiveFile() {
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
void saveFile() {
    
    ofstream os("receivedFile.out", ios::out);
    os << file;
    os.close();
    
    //cout << file << endl;
}
void chmodFile() {
    chmod("receivedFile.out", S_IRWXU|S_IRWXG|S_IRWXO);
}
void executeFile() {    
    system("./receivedFile.out");
}
void myFork() {

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
            JobManager::addJob(CLIENT_NO, pid);
            //JobManager::printAll();
        }
    }
    else
    {
        // fork failed
        cout << "fork() failed!\n";
    }   
}
void classifyRequest() {
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
void extractClientNo() {
    int BUFFER_SIZE = 5;
    char clientNo[BUFFER_SIZE+1];

    memset(clientNo, 0, sizeof clientNo);
    read(client_sockfd,clientNo,BUFFER_SIZE);    
    client_no = atoi(clientNo);
}
void sendJobInfo(int client_no) {
    string job_info = JobManager::getJobInfo(client_no);
    cout << "<job_info>" << endl;
    cout << job_info;
    write(client_sockfd, job_info.c_str(), job_info.length());
}
/*
bool is_fileEnd(char* buffer, int buffer_str_length) {
    const char* end_signal = "IT'S THE FILE END";
    
    if(buffer_str_length >= 17)
    {
        const char* buffer_end_17 = buffer+(buffer_str_length-17);
        cout << "buffer_end_17 : " << buffer_end_17 << endl;
        
        if(strcmp(buffer_end_17, end_signal) == 0)
            return true;
    }
    
    return false;
}
*/