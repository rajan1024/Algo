
#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;



int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

int gcd(int a, int b, int *x, int *y){
  if(b==0){
    *x = 1;
    *y = 0;
    return a;
  }
  int x1,y1;
  int g = gcd(b,a%b,&x1,&y1);
  *y = x1 - (a/b)*y1;
  *x = y1;
  return g;
}


int main(){
int a,b,g,x,y;
cin>>a>>b;
g = gcdExtended(min(a,b), max(a,b),&x,&y);
int x1,y1,g1;
g1 = gcd(max(a,b),min(a,b),&x1,&y1);

cout<<"gcd = "<<g<<"coefficents = "<<x<<' '<<y<<endl;
cout<<"gcd = "<<g1<<"coefficents = "<<x1<<' '<<y1<<endl;

return 0;
}
