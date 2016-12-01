#include<algorithm>
#include<vector>
#include<iostream>


using namespace std;

bool compare(const pair<int, int>&i, const pair<int, int>&j)
{
    return i.second < j.second;
}


int main(){
	
	vector< pair<int, int> >v;
	sort(v.begin(),v.end(),compare);
	return 0;
	
}
