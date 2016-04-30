#include "../header/SP_Client.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <string>

using namespace std;

SP_Client::SP_Client(hostent* server, int port_no, string fileToSend) {
    this->server = server;
    this->port_no = port_no;
    this->fileToSend = fileToSend;
    connect_state = -1;
    
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
    else
        cout << "connect success" << endl;
}
void SP_Client::sendSimulator()
{
    string header = "|F|";    
    write(server_sockfd, header.c_str(), 3);
    write(server_sockfd, simulator.c_str(), simulator.length());
    close(server_sockfd);
    /*    
    string end_signal = "IT'S THE FILE END";
    write(server_sockfd, end_signal.c_str(), 17);
   
    string buffer = "777777777 ";    
    write(server_sockfd, buffer.c_str(), 10);
    */
}
void SP_Client::readSimulator()
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
    
    cout << "printJobInfo() : start" << endl;
    
    requestJobInfo();
    read(server_sockfd,job_info,BUFFER_SIZE);
    cout << job_info << endl;
    
    cout << "printJobInfo() : end" << endl;
}
void SP_Client::requestJobInfo() {
    string header = "|S|00001";    
    write(server_sockfd, header.c_str(), 8);
    //close(server_sockfd);
}