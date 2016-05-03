#include "header/JobManager.h"
#include "header/SP_Client.h"

#include <iostream>
#include <unistd.h>

using namespace std;

void askTo_user(string *server_str, int *port_no, string *filePath, int *numberOf_submit);

int main()
{
    struct hostent *server = NULL; //gethostbyname(argv[1]);
    int port_no = -1, numberOf_submit = -1, temp_int = -1, count = 0;
    string filePath = "", server_str = "", temp_str = "";
    char temp_char = 0, *temp_charPtr = NULL;
    
    askTo_user(&server_str, &port_no, &filePath, &numberOf_submit);
    server_str = "127.0.0.1";
    port_no = 40000;
    filePath = "/home/anseungchan/workspace/s_p/simulator_static.out";
    
    server = gethostbyname(server_str.c_str());
    
    //cout << endl << "*********** 1 ***********" << endl << endl;
    //cout << "server : " << server << endl;
    //cout << "port_no : " << port_no << endl;
    
    SP_Client sp_client(server, port_no);
    
    //cout << endl << "*********** 2 ***********" << endl << endl;
    
    sp_client.readSimulator(filePath);
    
    //cout << endl << "*********** 3 ***********" << endl << endl;
    
    for(int i=0; i<numberOf_submit; i++)
    {
        sp_client.connect_toServer();
        //sp_client.checkConnect();
        sp_client.sendSimulator();
        
        sp_client.connect_toServer();
        //sp_client.checkConnect();
        temp_int = sp_client.receiveJobNo();
        
        //cout << "job_no : " << temp_int << endl;
        
        JobManager::add_job(temp_int);
    }
    JobManager::print_jobNos();
    while(true)
    {
        sleep(2);
        cout << endl << "elapsed time : " << ++count * 2 << " sec";
        
        for(int i=0; i<numberOf_submit; i++)
        {
            temp_int = JobManager::get_jobNo(i);
            sp_client.connect_toServer();
            //sp_client.checkConnect();
            temp_char = sp_client.check_status(temp_int);
            
            //cout << endl << "pstatus : " << temp_char << endl << endl;
            
            JobManager::update_pstatus(temp_int, temp_char);
        }
        if(JobManager::all_is_over())
        {
            cout << endl << "every job is over" << endl;
            break;
        }
        else
        {
            JobManager::print_statuses();
        }
    }
    for(int i=0; i<numberOf_submit; i++)
    {
        temp_int = JobManager::get_jobNo(i);
        
        sp_client.connect_toServer();
        //sp_client.checkConnect();
        sp_client.request_result(temp_int);
        temp_charPtr = sp_client.receive_result();
        JobManager::process_result(temp_int, temp_charPtr);
    }
    JobManager::print_result();
    
    cout << endl;
    return 0;
}

void askTo_user(string *server_str, int *port_no, string *filePath, int *numberOf_submit) {
    cout << "server IP : ";
    cin >> *server_str;
    cout << "server port number : ";
    cin >> *port_no;
    cout << "file path : ";
    cin >> *filePath;
    cout << "number of submit : ";
    cin >> *numberOf_submit;
}