#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include<stdlib.h>

int main(int argc, char * argv[])
{
    struct sockaddr_in saddr;
    struct hostent *h;
    int sockfd,var,client_fd;
    unsigned short port = 8784;
    char clientms[1000], svms[1000];


    if(argc != 2)
    {
        printf("Usage: %s hostname\n", argv[0]);
        return 1;
    
    }
    
    
    
    
    
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("error creating socket");
        return 1;


    char name[255];
    if (argc > 1){
        strcpy(name, argv[1]);
    }
    else{
        printf("Enter a name: ");
        scanf("%s", name);
        fflush(stdin);
    }
    
    
    h = gethostbyname(argv[1]);

    if(h == NULL)
    {
        printf("Unknown host\n");
        return 0;

    }
    printf("Hostname: %s\n", name); 



    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy(&saddr.sin_addr, h->h_addr, h->h_length);
    saddr.sin_port = htons(port);
    
    if(connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        printf("Cannot connect\n");
        return 1;
    }
    printf("Connected successfully");
    char buf[1024];
    while(1)
    {
        printf("Enter a command: ");
        fgets(buf, sizeof(buf), stdin);
        if(strncmp(buf, "exit", 4) == 0)
        {
            break;
        }
        if(send(sockfd, buf, strlen(buf), 0) < 0)
        {
            perror("send");
            return 1;
        }
        else{
            do{
                fgets(svms, 1000, stdin);
                send(client_fd, svms, strlen(svms) + 1, 0);
                } while (svms[strlen(svms) - 1] != '\n');
        if(recv(sockfd, buf, sizeof(buf), 0) < 0)
        {
            perror("recv");
            return 1;
        }
        else{
            do{
                recv(client_fd, clientms, sizeof(clientms), 0);
                printf("%s", clientms);
            } while (clientms[strlen(clientms) - 1] != '\n');
        }

        printf("Message to server: ");
        
    }
    close(sockfd);
    return 0;
}
}
}