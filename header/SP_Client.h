#include <string>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

class SP_Client {
private:
    int server_sockfd, port_no, connect_state, job_no;
    struct sockaddr_in serv_addr;
    string simulator;
    hostent* server;
    char file_type;

    string makeHeader(string request_type, int job_no);
    
public:
    SP_Client(hostent* server, int port_no);

    void error(const char *msg);
    void setServ_addr();
    void connect_toServer();
    void checkConnect();
    void sendSimulator();
    void check_fileType(string fileToSend);
    void readSimulator(string fileToSend);
    void printJobInfo();
    
    void requestJobInfo(int job_no);
    void request_result(int job_no);
    
    int receiveJobNo();
    char* receive_result();
    
    void printJobNo();
    char check_status(int job_no);
    
    void close_socket();
};