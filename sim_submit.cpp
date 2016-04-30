#include "header/SP_Client.h"

#include <stdlib.h>
#include <string>
#include <netdb.h>

using namespace std;

int main(int argc, char *argv[])
{
    struct hostent* server = gethostbyname(argv[1]);
    int port_no = atoi(argv[2]);
    string fileToSend = argv[3];
    
    SP_Client sp_client(server, port_no);
    
    sp_client.readSimulator(fileToSend);
    sp_client.connect_toServer();
    sp_client.checkConnect();
    sp_client.sendSimulator();
    
    sp_client.connect_toServer();
    sp_client.checkConnect();
    sp_client.receiveJobNo();
    sp_client.printJobNo();
    
    return 0;
}