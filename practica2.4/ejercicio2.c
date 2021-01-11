#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

        int p_h[2];
        int h_p[2];

    if(pipe(p_h) == -1){
        perror("Error creating pipe p_h");
    }
    if(pipe(h_p) == -1){
        perror("Error creating pipe h_p");
    }

    pid_t pid = fork();

    if(pid == 0){ // HIJO
        if(close(p_h[1]) == -1 || close(h_p[0]) == -1){
            perror("Child close error");
        }
        
        int i = 0;
        while(i < 10){
            char s[100];

            if(read(p_h[0], s, sizeof(s)) == -1){ // Leer mensaje de padre
                perror("p_h read error");
            }
            printf("%s\n", s); // Escribir mensaje en stdout

            sleep(1);

            i++;

            if(i < 10){
                if(write(h_p[1], "l", 1) == -1){ // Escribir listo a padre
                    perror("h_p write error");
                }
            }
            else{
                if(write(h_p[1], "q", 1) == -1){ // Escribir fin a padre
                    perror("h_p write error");
                }
            }
        }

    }
    else if(pid > 0){ // PADRE
        if(close(p_h[0]) == -1 || close(h_p[1]) == -1){
            perror("Child close error");
        }

        char c[1] = "";

        while(1){
            char s[100];

            scanf("%s", s); // Leer mensaje de stdin
            if(write(p_h[1], s, sizeof(s)) == -1){ // Enviar mensaje a hijo
                perror("p_h write error");
            }
        

            if(read(h_p[0], c, 1) == -1){ // Leer mensaje de hijo
                perror("h_p read error");
            }

            if(c[0] == 'q'){
                break;
            }
        }

    }
    else{
        perror("Fork error");
    }

    return 0;
}