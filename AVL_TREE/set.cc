#include"avl_tree.h"


/* Set of Integers... */
class my_set : public Avl_tree{
public:
	// empty constructor.
	my_set():Avl_tree(	[](void *p1, void *p2)->int{
					int a1 = *(int*)p1, a2 = *(int*)p2;
					return a1>a2?1:(a1<a2?-1:0);
					},
				[](void *data)->void{ free(data); },
				[](node* nod)->void{ if(nod) printf("node = %d, size =%d, parent = %d\n",
						*(int*)(nod->data),nod->size,nod->parent?*(int*)(nod->parent->data):-1); 
					}
				){}

	void insert_element(int data){
		printf("inserting %d\n",data);
		int *p = (int*)malloc(sizeof(int));
		*p = data;
		insert_data(p);
	}
	void delete_element(int data){
		printf("deleting data %d\n",data);
		int *p = (int*)malloc(sizeof(int));
		*p = data;
		delete_data(p);
		free(p);
	}
	node* find_element(int data){
		int *p = (int*)malloc(sizeof(int));
		*p = data;
		node *nod = find_node(p);
		free(p);
		return nod;
	}
	
	int rank_of_element(int data){
		int *p = (int*)malloc(sizeof(int));
		*p = data;
		int r =rank(p);
		free(p);
		return r;
	}

	

};


int main(){
	my_set s;
	printf("tree size should be 0  = %d\n",s.size());
	s.insert_element(43);
	s.insert_element(3);
	s.insert_element(1);
	s.insert_element(34);
	s.insert_element(34);
	s.insert_element(55);
	s.delete_element(4444);
	s.delete_element(1);
	s.delete_element(3);

}
