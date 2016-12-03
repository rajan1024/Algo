#include<iostream>
#include<vector>
#include<map>

#define F first
#define S second

using namespace std;

//Each Node will have unique name<int> and can contain a data...
template <typename T>
struct Node {
	T* data;
	int name;
	map<string,int> n_attbr;
};

template <typename T>
class Graph {
	
	public:
		map<string,int> node_attbr;
		//vector< Node, Edges >; each edge contains name of Node and weight....
		vector< pair<Node<T>*, vector< pair<int,int> > > > head;
		
		void initialise_node_attbr(string str, int n){
			node_attbr[str] = n;
		}
		bool add_node(int _name,T* t = NULL){
			//Checking wheter node with same name already exists or not....
			for(int i=0;i<head.size();i++){
				if(head[i].F->name == _name) {
					cout<<"Node with name "<<_name<<" already exists. Two nodes should have unique name...."<<endl;
					return false;
				}
			}
			Node<T>* n = new Node<T>();
			n->data = t;
			n->name = _name;
			map<string,int>::iterator it = node_attbr.begin();
			while(it!=node_attbr.end()){
				n->n_attbr.insert( make_pair(it->F,it->S) );
				it++;
			}
			vector< pair<int,int> > v;
			head.push_back( make_pair(n,v));
		}
		bool d_edge(int f,int t,int w = 0){
			int fi,ti;
			//if nodes by name 'f' and 't' does not exists then add_node...
			if(find_node(f) == NULL) add_node(f);
			if(find_node(t) == NULL) add_node(t);
			fi = find_node_index(f);
			
			//Check if edge already exists....? Mulitedge not allowed...
			vector< pair<int,int> >::iterator it  = head[fi].S.begin();
			while(it!=head[fi].S.end()){
				if(it->F == t){
					cout<<"Edge alredy exists between "<<f<<" and "<<t<<". Multiedge not allowed...."<<endl;
					return false;
				}
				it++;
			}
			
			head[fi].S.push_back(make_pair(t,w));
			return true;
			
		}
		
		//Undirected edge....
		bool edge(int f, int t, int w=0){
			d_edge(f,t,w);
			d_edge(t,f,w);
		}
		
		T* find_node(int _name){
			for(int i=0;i<head.size();i++){
				if(head[i].F->name == _name) return head[i].F;
			}
			return NULL;
		}
		int find_node_index(int _name){
			for(int i=0;i<head.size();i++){
				if(head[i].F->name == _name) return i;
			}
			return -1;
		}
		
		
		void print_graph(){
			for(int i=0;i<head.size();i++){
				cout<<head[i].F->name<<':';
				for(int j=0;j<head[i].S.size();j++){
					cout<<" ("<<head[i].S[j].F<<","<<head[i].S[j].S<<")";
				}
				cout<<endl;
			}
		}
		
		
};

/*
int main(){
	
	Graph<void> g; //graph with nodes storing no data...
	g.initialise_node_attbr("color",0);
	g.initialise_node_attbr("sdlfads",9);
	g.add_node(3);
	cout<<g.head[0].F->name<<endl;
	cout<<g.head[0].F->n_attbr["sdlfads"]<<endl;
	g.add_node(6);
	g.d_edge(3,6,89);
	g.add_node(5);
	g.add_node(45);
	g.add_node(35);
	g.edge(3,5,45);
	g.edge(45,3,45);
	g.d_edge(35,45,4);
	g.edge(6,45);
	g.edge(6,35);
	cout<<"The whole Graph is...."<<endl;
	g.print_graph();
	return 0;
}
*/