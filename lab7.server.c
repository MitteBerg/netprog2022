#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    int sockfd, clen, client_fd;
    struct sockaddr_in saddr, caddr;//server addr, client addr 
    unsigned short port = 8784;

    
    if ((sockfd =  socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        return 1;
    }

    
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    
    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0){
        printf("Error binding\n");  
        return 1;
    }
    
    if (listen(sockfd, 5) < 0){
        printf("Error listening\n");  
        return 1;
    }
     
    clen = sizeof(caddr);
    if ((client_fd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error accepting connection\n"); 
        return 1;
    }
    printf("Client is connected.\n");

    char clientms[1234], svms[1234];
    int shutdown(int socket, int how);
    while(1)
    {
        printf("Enter a command: ");
        fgets(svms, 1234, stdin);
        if (strcmp(clientms, "/dc") == 0) {
            printf("Client disconnected.\n");
            shutdown(client_fd, SHUT_RDWR);
            close(client_fd);
            break;
        }
        if(send(sockfd, svms, strlen(svms), 0) < 0)
        {
            perror("send");
            return 1;
        }
        else
        {
          do{
                fgets(clientms, 1000, stdin);
                send(client_fd, svms, strlen(svms) + 1, 0);
            } while (clientms[strlen(clientms) - 1] != '\n');
        if(recv(sockfd, svms, sizeof(svms), 0) < 0)
        {
            perror("recv");
            return 1;
        }
        else{
          do{
                recv(client_fd, clientms, sizeof(clientms), 0);
                printf("%s", clientms);
            } while (svms[strlen(clientms) - 1] != '\n');
        }

        printf("Message to client:%s ", svms);
 
        }
    close(sockfd)
    return 0;
}

    

    
}
