#include<bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long int lli;
typedef pair<int,int> pii;
typedef pair<lli,lli> plli;


// suf[i] = k => ith rank has kth index.
// pos[i] = k => ith index has kth rank.

void suffix_array(char *str, int *suf){
	int n = strlen(str);
	int pos[n];
	int temp[n];
	temp[0] = 0;
	for(int i=0;i<n;i++){ pos[i] = str[i]; suf[i] = i;}
	int gap;

	auto comp_suff =	[&pos,&gap,n](int i,int j)->bool{
							if(pos[i]!=pos[j]) return pos[i]<pos[j];
							i = i+gap;
							j = j+gap;
							return (i<n and j<n)?pos[i]<pos[j]:i>j;
						};
	
	for(gap = 1;;gap*=2){
		sort(suf,suf+n, comp_suff);
		for(int i=0;i<n-1;i++) temp[i+1] = temp[i]+comp_suff(suf[i],suf[i+1]);
		for(int i=0;i<n;i++) pos[suf[i]] = temp[i];
		if(temp[n-1] == n-1 ) break;
	}
}


int main(){
	int t;
	cin>>t;
	while(t--){
		char str[100005];
		memset(str,0,100005);
		scanf("%s",str);
		int n = strlen(str);
		vector<vector<int> > pal(n,vector<int>(n,0));
		for(int i=0;i<n;i++) pal[i][i] = 1;
		for(int gap = 1;gap<n;gap++){
			for(int i=0;i+gap<n;i++){
				if(gap==1) pal[i][i+1] = str[i]==str[i+1]?1:0;
				else pal[i][i+gap] = (str[i] == str[i+gap])?pal[i+1][i+gap-1]:0;
			}
		}
		int suf[n];
		suffix_array(str,suf);
		for(int i=0;i<n;i++) printf("%s\n",str+suf[i]);	
	}
	return 0;
}
