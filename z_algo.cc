#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;

int z_algo(string str1,string str2){
	string str = str1;
	str.append("#");
	str.append(str2);
	int a[str.size()];
	a[0] = 0;
	int k,j;
	int cnt = 0;
	for(int i=1;i<str.size();){
		cnt = 0;
		if(str[i] == str[0]){
			k = 1;
			while(str[i+k] == str[k]){
				k++;
			}
			a[i] = k;
			for(j=1;j<k;j++){
				if(j+a[j]<k) a[i+j] = a[j];
				else break;
			}
			
			if(j== k) i = i+k;
			else i = i+j;
		}
		else{
			a[i] = 0;
			i++;
		} 
	}
	cout<<str<<endl;
	for(int i=0;i<str.size();i++){
		if(a[i] == str1.size()) cnt++;
		//cout<<a[i];
	}
	return cnt;
	
}


int main(){
	string str1,str2;
	getline(cin,str1);
	getline(cin,str2);
	
	int ans = z_algo(str1,str2);
	cout<<ans<<endl;
}








