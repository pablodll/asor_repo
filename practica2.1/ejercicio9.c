#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    printf("UID real: %d\n", getuid());
    printf("UID efectivo: %d\n", geteuid());
    
    return 0;
}