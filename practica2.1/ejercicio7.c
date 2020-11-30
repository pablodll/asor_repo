#include <stdio.h>
#include <unistd.h>

int main(){
    long link_max = pathconf("./", _PC_LINK_MAX);
    printf("Longitud maxima de argumentos: %d\n", link_max);
    
    long path_max = pathconf("./", _PC_PATH_MAX);
    printf("MNumero maximo de hijos: %d\n", path_max);

    long name_max = pathconf("./", _PC_NAME_MAX);
    printf("Numero maximo de ficheros abiertos: %d\n", name_max);
}