#include <iostream>     // std::cout
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>       // std::vector
#include <cstdlib>
#include <cstdio>

using namespace std;

void pow_(int *M, int n, int *M1){
	//cout<<"Inside pow for n = "<<n<<endl;
	if(n == 1){ for(int i=0;i<16;i++) M1[i] = M[i]; return; }
	int M2[16];
	int M3[16];
	pow_(M,n/2,M2);
	
	//M3 = M2*M2;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			int sum = 0;
			for(int k=0;k<4;k++) sum = sum + M2[4*i+k]*M2[j+4*k];
			M3[4*i+j] = sum;
		}
	}
	if(n%2!=0){ //M1 = M*M3;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				int sum = 0;
				for(int k=0;k<4;k++) sum= sum+ M[4*i+k]*M3[j+4*k];
				M1[4*i+j] = sum;
			}
		}
	}
	else{ //M1 = M3;
		for(int i=0;i<16;i++) M1[i] = M3[i];
	}
	
	
}

int  do_it(int n){
	if(n < 0){
		if(n == 0) return 0;
		if(n == -1) return 3;
		if(n == -3) return 1;
		if(n == -2 )return 0;
	}
	int M[16] = {0,4,0,-1, 1,0,0,0, 0,1,0,0, 0,0,1,0};
	int M1[16];
	//calculate M^n .....
	pow_(M,n,M1);
	return (M1[1]*3 + M1[3]);
	
}

int main () {
	int n;
	cin>>n;
	cout<<"answer is :"<<do_it(n-3);
	//else cout<<"enter even number...."<<endl;
	
	return 0;
}