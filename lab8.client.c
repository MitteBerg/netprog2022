#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>
#include<unistd.h>
#include<errno.h>
#include <fcntl.h>
#include <poll.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in saddr;
    struct hostent *h;
    struct in_addr *address;
    int sockfd,clientfd;
    unsigned short port = 8784;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Error creating socket\n");
        return 1;
    }
    char name[255];
    if (argc > 1){
        strcpy(name, argv[1]);
    }
    else{
        printf("Enter a name: ");
        scanf("%s", name);
        fflush(stdin);
    }
    h = gethostbyname(name);

    if (h == NULL){
        printf("Unknown host !!!\n");
        return 0;
    }
    printf("Hostname: %s\n", name); 
    
    int i=0;
    while(1){
        if (h->h_addr_list[i]==NULL){
            break;
        }
        else{
            address = (struct in_addr *)(h->h_addr_list[i]);
            printf("%s has address %s\n",name, inet_ntoa(*address)); 
        }
        i++;
    }
    
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;//ipv4
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);
    
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0){
        printf("Cannot connect\n");
        return 1;
    }
    printf("Successfully connected to Server.\n");
    
    
    int setsockopt(int socket, int level,
    int option_name,
    const void *option_value, socklen_t option_len);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    


    int fl = fcntl(sockfd, F_GETFL, 0);
    fl |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, fl | O_NONBLOCK);

    char clientms[1234], svms[1234];
    int shutdown(int socket, int how);
    while(1)
    {
        printf("Enter a command: ");
        fgets(clientms, 1234, stdin);
        if (strcmp(clientms, "/quit") == 0){
            shutdown(sockfd, SHUT_WR);
            printf("Disconnected from Server.\n");
            break;
        }
        if(send(sockfd, clientms, strlen(clientms), 0) < 0)
        {
            perror("send");
            return 1;
        }
        else
        {
            do{
                fgets(svms, 1000, stdin);
                send(clientfd, clientms, strlen(clientms) + 1, 0);
               } 
                while (svms[strlen(svms) - 1] != '\n');
        }
        if(recv(sockfd, clientms, sizeof(clientms), 0) < 0)
        {
            perror("recv");
            return 1;
        }
        else{
            do{
                recv(clientfd, clientms, sizeof(svms), 0);
                printf("%s", svms);
            } while (svms[strlen(svms) - 1] != '\n');
        }

        printf("Message to server:%s ", clientms);
 
        }
    

    return 0;
}