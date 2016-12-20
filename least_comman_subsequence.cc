#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>

using namespace std;

int max(int i, int j){ if(i>j) return i; else return j;}

int fuck(int *a,string str1,string str2,int n1, int n2){
	//cout<<"At:-----	n1 = "<<n1<<" n2 = "<<n2<<endl;
	if(n1 == str1.size() || n2 == str2.size()) return 0;
	
	if(a[n1*str2.size()+n2] != -1) return a[n1*str2.size()+n2];
	
	if(str1[n1] == str2[n2]){
		//cout<<"Match found.."<<endl;
		int k = fuck(a,str1,str2,n1+1,n2+1);
		//cout<<"At n1 = "<<n1<<" n2 = "<<n2<<"ans = "<<1+k<<endl;
		a[n1*str2.size()+n2] = 1+k;
		return 1+k;
	} 
	else{
		//cout<<"Match not found...."<<endl;
		int k1,k2;
		k1 = fuck(a,str1,str2,n1,n2+1);
		k2 = fuck(a,str1,str2,n1+1,n2);
		int r = max(k1,k2);
		//cout<<"At n1 = "<<n1<<" n2 = "<<n2<<"ans = "<<r<<endl;
		a[n1*str2.size()+n2] = r;
		return r;
	} 
}

int main(){
string str1,str2;
int n,n1,n2;
cin>>n;
while(n--){
	cin>>n1>>n2;
	cin>>str1;
	cin>>str2;
	n1 = n2 = 0;
	int a[str1.size()*str2.size()];
	for(int i=0;i<str1.size();i++) for(int j=0;j<str2.size();j++) a[i*str2.size()+j] = -1;
	cout<<fuck(a,str1,str2,n1,n2)<<endl;
}
return 0;
}