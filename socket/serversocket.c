#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

#define buffersize 1024


void sig_fork(int signo) {
    int stat;
    waitpid(0, &stat, WNOHANG);
    return;
}

int main(){
    signal(SIGCHLD, sig_fork); 

    struct timeval timeout;
    timeout.tv_sec = 5; // sec
    timeout.tv_usec = 0; // ms


    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  
    serv_addr.sin_port = htons(5566);  
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(serv_sock, 20);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    while (1) {
      int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
      // set recv and send timeout
      if( setsockopt (clnt_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0 )
        printf( "setsockopt fail\n" );
      if( setsockopt (clnt_sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0 )
        printf( "setsockopt fail\n" ) ;
      
      int pid = fork();
      if (pid == -1) {
        printf( "ERROR pid\n" );
      } 
       
      else if (pid == 0) {
        printf("%d\n", getpid()) ;
        char *buffer = (char*) calloc(buffersize, sizeof(char));
        recv(clnt_sock, buffer, buffersize, 0) ;
        printf("Server receive:%s\n", buffer) ;
        int total = (int)(atoi(buffer)*atoi(buffer)) ;
        printf("Server return num^2:%d\n", total) ;
        char *returnvalue = (char*) calloc(buffersize, sizeof(char));
        sprintf( returnvalue, "result:%d", total ) ;
        send(clnt_sock, returnvalue, buffersize, 0) ;
        close(clnt_sock) ;
        close(serv_sock) ;
        return 0 ;
      } 
      else {
        close(clnt_sock);
      }

    }    
       
    close(serv_sock);
    return 0;
}
