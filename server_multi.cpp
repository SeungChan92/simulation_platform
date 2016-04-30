#include "header/SP_Server.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    int port_no = atoi(argv[1]);
    pid_t pid;
    SP_Server SP_Server(port_no);

    while(true)
    {
        SP_Server.acceptClient();
        SP_Server.classifyRequest();  
        pid = SP_Server.myFork();
        
        if(pid == 0) break;
    }
    
    //cout << "--end of program-- pid : " << pid << endl << endl;
    return 0;
}
