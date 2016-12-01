#include <iostream>
#include<set>
#include<queue>
#include<vector>
#include<algorithm>


using namespace std;

class comp{
	public:
		bool operator()( pair<int, pair<int,pair<int,int> > >  p1,  pair<int, pair<int,pair<int,int> > > p2){
			return p1.first < p2.first;
		}
} oo;


bool my_func( pair<int, pair<int,pair<int,int> > >  p1,  pair<int, pair<int,pair<int,int> > > p2){
			return p1.first < p2.first;
}
		

	
		
		
int main()
{
	
	
    typedef vector< pair<int,pair<int,int> > > line_seg;
	line_seg ls;
	int i,j,k,l,y,x1,x2;
	cout<<"Enter the no of line segment:";
	cin>>l;
	cout<<"Enter y x1,x2 of each line segment"<<endl;
	while(l--){
		cin>>y>>x1>>x2;
		ls.push_back(make_pair(y,make_pair(x1,x2)));
	}
	
	vector< pair<int, pair<int,pair<int,int> > > > segs;
	
	line_seg::iterator it = ls.begin();
	while(it!= ls.end()){
		i  =  it->second.first;
		j = it->first;
		k = it->second.second;
		segs.push_back(make_pair(i, make_pair(j,make_pair(i,k))) );
		segs.push_back(make_pair(k, make_pair(j,make_pair(i,k))) );
		it++;
	}
	
	
	sort(segs.begin(), segs.end(), my_func);
	cout<<"After sorting line_segments according to starting point and end point..."<<endl;
	vector< pair<int, pair<int,pair<int,int> > > >::iterator itt = segs.begin();
	while(itt!= segs.end()){
		cout<<itt->first<<" ("<<itt->second.first<<" ["<<itt->second.second.first<<","<<itt->second.second.second<<"]"<<")"<<endl;
		itt++;
	}
	
	
	
	
	
	line_seg heap_;
	line_seg result;
	itt = segs.begin();
	while(itt!=segs.end()){
		//if starting point...
		if(itt->first == itt->second.second.first){
			heap_.push_back(itt->second);
			push_heap(heap_.begin(), heap_.end());
			if(heap_.size() > 1){
				it = heap_.begin();
				//if this line_seg is at top...
				if(it->first == itt->second.first){
					//set this line_seg in result remove previous one...
					it = result.end() -1;
					pair<int,pair<int,int> >  p1 = *it;
					result.erase(it);
					p1.second.second = itt->first;
					result.push_back(p1);
					result.push_back(itt->second);
				}
			}
			else{
				//only 1 line segment in heap so push in result...
				result.push_back(itt->second);
			}
		}
		else{
			//if it is end point remove from heap...
			//if it was at top...
			if(itt->second.first == heap_.begin()->first){
				pop_heap(heap_.begin(),heap_.end()); heap_.pop_back();
				
				// if heap_size > 0 then set max_segment now to result...
				if(heap_.size()>0){
					pair<int,pair<int,int> > p1 =  *(heap_.begin());
					p1.second.first = itt->first;
					result.push_back(p1);
				}
				
			}
			else{
				//if not at top simply remove it from heap...
				heap_.erase(find(heap_.begin(), heap_.end(), itt->second) );
				make_heap(heap_.begin(), heap_.end());
				int i;
			}
			
		}
		itt++;
	}
	
	
	it = result.begin();
	while(it!= result.end()){
		cout<<it->first<<"("<<it->second.first<<","<<it->second.second<<")"<<endl;
		it++;
	}
	
 
return 0;
}