#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int sockfd, portno, connect_state;
struct sockaddr_in serv_addr;
struct hostent *server;

void error(const char *msg);
void setServ_addr();
void checkConnect();
void sendBit();

int main(int argc, char *argv[])
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    server = gethostbyname(argv[1]);
    portno = atoi(argv[2]);
    setServ_addr();
    connect_state = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

    checkConnect();
    sendBit();

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
void sendBit()
{
    char buffer[1] = {'1'};
    write(sockfd, buffer, 1);
}