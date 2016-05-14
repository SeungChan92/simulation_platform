#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    srand(clock());
    int memory_size = 1;
    int numberOf_loop = 270000; //support elapsed time to about 1.5
    
    printf("It's a static_io simulator.\n");
    printf("memory_size : more than %d bytes\n", memory_size);
    printf("numberOf_loop : %d\n", numberOf_loop);  
    
    void* memory = malloc(memory_size);
    
    int i=0;
    for(i; i<numberOf_loop; i++)
    {
        printf("test");
    }
    
    printf("end\n");
    
    return 0;
}