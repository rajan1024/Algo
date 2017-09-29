#include <bits/stdc++.h>
using namespace std;

// Change rand function accordingly.
#define RAND rand()

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int flag;


int partition(int *a, int l, int r){
    int size = r-l+1;
    int pidx = RAND%size;
    pidx = l+pidx;
    swap(a+l,a+pidx);
    int pivot = a[l];
    int left = l;
    int right = r;
    while(left <= right){
        while(a[left] <= pivot && left <= r) left++;
        while(a[right] > pivot && right >= l) right--;
	if(left <= right){
		swap(a+left,a+right);
		left++;
		right--;
	}
    }
    swap(a+l,a+right);
    return right;
    
}

int find_kth_smallest(int *a, int n, int k){
    k--;
    int l = 0;
    int r = n-1;
    int idx = partition(a,0,n-1);
    while(1){
        //printf("partitioning in range{%d,%d} pivot at %d\n",l,r,idx);
        if(idx == k) return a[idx];
        if(idx > k){
            r = idx-1;
            idx = partition(a,l,r);
        }
        if(idx < k){
            l = idx+1;
            idx = partition(a,l,r);
       	}
    }
}



int main() {
	int T;
	cin>>T;
	while(T--){
	    int n,k;
	    cin>>n;
	    int a[n];
	    vector<int> b(n);
	    for(int i=0;i<n;i++) scanf("%d",a+i);
	    for(int i=0;i<n;i++) b[i] = a[i];
	    cin>>k;
	    printf("%d\n",find_kth_smallest(a,n,k));
	    

	}
	return 0;
}
