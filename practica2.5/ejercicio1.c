#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

int main(int argc, char *argv[]){

    struct addrinfo *res, *rp;
    struct sockaddr *sa;
    socklen_t len;
    char hbuf[1025], sbuf[32];

    if(getaddrinfo(argv[1], NULL, NULL, &res) != 0){
        perror("Error getaddrinfo");
        exit(1);
    }

    for(rp = res; rp != NULL; rp = rp->ai_next){
        
        sa = rp->ai_addr;
        len = rp->ai_addrlen;  

        if(getnameinfo(sa, len, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST) == 0){
            printf("%s\t", hbuf); 
            printf("%d\t", rp->ai_family);
            printf("%d\n", rp->ai_socktype);
        }
        else{
            perror("Error getnameinfo");
        }
    }

    return 0;
}