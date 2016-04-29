#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <string>

using namespace std;

int server_sockfd, portno, connect_state = -1, job_no;
struct sockaddr_in serv_addr;
struct hostent *server;
string simulator, fileToSend;

void error(const char *msg);
void setServ_addr();
void checkConnect();
void sendSimulator();
void readSimulator();
void writeSimulator();
void printJobInfo();
void requestJobInfo();

int main(int argc, char *argv[])
{
    server = gethostbyname(argv[1]);
    portno = atoi(argv[2]);
    fileToSend = argv[3];
 
    setServ_addr();   
    
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect_state = connect(server_sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    checkConnect();
    readSimulator();
    sendSimulator();
    
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);    
    connect_state = connect(server_sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    checkConnect();
    printJobInfo();
    //cout << "JobNo : " << job_no << endl;

    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
void setServ_addr()
{
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
}
void checkConnect()
{
    if (connect_state < 0) 
        error("ERROR connecting");
    else
        cout << "connect success" << endl;
}
void sendSimulator()
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
void readSimulator()
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
void printJobInfo() {
    int BUFFER_SIZE = 100;
    char job_info[BUFFER_SIZE+1];
    
    cout << "printJobInfo() : start" << endl;
    
    requestJobInfo();
    read(server_sockfd,job_info,BUFFER_SIZE);
    cout << job_info << endl;
    
    cout << "printJobInfo() : end" << endl;
}
void requestJobInfo() {
    string header = "|S|00001";    
    write(server_sockfd, header.c_str(), 8);
    //close(server_sockfd);
} 
/*
void writeSimulator()
{
    ofstream outsimulator("output.out", ios::out);
    outsimulator << simulator;
    outsimulator.close();
}
*/