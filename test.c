#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <wiringPi.h>
#include <time.h>

#define PIN1 25
#define PIN2 24
#define PIN3 23
#define PIN4 22
#define MAXLINE 1024
void low();
void high();
void loop(float len);
void initPin();

int main(int argc, char *argv[])
{
        int i,n,sockfd,new_fd;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        int sin_size,portnumber;
        char hello[]="Hello! Are You Fine?\n";
        char buff[1024]; 

        if(argc!=2)
        {
                fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
                exit(1);
        }

        if((portnumber=atoi(argv[1]))<0)
        {
                fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
                exit(1);
        }

        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
                fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
                exit(1);
        }

        initPin();

        bzero(&server_addr,sizeof(struct sockaddr_in));
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        server_addr.sin_port=htons(portnumber);

        if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
        {
                fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
                exit(1);
        }

        if(listen(sockfd,5)==-1)
        {
                fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
                exit(1);
        }

        while(1)
        {
                sin_size=sizeof(struct sockaddr_in);
                if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
                {
                        fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
                        exit(1);
                }

                fprintf(stderr,"Server get connection from %s\n",
                inet_ntoa(client_addr.sin_addr));

                n = recv(new_fd, buff, MAXLINE, 0);  
                buff[n] = '\0'; 
		fprintf(stderr,"----------------");
                for(i=2;i<=100;i++)
                {
			if(n != 1)
			{
				break;	
			}

                  	fprintf(stderr,"%d|--------|%s-------------high=%f\n",
				 n,buff,1+0.8*atoi(buff)/10);
                        loop(1+0.8 * atof(buff) / 10 );
                }

                fprintf(stderr,"-------end loop \n"),
                close(new_fd);
        }
        close(sockfd);
        exit(0);
}



void initPin()
{
        

        // printf("-----micros=%d\n",micros());
        wiringPiSetup();
        pinMode(PIN1,OUTPUT);
        pinMode(PIN2,OUTPUT);
        pinMode(PIN3,OUTPUT);
        pinMode(PIN4,OUTPUT);

        
}

void low()
{

        digitalWrite(PIN1,LOW);
        digitalWrite(PIN2,LOW);
        digitalWrite(PIN3,LOW);
        digitalWrite(PIN4,LOW);

}
void high()
{
        digitalWrite(PIN1,HIGH);
        digitalWrite(PIN2,HIGH);
        digitalWrite(PIN3,HIGH);
        digitalWrite(PIN4,HIGH);

}
//len 0.92-2.12ms
void loop(float len)
{
        int end;
        int start=micros();

        high();
        delayMicroseconds(len*1000);
        end = micros();
        // printf("high=%d\n",end-start);

        low();
        delayMicroseconds(20000+start-micros());
        end = micros();
        // printf("cycle=%d\n",end-start);
}


