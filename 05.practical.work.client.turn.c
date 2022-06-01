#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char const* argv[])
{
    struct sockaddr_in saddr;
    struct hostent *h;
    int sockfd,var,client_fd;

    if(argc != 2)
    {
        printf("Usage: %s hostname\n", argv[0]);
        return 1;
    
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket");
        return 1;
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8784);
    h = gethostbyname(argv[1]);
    if(h == NULL)
    {
        printf("Unknown host\n");
        return 1;
    }
    memcpy(&saddr.sin_addr, h->h_addr, h->h_length);
    if(connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        printf("Cannot connect\n");
        return 1;
    }
    printf("Connected to %s\n", argv[1]);
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
        if(recv(sockfd, buf, sizeof(buf), 0) < 0)
        {
            perror("recv");
            return 1;
        }
        printf("%s", buf);
    }
    close(sockfd);
    return 0;
}