#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define DUPLICATION 8
int sockfd_client;
int sockfd_server;
int Clientfd;
struct package{
    int Anonce;
    char ACK[30];
    int r;
};
/*输入密文字符，将它们转为两个16进制数*/
void dump_hex(unsigned char *p, int n, unsigned char *q)
{
   int i;
   for(i=0; i<n; i++)
   {
      sprintf((char *)&q[i*2], "%02X", p[i]);
   }
   q[i*2] = '\0';
}

//check the message from CLient to AP
void* func1(void *args)
{
    int count = 0;
    FILE * fp;
    if((fp = fopen("captured_cipher","w+"))==NULL){
        printf("Can't open the file!\n");
        exit(1);
    }
    while (true)
    {
        char buff[50]={0};
        struct package b;
	    memset(&b,0,sizeof(b));
        // get the package from client to server
        int len=recv(Clientfd,buff,  50 ,0);
        if(len>0)
        {
            if(strstr(buff,"Completed!\n"))
            {
                printf("capture the ACK package.\n");
                count++;
                if(count==DUPLICATION) {
                    send(sockfd_client,buff,len,0);
                    printf("send the ACK package.\n");
                }
                fprintf(fp,"%d\n",count);
                continue;
            }
            
            else if(len == 16)//the message is a cipher
            {
                unsigned char hex[50]={0};
                dump_hex((unsigned char*)buff,16,hex);
                printf("encrypted data:%s\n",hex);
                fprintf(fp,"%s\n",hex);
            }
            send(sockfd_client,buff,len,0);
            if(!strcmp(buff,"end")) 
            {
                break;
            }
        }
    }
    fclose(fp);
}

//send all the message from AP to Client
void* func2(void* args)
{
    while (true)
    {
        unsigned char buff[50]={0};
        int len=recv(sockfd_client,buff,  50 ,0);
        if(len > 0)
        {
            send(Clientfd,buff,len,0);
        }
        
    }
}

// 1.target IP address 2.target AP's port 3. my port
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("the input is invalid!\n");
        exit(-1);
    }
    // as a client
    if((sockfd_client = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() failed!\n");
        return -1;
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  //具体的IP地址
    serv_addr.sin_port = (atoi(argv[2]));           //端口
    bzero(&(serv_addr.sin_zero), 8);
    if(connect(sockfd_client, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("connect() failed!\n");
        close(sockfd_client);
        return -1;
    }
    printf("Connect to the target.\n");
    
	//as a server 
    struct sockaddr_in ServerAddr, ClientAddr;
    sockfd_server = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd_server == -1)
    {
        printf("Socket Create Failed!\n");
        return -1;
    }
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = atoi(argv[3]);
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(ServerAddr.sin_zero), 8);
    if(bind(sockfd_server, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) == -1)
    {
        printf("Bind Failed!\n");
        close(sockfd_server);
        return -1;
    }
    if(listen(sockfd_server, 5) == -1)
    {
        printf("Listen Failed!\n");
        close(sockfd_server);
        return -1;
    }
    printf("Prepared for the client!\n");
    printf("server socketfd: %d     client socketfd: %d;\n",sockfd_server,sockfd_client);
    int ConnectSize = sizeof(struct sockaddr_in);
    Clientfd = accept(sockfd_server, (struct sockaddr *)&ClientAddr, (socklen_t *)&ConnectSize);
    //begin to attack
	pthread_t tid1,tid2;
    pthread_create(&tid2, NULL, func2, NULL);
    pthread_create(&tid1, NULL, func1, NULL);
    pthread_join(tid1,NULL);
    close(sockfd_server);
}