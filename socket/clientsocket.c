#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define buffersize 1024

int main(int argc, char *argv[]){
 
    int sock = socket(AF_INET, SOCK_STREAM, 0);
  
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  
    serv_addr.sin_port = htons(5566); 
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   
    char *message = (char*) calloc(strlen(argv[1])+1, sizeof(char)) ;
    strcpy(message, argv[1]) ;
    send(sock, message, strlen(message)+1, 0) ;

    char *buffer = (char*) calloc(buffersize, sizeof(char)) ;
    read(sock, buffer, buffersize);
    printf("result form server: %s\n", buffer);

    free(message);
    free(buffer);
    close(sock);
    return 0;
}
