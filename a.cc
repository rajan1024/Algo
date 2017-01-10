#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define fbo(x) (x&(-x))
#define min(x,y) (x<y?x:y)
#define pc putchar_unlocked
#define gc getchar_unlocked
template<typename T>
void scanint(T &x){	 
	register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

template<typename T>
void printint(T a){
int i=0;
char S[20];
while(a>0)
{
    S[i++]=a%10+'0';
a=a/10;
}
--i;
while(i>=0)
pc(S[i--]);
}

typedef pair<int,int> pii;
typedef vector<pair<pair<int,int>,pair<int,int> > > seg_tree;


void do_it(seg_tree &a,int n){
	for(int i=n-1;i>0;i--){	
		if(  abs(a[i*2].F.F) > abs(a[i*2+1].F.F) ){
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
		if(abs(a[idx*2].F.F) > abs(a[idx*2+1].F.F)){
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

int main(){
	
	
	int n,e,u,v;
	cin>>n>>e;
	int _n = p2(n);
	seg_tree st(2*_n,mp(mp(0,0),mp(0,0)));
	for(int i=_n;i<2*_n;i++){
		st[i].F.S = i-_n+1;
		st[i].S.F = st[i].S.S = i-_n+1;
	}
	vector<vector<int> > g1(n+1),g2(n+1);
	vector<pii> edge(n+1);
	for(int i=0;i<e;i++){
		scanint(u);
		scanint(v);
		edge[i+1] = mp(u,v);
		g1[u].pb(v);
		g2[v].pb(u);
		st[_n+u-1].F.F++;
		st[_n+v-1].F.F--;
	}
	
	
	for(int i=_n;i<2*n;i++){
		if(abs(st[i].F.F)%2 != 0){cout<<"NO"<<endl; return 0;}
	}
	
	cout<<"YES"<<endl;
	do_it(st,_n);
	
	
	
	
	
	
	
	
	while(st[1].F.F != 0){
		int idx = st[1].F.S; //stores the node having maximum defect...
		int def = st[1].F.F; //to find out defect...
		cout<<"node is "<<idx<<" defect is "<<def<<"    ";
		
		if(def > 0){ 
			int node = g1[idx][0]; //take out first outgoing node...
			int min = g1[node].size()-g2[node].size(); //calculte its defect...
			int min_n = node;
			for(int i=1;i<g1[idx].size();i++){
				int node = g1[idx][i];
				int temp = g1[node].size()-g2[node].size();
				if(temp < min){ min = temp; min_n = node; }
			}
			cout<<"swaping edge between "<<idx<<':'<< min_n<<endl;
			//min_n is the node with most negative defect...
			//reverse the edge between idx and min_n...
			g1[idx].erase(find(g1[idx].begin(),g1[idx].end(), min_n ));
			g2[idx].pb(min_n);
			g1[min_n].pb(idx);
			g2[min_n].erase(find(g2[min_n].begin(),g2[min_n].end(), idx ) );
			
			//correct the defect in seg tree...
			update(st,idx, st[idx+_n-1].F.F - 2,_n);
			update(st,min_n, st[min_n+_n-1].F.F + 2,_n);
		}
		else{
			int node = g2[idx][0]; 
			int max = g1[node].size()-g2[node].size(); 
			int max_n = node;
			for(int i=1;i<g2[idx].size();i++){
				int node = g2[idx][i];
				int temp = g1[node].size()-g2[node].size();
				if(temp > max){ max = temp; max_n = node; }
			}
			
			cout<<"swaping edge between "<<idx<<':'<<max_n<<endl;
			
			g2[idx].erase(find(g2[idx].begin(),g2[idx].end(), max_n ));
			g1[idx].pb(max_n);
			g2[max_n].pb(idx);
			g1[max_n].erase(find(g1[max_n].begin(),g1[max_n].end(), idx ) );
			
			//correct the defect in seg tree...
			update(st,idx, st[idx+_n-1].F.F + 2,_n);
			update(st,max_n, st[max_n+_n-1].F.F - 2,_n);
		}
	}
	
	
	
	for(int i=1;i<=e;i++){
		u = edge[i].F;
		v = edge[i].S;
		if(find(g1[u].begin(), g1[u].end(), v) != g1[u].end()) { printint(u); pc(' '); printint(v); pc('\n');}
		else { printint(v); pc(' '); printint(u); pc('\n');}
	}
	
	
	
	cout<<"FINISHING,,,,"<<endl;
	return 0;
}








