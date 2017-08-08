#include"avl_tree.h"

using namespace std;

#ifdef DEBUG
	#define DEBUG_LVL DEBUG
#else
	#define DEBUG_LVL 0
#endif


/* Heighest Debug Level */
#define TREE_CONSTRUCTION 1
#define INFO 2
/* Lowest Debug Level */



static void print_node_addr(node *nod){
	printf("node = %p\n",nod);
}


Avl_tree::Avl_tree(	int (*comparator_fun)(void*,void*), 
					void (*delete_data_fun)(void*),
					void (*print_node_fun)(node*)
		){
	// Initialise root to NULL.
	root = NULL;

	// Set the compare function passed as and argument.
	compare_function = comparator_fun;

	// Set the node printer function.
	// If NULL is passed default will be print_node_addr.
	print_node_function = print_node_fun;

	// Set node's data deleter function.
	delete_data_function = delete_data_fun;

	// By default unique_nodes flag is set to false to insert repeated elements.
	unique_nodes = false;

}

Avl_tree::Avl_tree( 	int (*comparator_fun)(void*,void*),
			void (*delete_data_fun)(void*)
		){
	Avl_tree(comparator_fun,delete_data_fun,print_node_function);
}

int Avl_tree::size(){
	return root?root->size:0;
}

void Avl_tree::set_unique_nodes(bool b){
	unique_nodes = b;
}

int Avl_tree::rank(void *data){
	node *temp = root;
	int sum = 0;
	while(temp){
		int result  = compare_function(data,temp->data);
		if(result == 0){
			sum += temp->left?temp->left->size:0;
			return sum;
		}
		else if(result > 0){
			sum += temp->left?temp->left->size+temp->count:temp->count;
			temp = temp->right;
		}
		else temp = temp->left;
	}

	return sum;
}

void Avl_tree::insert_data(void *data){

	// If first insertion in tree initialise root of tree.
	if(root == NULL){
		root = (node*)malloc(sizeof(node));
		root->parent = NULL;
		root->left = NULL;
		root->right = NULL;
		root->data = data;
		root->size = 1;
		root->height = 1;
		root->count = 1;
	}	
	else root = insert_node(root,data,root->parent);
}

node* Avl_tree::insert_node(node *nod, void *data, node *parent){
	// If first insertion in tree initialise root of tree.
	if(nod == NULL){
		nod = (node*)malloc(sizeof(node));
		nod->parent = parent;
		nod->left = NULL;
		nod->right = NULL;
		nod->data = data;
		nod->size = 1;
		nod->height = 1;
		nod->count = 1;
		return nod;
	}

	int result = compare_function(data,nod->data);
	if(result < 0){
		// data is <= current node data
		// insert it in left subtree.
		nod->left = insert_node(nod->left,data,nod);
	}
	else if(result > 0){
		// data is > current node data
		// insert it in right subtree.
		nod->right = insert_node(nod->right,data,nod);
	}
	else{
		// repeated element encounterd.
		// If unique_nodes flag is set don't insert.
		if(unique_nodes){
#if (DEBUG_LVL <= INFO)
			printf("Node already exists, not inserting..\n");
			print_node_function(nod);
#endif
		}
		else nod->count++;

	}
	
	// Update current node attributes...
	update_node_attributes(nod);

	// If tree is unbalanced then balance it.
	int left_height =  nod->left?nod->left->height:0;
	int right_height = nod->right?nod->right->height:0;
	
	if(abs(left_height-right_height) > 1){
#if (DEBUG_LVL <= TREE_CONSTRUCTION)
		printf("Tree unbalanced at node\n");
		print_node_function(nod);
#endif
		nod = balance(nod);
	}

	return nod;

}


void Avl_tree::delete_data(void *data){
	node *nod = find_node(data);
	if(nod){
		if(nod->count == 1) delete_node(nod);
		else{
			nod->count--;
			while(nod){
				update_node_attributes(nod);
				nod = nod->parent;
			}
		
		}

	}
	else{
#if (DEBUG_LVL <= INFO)
		printf("Delete Failed. Node not found.\n");
#endif
	}
}


void Avl_tree::delete_node(node *nod){
	node *balancing_node = NULL;

	// If nod is a leaf node, delete it and balance up the tree.
	if(nod->left == NULL && nod->right == NULL){
		balancing_node = nod->parent;
		
		// If 'nod' is the root node of tree then its parent is NULL.
		// Tree will be empty after deletion. Set root to NULL.
		if(balancing_node != NULL){
			if(balancing_node->left == nod) balancing_node->left = NULL;
			else balancing_node->right = NULL;
		}
		else{
			root = NULL;
		}
		delete_data_function(nod->data);
		free(nod);
	}


	if(nod->left == NULL && nod->right != NULL){
		balancing_node = nod->parent;

		// If this is the root node, set root to  nod->right.
		if(balancing_node != NULL){
			if(balancing_node->left == nod) balancing_node->left = nod->right;
			else balancing_node->right = nod->right;
			nod->right->parent = balancing_node;
	  	}
		else{
			root = nod->right;
			nod->right->parent = NULL;
		}
		delete_data_function(nod->data);
		free(nod);
	}
	if(nod->left != NULL && nod->right == NULL){
		balancing_node = nod->parent;

		// If this is the root node, set root to  nod->left.
		if(balancing_node != NULL){
			if(balancing_node->left == nod) balancing_node->left = nod->left;
			else balancing_node->right = nod->left;
			nod->left->parent = balancing_node;
	  	}
		else{
			root = nod->left;
			nod->left->parent = NULL;
		}
		delete_data_function(nod->data);
		free(nod);
	}
	if(nod->left != NULL && nod->right != NULL){
		// Replace the current node with largest element in left subtree/
		// Go to left then continuing going right.

		node *temp = nod->left;
		while(temp->right) temp = temp->right;

		// This temp node data will be swapped with 'nod' node data,
		// then temp will be deleted.
		balancing_node = temp->parent;
		if(balancing_node->left == temp) balancing_node->left = temp->left;
		else balancing_node->right = temp->left;
		
		if(temp->left) temp->left->parent = balancing_node;

		// Swap temp->data with nod->data, and delete temp node.
		delete_data_function(nod->data);
		nod->data = temp->data;
		nod->count = temp->count;
		free(temp);
	}

	// Now balance recursively up the tree.
	while(balancing_node){
		update_node_attributes(balancing_node);
		int left_height = balancing_node->left?balancing_node->left->height:0;
		int right_height = balancing_node->right?balancing_node->right->height:0;
		if(abs(left_height-right_height) > 1) 
			balance(balancing_node);
		balancing_node = balancing_node->parent;
	}
}

void Avl_tree::update_node_attributes(node *nod){
	// Updates height and size of node based on children.
	int left_height = nod->left?nod->left->height:0;
	int right_height = nod->right?nod->right->height:0;
	nod->height = max(left_height,right_height)+1;

	int left_size = nod->left?nod->left->size:0;
	int right_size = nod->right?nod->right->size:0;
	nod->size = left_size + right_size + nod->count;
}

node* Avl_tree::find_node(void *data){
	// if node containing data not found return NULL.
	node *temp = root;
	while(temp != NULL){
		int result = compare_function(data,temp->data);
		if(result == 0) return temp;
		else if(result < 0) temp = temp->left;
		else if(result > 0) temp = temp->right;
	}
	return NULL;
}


node* Avl_tree::right_rotate(node *nod){
#if (DEBUG_LVL <= TREE_CONSTRUCTION)
	printf("Right rotating node..\n");
	print_node_function(nod);
#endif
	node *parent = nod->parent;
	node *nod_left = nod->left;
	node *nod_left_right = nod->left->right;

	nod_left->right = nod;
	nod->left = nod_left_right;

	nod->parent = nod_left;
	nod_left->parent = parent;
	if(nod_left_right) nod_left_right->parent = nod;
	

	// If this is not root.
	if(parent != NULL){
		if(parent->left == nod)	parent->left = nod_left;
		else parent->right = nod_left;
	}
	else{
		root = nod_left;
	}


	// Now update the node attributes recursively till top.
	while(nod){
		update_node_attributes(nod);
		nod = nod->parent;
	}
	
	return nod_left;

}

node* Avl_tree::left_rotate(node *nod){
#if (DEBUG_LVL <= TREE_CONSTRUCTION)
	printf("Left rotating node...\n");
	print_node_function(nod);
#endif
	node *parent = nod->parent;
	node *nod_right = nod->right;
	node *nod_right_left = nod->right->left;

	nod_right->left = nod;
	nod->right = nod_right_left;
	
	nod->parent = nod_right;
	nod_right->parent = parent;
	if(nod_right_left) nod_right_left->parent = nod;

	// If this is not root.
	if(parent != NULL){
		if(parent->left == nod) parent->left = nod_right;
		else parent->right = nod_right;
	}
	else{
		root = nod_right;
	}

	// Now Update the node attributes recursively till top.
	while(nod){
		update_node_attributes(nod);
		nod = nod->parent;
	}

	return nod_right;

}



node* Avl_tree::balance(node *nod){
	/* 	There are 4 cases
		1. left-left case:
				nod->left->height is greater and nod->left->left->height is greater
				=> right rotate nod;

		2. left-right case:
				nod->left->height is greater and nod->left->right->height is greater
				=> left rotate nod->left and right rotate nod;
		
		3. right-right case:
				nod->right->height is greater and nod->right->right->height is greater
				=> left rotate nod;
		
		4. right-left case:
				nod->right->height is greater and nod->right->left->height is greater
				=> right rotate nod->right and left rotate nod;
	*/
	
	int nod_left_height = nod->left?nod->left->height:0;
	int nod_right_height = nod->right?nod->right->height:0;
	if(nod_left_height > nod_right_height){
		// It may be left-left case or left-right case
		int nod_left_left_height = nod->left->left?nod->left->left->height:0;
		int nod_left_right_height = nod->left->right?nod->left->right->height:0;
		if(nod_left_left_height > nod_left_right_height){
			// This is left-left case:
			return right_rotate(nod);
		}
		else{
			// This is left-right case:
			left_rotate(nod->left);
			return right_rotate(nod);
		}
	}
	else{
		// It may be righ-right case or right-left cases
		int nod_right_right_height = nod->right->right?nod->right->right->height:0;
		int nod_right_left_height = nod->right->left?nod->right->left->height:0;
		if(nod_right_right_height > nod_right_left_height){
			// This is right-right case:
			return left_rotate(nod);
		}
		else{
			// This is right-left case:
			right_rotate(nod->right);
			return left_rotate(nod);
		
		}
	}

}



void Avl_tree::inorder(node *nod){
	if(nod == NULL) return;
	inorder(nod->left);
	int n = nod->count;
	while(n--)
		print_node_function(nod);
	inorder(nod->right);
}


void Avl_tree::inorder_traversal(){
	printf("Inorder traversal...\n");
	inorder(root);
}




