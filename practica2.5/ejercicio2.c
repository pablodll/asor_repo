#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <locale.h>

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

    rc = bind(sd, res->ai_addr, res->ai_addrlen);

    if(rc == -1){
        perror("Error bind()");
        exit(1);
    }

    while(1){
        
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        struct sockaddr_storage client_addr;
        socklen_t client_len = sizeof(struct sockaddr_storage);

        int bytes = recvfrom(sd, buf, 90, 0, (struct sockaddr *) &client_addr, &client_len);

        if(bytes == -1){
            perror("Error recvfrom()");
        }

        buf[bytes]='\0';

        rc = getnameinfo((struct sockaddr *) &client_addr, client_len, 
                host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

        if(rc != 0){
            perror("Error getnameinfo");
        }

        printf("%d bytes de %s\n", bytes, host);
        
        if(time(&t) == (time_t)-1){
            perror("Error time");
        }
        else{
            localt = localtime(&t);
            if(localt == NULL){
                perror("Error localtime");
            }
        }

        switch (buf[0]){
            case 't':
                bytes = strftime(buf, sizeof(buf), "%I:%M:%S %p\n", localt);
                if(sendto(sd, buf, bytes, 0, (struct sockaddr *) &client_addr, client_len) == -1){
                    perror("Error sendto()");
                }
                break;

            case 'd':
                bytes = strftime(buf, sizeof(buf), "%F\n", localt);
                if(sendto(sd, buf, bytes, 0, (struct sockaddr *) &client_addr, client_len) == -1){
                    perror("Error sendto()");
                }
                break;

            case 'q':
                printf("Saliendo...\n");
                return 0;
                break;

            default:
                printf("Comando no soportado: %s", buf);
                break;
        }

    }

    return 0;
}