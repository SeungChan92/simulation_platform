#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(clock());
    int memory_size = rand();
    int numberOf_loop = rand();
    
    cout << "It's simulator." << endl;
    
    cout << "memory_size : " << memory_size << endl;
    void* memory = malloc(memory_size);
    
    for(int i=0 ;i<numberOf_loop; i++)
    {
        1*1;
    }
    
    cout << "end" << endl;
    
    return 0;
}