/* Longest Increasing Subsequence  
*  A[] = {3, 2, 4, 1, 3, 4, 7, 2, 5, 3, 7}
*  LIS = 5 {1,3,4,5,7}
*/

#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define F first
#define S second

int LIS(int *a, int size){
	typedef vector<pair<int,int> > data;
	data active_list;
	active_list.pb({a[0],1});
	data::iterator it;
	for(int i=1;i<size;i++){
		it = lower_bound(active_list.begin(),active_list.end(),mp(a[i],0), 
								[](pair<int,int> element, pair<int,int> val)->bool{return element.F < val.F; });
		if(it == active_list.begin()){
			// Start new list with size 1.
			// That is replace current active_list of size 1 with a[i];
			active_list[0] = {a[i],1};
		}
		else if(it == active_list.end()){
			// Append to the largest list, create one new active_list
			int s = active_list.size();
			active_list.pb({a[i],s+1});
		}
		else{
			if(it->F > a[i])
				it->F = a[i];
		}
	
	}
	return active_list.size();
}


int main(){
	int N;
	cin>>N;
	int a[N];
	for(int i=0;i<N;i++) scanf("%d",a+i);
	printf("LIS = %d\n",LIS(a,N));
	return 0;
}
