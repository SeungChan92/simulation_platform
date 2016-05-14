#include <string>
#include <netinet/in.h>
#include <sys/time.h>

using namespace std;

class SP_Server {
private:
    const static int WAITING_QUEUE_SIZE = 5;
    const static int CLIENT_NO = 1;

    int sockfd, port_no, job_count, client_no;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    char request_type;
    bool isMain;
    pthread_t thread;
    
    void openSocket();
    void setServ_addr();
    
public:
    struct thread_argument
    {
        int client_sockfd, job_no;
    };

    SP_Server(int port_no);

    //bool getIsMain();

    void processRequest();
    int acceptClient();
    static string receiveFile(int client_sockfd);
    static void saveFile(string file, string file_name);
    static void chmodFile(string file_name);
    static void executeFile(string file_name);
    char classifyRequest(int client_sockfd);
    
    int extract_jobNo(int client_sockfd);
    static char extract_fileType(int client_sockfd);
    
    void sendJobInfo(int client_sockfd, int job_no);
    void send_pstatus(int client_sockfd, int job_no);
    void send_result(int client_sockfd, int job_no);
    
    void alertJobNo(int client_sockfd, int job_no);
    static string getFile_name(int job_no, char file_type);
    void startThread(int client_sockfd, int job_no);
    static void* thread_main(void*);
    void* buildThread_argument(int client_sockfd, int job_no);
    static int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y);
    //char check_pstatus(int pid);
    static double to_double(timeval tv);
    static double cal_elapsedTime(timeval tv_start);
    static void run_dlSim(string file_name);
};