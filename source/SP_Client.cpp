#include "../header/SP_Client.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <string>

using namespace std;

SP_Client::SP_Client(hostent* server, int port_no) {
    this->server = server;
    this->port_no = port_no;
    connect_state = -1;
    file_type = 0;
    
    setServ_addr();
}

void SP_Client::error(const char *msg)
{
    perror(msg);
    exit(1);
}
void SP_Client::setServ_addr()
{
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port_no);
}
void SP_Client::connect_toServer() {
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect_state = connect(server_sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));    
}
void SP_Client::checkConnect()
{
    if (connect_state < 0) 
        error("ERROR connecting");
    /*
    else
        cout << "connect success" << endl;
    */
}
void SP_Client::sendSimulator()
{
    string header = "|F|";
    
    header.append(&file_type, 1);
    
    write(server_sockfd, header.c_str(), 4);
    write(server_sockfd, simulator.c_str(), simulator.length());
    close(server_sockfd);
}
void SP_Client::check_fileType(string fileToSend) {
    string classifier = fileToSend.substr(fileToSend.length()-1, 1);
    
    if(classifier.compare("t") == 0) //.out
    {
        file_type = 'O';
    }
    else if(classifier.compare("o") == 0) //.so
    {
        file_type = 'S';
    }    
}
void SP_Client::readSimulator(string fileToSend)
{
    string line;
    
    ifstream is(fileToSend.c_str());
    if (is.is_open())
    {
    while ( getline (is, line) )
    {
        simulator.append(line);
        simulator.append("\n");
    }
        is.close();
    }
}
void SP_Client::printJobInfo() {
    int BUFFER_SIZE = 100;
    char job_info[BUFFER_SIZE+1];
    memset(job_info, 0, BUFFER_SIZE+1);
    
    read(server_sockfd,job_info,BUFFER_SIZE);
    cout << endl << job_info << endl << endl;
}
void SP_Client::requestJobInfo(int job_no) {
    string header = makeHeader("|I|", job_no);
    write(server_sockfd, header.c_str(), 13);
}
void SP_Client::request_result(int job_no) {
    string header = makeHeader("|R|", job_no);
    write(server_sockfd, header.c_str(), 13);
}
int SP_Client::receiveJobNo() {
    int BUFFER_SIZE = 20;
    char job_no_str[BUFFER_SIZE+1];
    memset(job_no_str, 0, BUFFER_SIZE+1);
    
    read(server_sockfd,job_no_str,BUFFER_SIZE);
    job_no = atoi(job_no_str);
    
    return job_no;
}
char* SP_Client::receive_result() {
    int BUFFER_SIZE = 20;
    char *result = new char[BUFFER_SIZE+1];
    
    memset(result, 0, BUFFER_SIZE+1);
    read(server_sockfd, result, BUFFER_SIZE);
    
    //cout << "receive_result() - result : " << result << endl;
    return result;
}

void SP_Client::printJobNo() {
    cout << endl << "job_no : " << job_no << endl << endl;
}
string SP_Client::makeHeader(string request_type, int job_no) {
    string job_no_str = to_string(job_no);
    int lengthOf_jobNo = job_no_str.length();
    string zeros = "";
    string header = request_type;
    string zero = "0";  
    
    for(int i=0; i<10-lengthOf_jobNo; i++)
    {
        zeros.append(zero.c_str());
    }
    header.append(zeros).append(job_no_str);
    
    //cout << endl << "header : " << header << endl << endl;
    
    return header;
}
char SP_Client::check_status(int job_no) {
    int BUFFER_SIZE = 2;
    char pstatus[BUFFER_SIZE+1];
    string header = makeHeader("|S|", job_no);
    
    write(server_sockfd, header.c_str(), 13);
    
    memset(pstatus, 0, BUFFER_SIZE+1);
    read(server_sockfd, pstatus, BUFFER_SIZE);
    
    return pstatus[0];
}

void SP_Client::close_socket() {
    close(server_sockfd);
}
