/*
*	RSA cryptography program
*	
*	JunkProgramshelf
*	2024.6.22
*/

#include<stdio.h>
#include<winsock2.h>
#include<stdlib.h>

#define PORT 9999
int func(int a,int k,int n);


int main( ){
	int sock;
	struct sockaddr_in addr;
	int len;
	int len2;
	int result;
	unsigned char c[256];
	unsigned char k[256];
	int cipher=0;
	//public key
	int key=0;
	//secret key
	int d=359;
	//decrypted data
	int m=0;
	
	//Winsock2 Initialization
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,0), &wsaData);
	
	//Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//Socket Configration
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	//Conect to Server
	result = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	if (result != 0) {
		perror("connect");
		return 1;
	}
	
	//serve data
	//cipher text
	memset(c, 0, sizeof(c));
	len = recv(sock, c, sizeof(c), 0);
	//public key
	memset(k, 0, sizeof(k));
	len2 = recv(sock, k, sizeof(k), 0);
	
	
	//decrypted
	cipher=atoi(c);
	key=atoi(k);
	
	m=func(cipher,d,key);
	printf("<===================================>\n");
	printf("cipher text:::::%d\n",cipher);
	printf("decrypted data::%d\n",m);
	printf("<===================================>\n");
	//Finish  TCP session
	closesocket(sock);

	//Finish winsock2
	WSACleanup();
	
	return 0;
}

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
