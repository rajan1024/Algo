#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

struct node{
	int name;
	int color ;
	struct edge *edge;
	struct node *next_node;
};

struct edge{
	int weight;
	struct node *the_node;
	struct edge *next_edge;
};

struct node* add_node(struct node *start, int n){
	if(start == NULL){
		start = (struct node*)malloc(sizeof(struct node));
		start->name = n;
		start->edge = NULL;
		start->next_node = NULL;
		return start;
	}
	
	struct node *p;
	p = start;
	while(p->next_node != NULL){
		if(p->name == n) return start; //node already exists...
		p = p->next_node;
	}
	if(p->name == n) return start;
	p->next_node = (struct node*)malloc(sizeof(struct node));
	p = p->next_node;
	p->next_node = NULL;
	p->edge = NULL;
	p->name = n;
	
	return start;
}

struct node* find_node(struct node *start, int n){
	struct node *p;
	p = start;
	while(p!=NULL){
		if(p->name == n) return p;
		p = p->next_node;
	}
	return NULL;
}


void edge(struct node *start, int from, int to, int w=0){
	if(from==to) return; //no self loop allowed..
	//printf("edge(%d %d)\n",from,to);
	struct node *p,*f,*t,*q;
	f = find_node(start,from);
	if(f == NULL){
		//printf("node %d not found, adding...\n",from);
		add_node(start,from);
		f = find_node(start,from);
		if(f==NULL) cout<<"Impossible..."<<endl;
	}
	
	t = find_node(start,to);
	if(t==NULL){
		//printf("node %d not found, adding...\n",to);
		add_node(start,to);
		t = find_node(start,to);
	}
	//printf("addr of node from = %d and to = %d\n",f,t);
	//if f->edge == NULL => then add first edge to node f.
	if(f->edge == NULL){
		//printf("first time adding edge to node %d\n",from);
		f->edge = (struct edge*)malloc(sizeof(struct edge));
		f->edge->the_node = t;
		f->edge->weight = w;
		f->edge->next_edge = NULL;
		return;
	}
	
	struct edge *e;
	e = f->edge;
	while(e->next_edge != NULL){
		if(e->the_node == t) return; //edge already present... (no multi-edge)
		e = e->next_edge;
	}
	if(e->the_node == t) return;
	e->next_edge = (struct edge*)malloc(sizeof(struct edge));
	e = e->next_edge;
	e->the_node = t;
	e->weight = w;
	e->next_edge = NULL;
	
}

void d_edge(struct node *start, int from, int to, int w=0){
	edge(start,from,to,w);
	edge(start,to,from,w);
}

void print_graph(struct node *start){
	struct node *p;
	p = start;
	while(p!=NULL){
		cout<<p->name<<':';
		struct edge *e;
		e = p->edge;
		while(e!=NULL){
			cout<<e->the_node->name<<' ';
			e = e->next_edge;
		}
		cout<<endl;
		p=p->next_node;
	}
}


initialise_color(struct node *start,int c=0){
	struct node *p;
	p = start;
	while(p!=NULL){
		p->color = c;
		p=p->next_node;
	}
}








