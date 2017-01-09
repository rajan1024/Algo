#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define fbo(x) (x&(-x))
#define min(x,y) (x<y?x:y)

#define MAX 99

typedef vector<pair<pair<int,int>,pair<int,int> > > seg_tree;


void do_it(seg_tree &a,int n){
	for(int i=n-1;i>0;i--){	
		if(  a[i*2].F.F < a[i*2+1].F.F ){
			a[i].F.F = a[2*i].F.F;
			a[i].F.S = a[2*i].F.S;
		}
		else{
			a[i].F.F = a[2*i+1].F.F;
			a[i].F.S = a[2*i+1].F.S;
		}
		
		a[i].S.F = a[2*i].S.F;
		a[i].S.S = a[2*i+1].S.S;
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
	a[idx].F.F = v;
	idx = idx>>1;
	while(idx){
		if(a[idx*2].F.F < a[idx*2+1].F.F){
			a[idx].F.F = a[idx*2].F.F;
			a[idx].F.S = a[idx*2].F.S;
		}
		else{
			a[idx].F.F = a[2*idx+1].F.F;
			a[idx].F.S = a[2*idx+1].F.S;
		}
		idx = idx>>1;
		
	}
}


int min_range(seg_tree &a, int l, int r, int idx, int n){
	int _l = a[idx].S.F;
	int _r = a[idx].S.S;
	if(l==_l && r==_r) return a[idx].F.S;
	int mid = (_l+_r)/2;
	if(l<=mid && r>mid){
		int idx_l = min_range(a,l,mid,2*idx,n);
		int idx_r = min_range(a,mid+1,r,2*idx+1,n);
		if(a[idx_l+n-1].F.F < a[idx_r+n-1].F.F){
			return idx_l;
		} 
		else return idx_r;
	}
	if(r<=mid) return min_range(a,l,r,2*idx,n);
	if(r>mid) return min_range(a,l,r,2*idx+1,n);
}


int main(){
	int n,t,_n;
	cin>>n;
	_n = n;
	n = p2(n); // returns next power of 2 greater than n
	seg_tree a(2*n,mp(mp(0,0),mp(0,0)));
	
	for(int i=0;i<_n;i++){
		cin>>t;
		a[i+n].F.F = t;
		a[i+n].S.F =  a[i+n].S.S = a[i+n].F.S = 1+i;
	}
	for(int i=_n+n;i<2*n;i++){
		a[i].F.F = MAX;
		a[i].S.F =  a[i].S.S = a[i].F.S = i-n+1;
	}
	do_it(a,n);
	for(int i=1;i<2*n;i++) printf("%2d  ",i);cout<<endl;
	for(int i=1;i<2*n;i++) printf("%2d  ",a[i].F.S+n-1);cout<<endl;
	for(int i=1;i<2*n;i++) printf("%2d  ",a[i].F.F);cout<<endl;
	
	
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
			cout<<min_range(a,l,r,1,n)<<endl;
		}
		
		for(int i=1;i<2*n;i++) printf("%2d  ",i);cout<<endl;
		for(int i=1;i<2*n;i++) printf("%2d  ",a[i].F.S+n-1);cout<<endl;
		for(int i=1;i<2*n;i++) printf("%2d  ",a[i].F.F);cout<<endl;
		
	}
	return 0;
}

