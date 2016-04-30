#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(clock());
    int memory_size = rand();
    
    cout << "It's simulator." << endl;
    
    cout << "memory_size : " << memory_size << endl;
    void* memory = malloc(memory_size);
    
    cout << endl;
    
    return 0;
}