#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;

/* Give this program input "9 11 1 2 1 3 3 4 3 5 3 6 4 5 2 7 2 8 2 9 6 7 8 9"
   and see the bug in memory allocation by vector.
   run 1 time without commenting the below lines which is specified..
   and 1 time by commenting.
*/

int main(){
	
	// 'n' is the no of nodes and 'e' is no of edges...
	int n,e,u,v;
	cin>>n>>e;

	//g1[i] stores the list of nodes you can reach, from node 'i'. (outgoing edges's nodes)
	//g2[i] stores the list of nodes from which you can reach node 'i'. (incoming edge's nodes)
	vector<vector<int> > g1(n+1),g2(n+1);
	//vector<pii> edge(n+1); //comment this line...
	for(int i=0;i<e;i++){
		cin>>u>>v;
		//edge[i+1] = mp(u,v); //comment this line...
		g1[u].pb(v);
		g2[v].pb(u);
	}

	for(int i=1;i<g1.size();i++){
		cout<<i<<':'<<"->{";
		for(int j=0;j<g1[i].size();j++) cout<<g1[i][j]<<' '; cout<<"}  <-{";
		for(int j=0;j<g2[i].size();j++) cout<<g2[i][j]<<' '; cout<<'}'<<endl;
	}


	//reverse the edge 3->5
	int n1=5,n2=3;
	g2[n1].erase(find(g2[n1].begin(),g2[n1].end(), n2 ));
	g1[n1].pb(n2);
	g2[n2].pb(n1);
	g1[n2].erase(find(g1[n2].begin(),g1[n2].end(), n1 ) );

	//edge the edge is 5->3

	cout<<"Graph after reversing 3->5 edge..."<<endl;
	for(int i=1;i<g1.size();i++){
		cout<<i<<':'<<"->";
		for(int j=0;j<g1[i].size();j++) cout<<g1[i][j]<<' '; cout<<"  <-";
		for(int j=0;j<g2[i].size();j++) cout<<g2[i][j]<<' '; cout<<endl;
	}

	

	
	cout<<"FINISHING"<<endl;
	return 0;
}








