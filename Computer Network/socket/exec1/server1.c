#include<stdio.h>
#include<string.h>  
#include<stdlib.h>   
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>   
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include<signal.h>
#include<sys/shm.h> 
#include<pthread.h> 
 
int main()
{
    int sock = dup(0);
    int read_size;
    char *message , client_message[2000];
    message = "Greetings! I am your connection handler\n";
    write(sock , message , strlen(message));
    message = "Now type something and i shall repeat what you type \n";
    write(sock , message , strlen(message));
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        write(1,client_message,strlen(client_message));
        write(sock , client_message , strlen(client_message));
    }
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    return 0;
}
