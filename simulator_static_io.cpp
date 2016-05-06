#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main()
{
    srand(clock());
    int memory_size = 1;
    int numberOf_loop = 270000; //support elapsed time to about 1.5
    
    cout << "It's a static simulator." << endl;
    cout << "memory_size : more than " << memory_size << " bytes" << endl;
    cout << "numberOf_loop : " << numberOf_loop << endl;    
    
    void* memory = malloc(memory_size);
    
    for(int i=0 ;i<numberOf_loop; i++)
    {
        cout << "test";
    }
    
    cout << "end" << endl;
    
    return 0;
}