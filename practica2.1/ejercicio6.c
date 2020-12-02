#include <stdio.h>
#include <unistd.h>

int main(){
    long arg_max = sysconf(_SC_ARG_MAX);
    printf("Longitud maxima de argumentos: %d\n", arg_max);
    
    long child_max = sysconf(_SC_CHILD_MAX);
    printf("MNumero maximo de hijos: %d\n", child_max);

    long open_max = sysconf(_SC_OPEN_MAX);
    printf("Numero maximo de ficheros abiertos: %d\n", open_max);

    return 0;
}