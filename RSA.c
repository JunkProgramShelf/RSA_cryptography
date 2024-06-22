/*
*	RSA cryptography program
*	
*	JunkProgramshelf
*	2024.6.22
*/

#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

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

int main(){
	int p=17;//primary number p
	int q=29;//primary number q
	int m=131;//plain text
	int N=0;// product of p & q
	int d=0;//public key
	int e=0;//private key
	int temp=0;//product of (p-1) & (q-1)
	int c=0;//cipher text
	
	
	//calclation N
	N = p * q;
	
	//chosen e
	temp=(p-1)*(q-1);
	//e=chosen_e(temp);
	e=425;
	//chosen d
	
	//d=chosen_d(temp,e);
	d=409;
	//encryption
	c = func(m,e,N);
	int dm= func(c,d,N);	
	printf("(p,q):::::::::::(%d.%d)\n",p,q);
	printf("N::::::::::::::::%d\n",N);
	printf("d::::::::::::::::%d\n",d);
	printf("e::::::::::::::::%d\n",e);
	printf("plain_text:::::::%d\n",m);
	printf("cipher_text::::::%d\n",c);
	printf("decrypted_text:::%d\n",dm);
	return 0;
}