#include <string>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

class SP_Client {
private:
    int server_sockfd, port_no, connect_state, job_no;
    struct sockaddr_in serv_addr;
    string fileToSend, simulator;
    hostent* server;

public:
    SP_Client(hostent* server, int port_no, string fileToSend);

    void error(const char *msg);
    void setServ_addr();
    void connect_toServer();
    void checkConnect();
    void sendSimulator();
    void readSimulator();
    void printJobInfo();
    void requestJobInfo();
};