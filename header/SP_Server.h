#include <string>
#include <netinet/in.h>

using namespace std;

class SP_Server {
private:
    const static int WAITING_QUEUE_SIZE = 5;
    const static int CLIENT_NO = 1;

    int sockfd, port_no, client_sockfd, job_count, client_no;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    string file, file_name;
    char request_type;
    bool isMain;
    
    void openSocket();
    void setServ_addr();
    
public:
    SP_Server(int port_no);

    bool getIsMain();

    void processRequest();
    void acceptClient();
    void receiveFile();
    void saveFile();
    void chmodFile();
    void executeFile();
    void classifyRequest();
    int extractJobNo();
    void sendJobInfo(int job_no);
    void alertJobNo(int job_no);
    void setFile_name(int job_no);
};