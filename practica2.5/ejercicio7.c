#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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

    rc = connect(sd, res->ai_addr, res->ai_addrlen);
    if(rc == -1){
        perror("Error bind()");
        exit(1);
    }

    while(1){
        int bytes = read(0, buf, sizeof(buf));

        if(buf[0] == 'Q'){
            if(close(sd) == -1){
                perror("Error close()");
            }

            exit(0);
        }

        if(send(sd, buf, bytes, 0) == -1){
            perror("Error send()");
        }

        if(recv(sd, buf, bytes, 0) == -1){
            perror("Error recv()");
        }

        buf[bytes] = '\0';
        printf("%s\n", buf);
    }

    if(close(sd) == -1){
        perror("Error close()");
    }

    return 0;
}