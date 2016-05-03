#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(clock());
    int memory_size = rand();
    int numberOf_loop = rand();
    
    cout << "It's a dynamic simulator." << endl;
    cout << "memory_size : more than " << memory_size << " bytes" << endl;
    cout << "numberOf_loop : " << numberOf_loop << endl;
    
    void* memory = malloc(memory_size);
    
    for(int i=0 ;i<numberOf_loop; i++)
    {
        1*1;
    }
    
    cout << "end" << endl;
    
    return 0;
}