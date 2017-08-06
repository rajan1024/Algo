#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;


void merge_sort(int *a, int left, int right, lli &inv_cnt){
	
	//printf("merge %d to %d\n",left,right);

	// If only one element return.....
	if(left == right) return;
	
	// If two elements are there swap if required...
	if(right-left == 1){
		if(a[left] > a[right]){
			int t = a[left];
			a[left] = a[right];
			a[right] = t; 
			inv_cnt++;
		}
		return;
	}

	// If more than two elements are there call merge_sort recursively...
	int mid = (left+right)/2;
	merge_sort(a,left,mid,inv_cnt);
	merge_sort(a,mid+1,right,inv_cnt);

	// Now time to merge a[left:mid] and a[mid+1:right]....
	// Create two array to hold left sorted and right sorted array...
	int size_left = mid-left+1;
	int size_right = right-mid;
	int al[size_left],ar[size_right];
	int idx = 0;
	for(int i=left;i<=mid;i++) al[idx++] = a[i];
	idx = 0;
	for(int i=mid+1;i<=right;i++) ar[idx++] = a[i];

	// Now merge al[] and ar[]  into a[]....
	// Index pointer to al[] and ar[] array...
	int idx_left=0,idx_right=0; 
	// Index pointer to a[] array..
	idx = left;

	// Untill one of two array becomes empty.....
	while(idx_left < size_left && idx_right < size_right){
		if(al[idx_left] > ar[idx_right]){
			// There is inversion....
			a[idx++] = ar[idx_right++];
			inv_cnt+=(size_left-idx_left);
		}
		else{
			a[idx++] = al[idx_left++];
		}
	}
	
	// Push the non_empty array....
	if(idx_left < size_left){
		while(idx_left < size_left){
			a[idx++] = al[idx_left++];
		}
	}
	else{
		while(idx_right < size_right){
			a[idx++] = ar[idx_right++];
		}
	}

	assert(idx == right+1);
	assert(idx_left == size_left);
	assert(idx_right == size_right);

}

int main(){
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++){
		scanf("%d",a+i);
	}
	
	lli inv_cnt = 0;
	
	merge_sort(a,0,n-1,inv_cnt);

	cout<<inv_cnt<<endl;

	return 0;
}
