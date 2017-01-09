#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define fbo(x) (x&(-x))


#define MAX 100005


void add(int *b, int idx, int n, int size){
	while(idx<= size){
		b[idx] += n;
		idx +=  fbo(idx);
	}
	
}

void r_add(int *b, int *b_, int l, int r, int v, int size){
	add(b,l,v,size);
	add(b,r+1,-v,size);
	add(b_,l,(l-1)*v,size);
	add(b_,r+1, -(r)*v,size);
	
}

int sumupto(int *b, int *b_, int idx){
	int s1 = 0;
	int i = idx;
	while(idx){
		s1 += b[idx];
		idx -=  fbo(idx);
	}
	
	idx = i;
	s1 *= idx;
	while(idx){
		s1 -= b_[idx];
		idx -=fbo(idx);
	}
	return s1;
}





int main(){
	int bit[MAX] = {0};
	int bit_[MAX] = {0};
	
	while(1){
		int l,r,v;
		cin>>l>>r>>v;
		r_add(bit,bit_,l,r,v,MAX);
		for(int i=1;i<21;i++) printf("%3d ",i); cout<<endl;
		for(int i=1;i<21;i++) printf("%3d ",sumupto(bit,bit_,i));
		cout<<endl;
	}
	return 0;
}