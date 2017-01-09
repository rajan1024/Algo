#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define fbo(x) (x&(-x))
#define min(x,y) (x<y?x:y)

typedef vector<pair<int,pair<int,int> > > seg_tree;


void do_it(seg_tree &a,int n){
	for(int i=n-1;i>0;i--){	
		a[i].F = a[2*i].F + a[2*i+1].F;
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

int updated(seg_tree &a, int idx, int size){
	if(idx>=size) return 1;
	if(a[idx].F == a[2*idx].F+a[2*idx+1].F) return 1;
	else return 0;
}


void update(seg_tree &a, int l, int r, int v, int idx, int size){
	//printf("Updating l=%d to r=%d by value = %d at idx = %d\n",l,r,v,idx);
	if(!updated(a,idx,size)){
		//cout<<"Not updateded.."<<endl;
		int res = a[idx].F - (a[2*idx].F+a[2*idx+1].F);
		res = res/2;
		a[2*idx].F += res;
		a[2*idx+1].F += res;
	}
	int _l = a[idx].S.F, _r = a[idx].S.S;
	a[idx].F = a[idx].F+ (r-l+1)*v;
	if(_l == l && _r == r){
		return;
	}
	int mid = (_l+_r)/2;
	if(l<=mid && r >= mid+1){
		update(a,l,mid,v,2*idx,size);
		update(a,mid+1,r,v,2*idx+1,size);
		return;
	}
	if(mid >= r){
		update(a,l,r,v,2*idx,size);
		return;
	}
	if(mid+1<= l){
		update(a,l,r,v,2*idx+1,size);
		return;
	}
}


int sum(seg_tree &a, int l, int r, int idx){
	int _l = a[idx].S.F, _r = a[idx].S.S;
	int mid = (_l+_r)/2;
	//printf("sum from l=%d to r=%d  _l =%d _r =%d  mid=%d at idx = %d\n",l,r,_l,_r,mid,idx);

	if(_l==l && _r == r) return a[idx].F;
	if(mid >=l && mid+1 <=r) return sum(a,l,mid,idx*2) + sum(a,mid+1,r,idx*2+1);
	if(r<=mid) return sum(a,l,r,idx*2);
	if(l>=mid+1) return sum(a,l,r,idx*2+1);
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
		a[i].S.F =  a[i].S.S = i-n+1;
	}
	do_it(a,n);
	//for(int i=1;i<2*n;i++) printf("%-2d:%-3d{%-2d,%-2d}\n",i,a[i].F,a[i].S.F,a[i].S.S);
	while(1){
		int f,l,r,v;
		cin>>f;
		if(f&1){
			cin>>l>>r>>v;
			assert(l<=r);
			update(a,l,r,v,1,n);
		} 
		else{
			cin>>l>>r;
			assert(l<=r);
			cout<<sum(a,l,r,1)<<endl;
		} 
	}
	return 0;
}

