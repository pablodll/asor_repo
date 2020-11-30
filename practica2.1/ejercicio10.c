#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(){
    printf("UID real: %d\n", getuid());
    printf("UID efectivo: %d\n", geteuid());

    struct passwd *info = getpwuid(geteuid());
    printf("Nombre usuario: %s\n", info->pw_name);
    printf("Descripcion usuario: %s\n", info->pw_name);
    printf("Directorio home: %s\n", info->pw_dir);
    
    return 1;
}