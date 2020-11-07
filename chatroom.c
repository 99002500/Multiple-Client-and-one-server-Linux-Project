#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_CLIENTS 100
#define BUFFER_SZ 2048

static _Atomic unsigned int cli_count = 0;
static int uid = 10;


int main(int argc, char **argv)
{
    if(argc !=2)
    {
        printf("Usage %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    int option=1;
    int listenfd=0, connfd=0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    pthread_t tid;

    // Now we have to do settings for socket
 listenfd = socket(AF_INET, SOCK_STREAM, 0);
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = inet_addr(ip);
 serv_addr.sin_port = htons(port);

 // Now we do for signals which are basically system generated interrupts

 signal(SIGPIPE, SIG_IGN);
 if(setsockopt(listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&option, sizeof(option))<0)
{
    printf("ERROR: setsocketopt\n");
    return EXIT_FAILURE;
}
// Now we are going to bind the address

if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
{
 printf("ERROR: listen\n");   
}
    
 // listen
 if(listen(listenfd, 10)<0)
 {
     printf("Error: listen\n");
     return EXIT_FAILURE;
 }



}