#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(clock());
    int memory_size = 1; //rand();
    int numberOf_loop = rand();
    
    printf("It's a dynamic simulator.\n");
    //printf("memory_size : more than %d bytes\n", memory_size);
    //printf("numberOf_loop : %d\n", numberOf_loop);
    
    void* memory = malloc(memory_size);
    
    int i=0;
    for(i; i<numberOf_loop; i++)
    {
        1*1;
    }
    
    printf("end\n\n");
    
    return 0;
}
