#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int WAITING_QUEUE_SIZE = 5;

int sockfd, portno, newsockfd, bit;
struct sockaddr_in serv_addr, cli_addr;
socklen_t clilen;

void error(const char *msg);
void setServ_addr();
void receiveBit();

int main(int argc, char *argv[])
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    portno = atoi(argv[1]);
    setServ_addr();
    bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr));
    listen(sockfd, WAITING_QUEUE_SIZE);
    
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
                 
    receiveBit();
    
    cout << "bit : " << bit << endl;
    
    return 0;
}

void setServ_addr()
{
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
}
void receiveBit()
{
    char buffer[1];
    bzero(buffer,1);
    bit = read(newsockfd,buffer,1);
}