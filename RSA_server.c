/*
*	RSA cryptography program
*	
*	JunkProgramshelf
*	2024.6.22
*/

#include<stdio.h>
#include<math.h>
#include<winsock2.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define PORT 9999


int gcd(int a,int b);
int chosen_e(int temp);
int chosen_d(int temp,int e);
int func(int a,int k,int n);

int main(){
	int sock;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int socklen;
	int result;
	int p = 17;
	int q = 29;
	int m = 100;
	int N = p * q;//N=493
	int temp=(p-1)*(q-1);//temp=448
	
	int e=151;
	int d=359;
	/*auto choise e & d */
	//int e=chosen_e(temp);
	//int d=chosen_d(temp,e);
	
	int c = func(m,e,N);
	printf("<===================================>\n");
	printf("plain text:%d\n",m);
	printf("d::::::::::%d\n",d);
	printf("e::::::::::%d\n",e);
	printf("N::::::::::%d\n",N);
	printf("cipher:::::%d\n",c);
	printf("<===================================>\n");
	char cipher[256];
	char key1[256];
	
	snprintf(cipher,sizeof(cipher),"%d",c);
	snprintf(key1,sizeof(key1),"%d",N);
	/*
	printf("%s\n",cipher);
	int data=atoi(cipher);
	printf("dara=%d\n",data);
	*/
	
	
	//Winsock2 Initialization
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,0), &wsaData);
	
	//Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	//sock2= socket(AF_INET, SOCK_STREAM, 0);
	
	//socket configration
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	//socket address assignment
	result = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	if (result != 0) {
		perror("bind");
		return 1;
	}
	//Waiting for request from TCP cliant  
	result = listen(sock, 5);
	if(result != 0) {
		perror("listen");
		return 1;
	}
	
	
	
	//Accept connection request from TCP client
	socklen = sizeof(client);
	sock = accept(sock, (struct sockaddr *)&client, &socklen);
	
	//send message
	send(sock, (const char*)cipher, sizeof(cipher), 0);
	send(sock,(const char*)key1,sizeof(key1),0);
	
	//Session ends for TCP
	closesocket(sock);
	
	//winsock2 finish
	WSACleanup();
	return 0;
}


int gcd(int a,int b){
	int x=a;
	int y=b;
	int r=0;
	//printf("x:::%d/y:::%d",x,y);
	if(x>y){
		while(true){
			r= x % y;
			if(r==0){
				return y;
			}else{
				x=y;
				y=r;
			}
		}
	}else if(x==y){
		return x;
		
	}else{
		while(true){
			r=y%x;
			if(r==0){
				return x;
			}else{
				y=x;
				x=r;
			}
		}
	}
	
}

int chosen_e(int temp){
	int e=0;
	srand((unsigned int)time(NULL));
	while(true){
		e = rand() % (temp-1) +1;
		if( (gcd(temp,e)==1)){
			break;
		}
	}
	return e;
}
int chosen_d(int temp,int e){
	int d=0;
	srand((unsigned int)time(NULL));
	while(true){
		d = rand() % (temp-1)+1;
		if( (d < temp) &&(( d * e ) % temp == 1) ){
			break;
		}
	}
	return d;
}

//High speed exponential calclation(a^k mod n)
int func(int a,int k,int n){
	a %= n;
	int i;
    unsigned int data = 1;
	if(a == 0 || n == 0){
		return 0;
	}
	if(k == 0){
		return 1 % n;
	}
	
    for(i = 0; i < k; i++) {
        data *= a;
        if(data >= n) {
            data %= n;
        }
    }
    return data;
}

