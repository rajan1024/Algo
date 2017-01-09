#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define fbo(x) (x&(-x))
#define min(x,y) (x<y?x:y)

#define MAX 99

typedef vector<pair<int,pair<int,int> > > seg_tree;


void do_it(seg_tree &a,int n){
	for(int i=n-1;i>0;i--){	
		a[i].F = min(a[2*i].F,a[2*i+1].F);
		a[i].S.F = a[2*i].S.F;
		a[i].S.S = a[2*i+1].S.S;
		//printf("a[%d] = %2d l=%d  r=%d\n",i,a[i].F,a[i].S.F,a[i].S.S);
	}
	
}

int p2(int n){
	int i=1;
	while(i<n){
		i*=2;
	}
	return i;
}



void update(seg_tree &a,  int idx, int v, int n){
	idx = idx+n-1;
	a[idx].F = v;
	idx = idx>>1;
	while(idx){
		a[idx].F = min(a[idx*2].F,a[idx*2+1].F);
		idx = idx>>1;
		
	}
}


int min_range(seg_tree &a, int l, int r, int idx){
	int _l = a[idx].S.F;
	int _r = a[idx].S.S;
	if(l==_l && r==_r) return a[idx].F;
	int mid = (_l+_r)/2;
	if(l<=mid && r>mid) return min(min_range(a,l,mid,2*idx),min_range(a,mid+1,r,2*idx+1));
	if(r<=mid) return min_range(a,l,r,2*idx);
	if(r>mid) return min_range(a,l,r,2*idx+1);
}


int main(){
	int n,t,_n;
	cin>>n;
	_n = n;
	n = p2(n); // returns next power of 2 greater than n
	seg_tree a(2*n,mp(0,mp(0,0)));
	
	for(int i=0;i<_n;i++){
		cin>>t;
		a[i+n].F = t;
		a[i+n].S.F =  a[i+n].S.S = 1+i;
	}
	for(int i=_n+n;i<2*n;i++){
		a[i].F = MAX;
		a[i].S.F =  a[i].S.S = i-n+1;
	}
	do_it(a,n);
	for(int i=1;i<2*n;i++) printf("%2d  ",i);cout<<endl;
	for(int i=1;i<2*n;i++) printf("%2d  ",a[i].F);
	
	//for(int i=1;i<2*n;i++) printf("%-2d:%-3d{%-2d,%-2d}\n",i,a[i].F,a[i].S.F,a[i].S.S);
	while(1){
		int f,idx,v,l,r;
		cin>>f;
		if(f&1){
			cin>>idx>>v;
			update(a,idx,v,n);
		} 
		else{
			cin>>l>>r;
			assert(l<=r);
			cout<<min_range(a,l,r,1)<<endl;
		}
		
		for(int i=1;i<2*n;i++) printf("%2d  ",i);cout<<endl;
		for(int i=1;i<2*n;i++) printf("%2d  ",a[i].F);cout<<endl;
		
	}
	return 0;
}

