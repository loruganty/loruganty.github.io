#include "csapp.h"
#include<stdio.h>
#include<string.h>  //strlen
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include<unistd.h>  //write

int main(int argc, char **argv)
{
int clientfd, port,sock_fd;
char *host, buf[MAXLINE];
FILE *image;
rio_t rio;
if (argc != 3) {
fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
exit(0);
}
host = argv[1];
port = atoi(argv[2]);
clientfd = Open_clientfd(host, port);
//Rio_readinitb(&rio, clientfd);
//while (Fgets(buf, MAXLINE, stdin) != NULL) {
//Rio_writen(clientfd, buf, strlen(buf));
//Rio_readlineb(&rio, buf, MAXLINE);
//Fputs(buf, stdout);
image = fopen("/home/lalitha/Downloads/EOS/LABS/tiny/Client/godzilla.jpg", "rb");
int size;
fseek(image, 0, SEEK_END);
size = ftell(image);
fseek(image, 0, SEEK_SET);
printf("Sending Picture Size\n");
write(sock_fd, &size, strlen(size));

//Send Picture as Byte Array
printf("Sending Picture as Byte Array\n");
while(!feof(image)) {
    fread(buf, 1, strlen(buf), image);
    write(sock_fd, buf, strlen(buf));
    bzero(buf, strlen(buf));
}

Close(clientfd);
exit(0);
}
