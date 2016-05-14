#include "header/SP_Server.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    int port_no = atoi(argv[1]);
    int numberOf_threads = atoi(argv[2]);
    SP_Server sp_server(port_no, numberOf_threads);

    while(true)
    {
        sp_server.processRequest();
    }
    
    return 0;
}
