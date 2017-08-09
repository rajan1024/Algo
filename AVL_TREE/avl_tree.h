#include<bits/stdc++.h>

struct node_t{
	// node attributes.
	int height; 								
	int size;

	// repeated elements will have only one node
	int count;									
	
	// data to be stored in node.
	void *data; 								
	
	// pointers to children and parent.
	struct node_t *left;  						
	struct node_t *right; 						
	struct node_t *parent;						

};

typedef struct node_t node;



class Avl_tree{

	node *root;

	// If this flag is set tree will contain unique elements.
	bool unique_nodes;

	// compare function should be passed to compare node's data.
	int (*compare_function)(void*,void*);
	/* 	Comparator function should follow this rule.
		int compare(a,b){
			if(a==b) return 0;
			if(a>b) return 1;
			if(a<b) return -1;
		}
	*/



	void (*print_node_function)(node*);
	/*	custom print_node function should be passed,
		so that you can print your node's attributes and node's
	 	data in desired manner. If passed NULL insted will print only 
	 	node address by default.
	*/
					
	
	void (*delete_data_function)(void*);
	/*	pass your own node's data deletion function
		this will be called every time a node is begin 
		deleted from tree, to free memory occupied by node->data.
	*/

	
public:
	/* 	Constructor takes input comparator function,  
		node_printer function and
		node's data deleter function.
	*/
	Avl_tree(	int (*comparator_fun)(void*,void*), 
			void (*delete_data_fun)(void*),
			void (*print_node_fun)(node*)
		);
	
	// insert the data into tree.
	void insert_data(void *data);

	// delete the node containing data passed.
	void delete_data(void *data);

	// find node for a data.
	node* find_node(void *data);

	// prints inorder traversal of this tree.
	void inorder_traversal();
	
	// find the rank of a node containing data in tree.
	// if nodes were in an sorted array what would have been its rank.
	int rank(void *data);

	// returns tree size.
	int size();

	// set unique_nodes flag.
	void set_unique_nodes(bool);

private:
	// delete node from tree.
	void delete_node(node *nod);

	// insert data using root node of tree.
	node* insert_node(node *nod, void *data, node *parent);

	// balance the tree at a given node.
	node* balance(node *nod);

	// left rotate tree wrt a node.
	node* left_rotate(node* nod);

	// right rotate tree wrt a node.
	node* right_rotate(node* nod);

	// update node attributes like height and size.
	void update_node_attributes(node *nod);

	// inorder_traversal of this tree.
	void inorder(node *nod);
	
};
