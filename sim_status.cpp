#include "header/SP_Client.h"

#include <stdlib.h>
#include <netdb.h>

using namespace std;

int main(int argc, char *argv[])
{
    struct hostent* server = gethostbyname(argv[1]);
    int port_no = atoi(argv[2]);
    int job_no = atoi(argv[3]);
    
    SP_Client sp_client(server, port_no);
    
    sp_client.connect_toServer();
    sp_client.checkConnect();
    sp_client.requestJobInfo(job_no);
    sp_client.printJobInfo();

    return 0;
}