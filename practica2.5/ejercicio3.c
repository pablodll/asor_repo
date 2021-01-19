#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <locale.h>

#include <errno.h>

extern int errno;

#define NI_MAXHOST 1025
#define NI_MAXSERV 32

int main(int argc, char *argv[]){

    char buf[100];

    struct tm *localt;
    time_t t;

    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

    if(rc != 0){
        perror("Error getaddrinfo()");
        exit(1);
    }

    int sd = socket(res->ai_family, res->ai_socktype, 0);
    
    if(sd == -1){
        perror("Error socket()");
        exit(1);
    }

    struct sockaddr_storage server_addr;
    socklen_t server_len = sizeof(struct sockaddr_storage);

    if(sendto(sd, argv[3], 2, 0, res->ai_addr, res->ai_addrlen) == -1){
        perror("Error sendto()");
    }

    int bytes = recvfrom(sd, buf, 90, 0, (struct sockaddr *) &argv, &server_len);

    if(bytes == -1){
        perror("Error recvfrom()");
    }
    
    buf[bytes]='\0';

    printf("%s\n%", buf);

    if(close(sd) == -1){
        perror("Error close()");
    }

    return 0;
}