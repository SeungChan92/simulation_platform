#include "PlatformServer.h"

#include <stdlib.h>

void error(const char *msg);

int main(int argc, char *argv[])
{
    int port_no = atoi(argv[1]);
    pid_t pid;
    PlatformServer platformServer(port_no);

    while(true)
    {
        platformServer.acceptClient();
        platformServer.classifyRequest();  
        pid = platformServer.myFork();
        
        if(pid == 0) break;
    }
    
    //cout << "--end of program-- pid : " << pid << endl << endl;
    return 0;
}