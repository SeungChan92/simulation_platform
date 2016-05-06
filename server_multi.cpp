#include "header/SP_Server.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    int port_no = atoi(argv[1]);
    SP_Server sp_server(port_no);

    while(true)
    {
        sp_server.processRequest();
        
        /*        
        if(!sp_server.getIsMain())
            break;
        */
    }
    
    //cout << "--end of process-- pid : " << pid << endl << endl;
    return 0;
}
