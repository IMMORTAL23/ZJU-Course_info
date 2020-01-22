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
#include <openssl/md5.h>
#define BUFFSIZE 100
#define MAX_RAMDOM_NUM 1000
#define MAX_KEY_LEN 20
#define random(x) (rand()%x)
using namespace std;

unsigned char TK[17]={0};
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
void Xor(char* plain, char* key,char* cipher)
{
    int i=0;
    for(i=0;i<16;i++){
        cipher[i] = plain[i] ^ key[i];
    }
}
void GenerateKey(char* Nonce,unsigned char* TK,unsigned char* key)
{
    char MAC[20]="00:0c:29:c5:22:90";
    char IV[30]={0};
    strcpy(IV,MAC);
    strcat(IV,Nonce);
    char tmp[BUFFSIZE]={0};
    strcpy(tmp,IV);
    strcat(tmp, (char*)TK);
    //printf("%s\n",tmp);
    MD5((unsigned char*)tmp, strlen(tmp), key);
}
void int2char(int num, char * q)
{
    int n=0;
    sprintf(q, "%d", num);
    while(num=num/10) n++;
    n++;
    q[n] = '\0';
}
/*
AP 程序接收两个命令行参数： 
1. 密码 (MasterKey) 
2. 端口  
例如，如果程序命名为 AP, 则启动命令如下  ./AP z3dg35dg 1234
*/
int main(int argc, char *argv[])
{
    srand((int)time(0));
    char command[20]={0};
    if (argc !=3)
    {
        printf("the input is invalid!\n");
        exit(-1);
    }
    int sockfd;
    struct sockaddr_in ServerAddr, ClientAddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        printf("Socket Create Failed!\n");
        return -1;
    }
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = atoi(argv[2]);
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(ServerAddr.sin_zero), 8);
	
	//设置recv的超时时间为3
    struct timeval timeout ={3,0};    
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(struct timeval));
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(struct timeval));
    if(bind(sockfd, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) == -1)
    {
        printf("Bind Failed!\n");
        close(sockfd);
        return -1;
    }
    if(listen(sockfd, 5) == -1)
    {
        printf("Listen Failed!\n");
        close(sockfd);
        return -1;
    }
    printf("AP is prepared! The sockfd is %d\n",sockfd);
    int ConnectSize = sizeof(struct sockaddr_in);
    int Clientfd;
    Clientfd = accept(sockfd, (struct sockaddr *)&ClientAddr, (socklen_t *)&ConnectSize);
//-----------begin the WPA2------------------
    recv(Clientfd, command, 20, 0);
    char clentACK[17]={0};
    if(!strcmp(command,"request"))
    {
    //---------the first step-------------
        int r=random(MAX_RAMDOM_NUM);
        int ANonce = random(MAX_RAMDOM_NUM);
        struct package pac1;
        memset(pac1.ACK,0,sizeof(pac1.ACK));
        pac1.Anonce = ANonce;
        pac1.r = r;
        printf("SEND: the first handshake\n");
        printf("r:  %d\n",r);
        printf("ANonce=%d\n\n",ANonce);
        send(Clientfd,&pac1,sizeof(pac1),0);
    //--------the second step------------
        int CNonce;
        recv(Clientfd, &CNonce,sizeof(CNonce), 0);
        recv(Clientfd, &r,sizeof(r), 0);
        printf("RECV: the second handshake\n");
        printf("r:  %d\n",r);
        printf("CNonce=%d\n\n",CNonce);
    //-------the third step------------
        char MasterKey[MAX_KEY_LEN];
        strcpy(MasterKey,argv[1]);
        char ANonce_chr[MAX_KEY_LEN],CNonce_chr[MAX_KEY_LEN];
        int2char(ANonce,ANonce_chr);
        int2char(CNonce,CNonce_chr);
        char tmp[BUFFSIZE];
        strcpy(tmp,ANonce_chr);
        strcat(tmp,CNonce_chr);
        strcat(tmp,MasterKey);
        //printf("%s\n",tmp);
        MD5((unsigned char*)tmp, strlen(tmp), TK);
        //printf("TK:%s\n",TK);
        while(strcmp(clentACK,"Completed!\n")){
            s:
            r++;
            struct package pac2 = {.Anonce = -1};
            strcpy(pac2.ACK,"I have get the CNonce.\n");
            pac2.r = r;
            send(Clientfd,&pac2,sizeof(pac2),0);
            printf("SEND: the third handshake\n");
            printf("r:  %d\n",r);
            printf("ACK=%s\n\n",pac2.ACK);
            time_t start ,end ;  
            double cost;  
            time(&start);  
    //-------the fourth step------------    
            while(1)
            {
                char lastrecv[17] ={0};
                strcpy(lastrecv, clentACK);
                memset(clentACK,0,sizeof(clentACK));
                recv(Clientfd, clentACK,sizeof(clentACK), 0);
                if(!strcmp(lastrecv, clentACK)) break;
                if(strlen(clentACK)<4){
                    continue;
                }else if(strcmp(clentACK,"Completed!\n"))
				//如果收到的不是ACK包那就一定是密文包
                {
                    unsigned char hexcipher[33]={0};
                    dump_hex((unsigned char*)clentACK,16,hexcipher);
                    printf("Ciphertext = %s\n", hexcipher);
                }else{
                    break;
                }
				//设置等待ACK包的最长时间，超过改时间后就重发请求
                time(&end);  
                cost=difftime(end,start); 
                if(cost>4) goto s;
            }
            
        }
        recv(Clientfd, &r,sizeof(r), 0);
        printf("RECV: the final handshake\n");
        printf("r=%d\n",r);
        printf("Client:%s\n\n",clentACK);
    }
//---initial the parameter and begin the data transfer---
    if(!strcmp(clentACK,"Completed!\n"))
    {
        int Nonce = 0;
        char cipher[16]={0};
        unsigned char hexcipher[33]={0};
        unsigned char hexkey[33]={0};
        char plain[17]={0};
        while(recv(Clientfd, cipher,16, 0))
        {
            if(!strcmp(cipher,"end")) break; //结束标记
            dump_hex((unsigned char*)cipher,16, hexcipher);
            unsigned char key[16];
            char Noncechar[10]={0};
            int2char(Nonce,Noncechar);
            //printf("%s\n",TK);
            GenerateKey(Noncechar,TK, key);
            dump_hex((unsigned char*)key,16,hexkey);
            Xor(cipher, (char*)key, plain);
            printf("-------Nonce = %d ----------\n",Nonce);
            printf("Plaintext  = %s\n", plain);
            printf("Ciphertext = %s\n", hexcipher);
            printf("Key = %s\n\n",hexkey);
            Nonce ++;
            memset(cipher,0,sizeof(cipher));
        }
    }
    close(sockfd);
}