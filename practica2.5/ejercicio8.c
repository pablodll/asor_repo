#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define NI_MAXHOST 1025
#define NI_MAXSERV 32

#define N_PROC 3

int main(int argc, char *argv[]){

    char buf[100];

    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

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

    rc = listen(sd, 5);
    if(rc == -1){
        perror("Error listen");
    }

    while(1){

        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        struct sockaddr_storage client_addr;
        socklen_t client_len = sizeof(struct sockaddr_storage);

        int client_sd = accept(sd, (struct sockaddr *) &client_addr, &client_len);
        if(client_sd == -1){
            perror("Error accept()");
        }

        rc = getnameinfo((struct sockaddr *) &client_addr, client_len, 
        host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

        if(rc != 0){
            perror("Error getnameinfo");
        }

        printf("Conexion desde %s\n", host); 

        pid_t pid = fork();

        if(pid == 0){ // Hijo (gestion de recv y send)
            int bytes;
            while(bytes = recv(client_sd, buf, 90, 0)){
                if(bytes == -1){
                    perror("Error recv()");
                }

                buf[bytes]='\0';

                if(send(client_sd, buf, bytes, 0) == -1){
                    perror("Error send()");
                }
            }

            printf("Conexion terminada\n");
            exit(0);
        }
        else{ // Padre (cierra socket cliente)
            if(close(client_sd) == -1){
                perror("Error close()");
            }
        }

    }

    if(close(sd) == -1){
        perror("Error close()");
    }

    return 0;
}