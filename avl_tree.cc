/* Generic AVL Tree */
/* Author: Shailesh Kumar<sk38@iitbbs.ac.in> */

/* License
    Copyright (C) 2017 Shailesh Kumar

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include<bits/stdc++.h>

using namespace std;

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


static void print_node_addr(node*);


class Avl_tree{

	node *root;


	// compare function should be passed to compare node's data.
	int (*compare)(void*,void*);
	/* 	Comparator function should follow this rule.
		int compare(a,b){
			if(a==b) return 0;
			if(a>b) return 1;
			if(a<b) return -1;
		}
	*/



	void (*print_node)(node*);
	/*	custom print_node function should be passed,
		so that you can print your node's attributes and node's
	 	data in desired manner. If passed NULL insted will print only 
	 	node address by default.
	*/
					
	
	void (*delete_node_data)(void*);
	/*	pass your own node's data deletion function
		this will be called every time a node is begin 
		deleted from tree, to free memory occupied by node->data.
	*/

	
public:
	/* 	Constructor takes input comparator function,  
		node_printer function and
		node's data deleter function.
	*/
	Avl_tree(	int (*comp)(void*,void*), 
				void (*print_node)(node*), 
				void (*delete_node_data)(void*)
			);
	
	
	// insert the data into tree.
	void insert_data(void *data);

	// delete the node containing data passed.
	void delete_data(void *data);

	// find node for a data.
	node* find_node(void *data);

	// prints inorder traversal of this tree.
	void inorder_traversal();


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

Avl_tree::Avl_tree(	int (*comp)(void*,void*), 
					void (*print)(node*) = print_node_addr,
					void (*del)(void*) = free
				){
	// Initialise root to NULL.
	root = NULL;

	// Set the compare function passed as and argument.
	compare = comp;

	// Set the node printer function.
	// If NULL is passed default will be print_node_addr.
	if(print) print_node = print;
	else print_node = print_node_addr;

	// Set node's data deleter function.
	if(del) delete_node_data = del;
	else	delete_node_data = free;
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

	int result = compare(data,nod->data);
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
		nod->count++;
	}
	
	// Update current node attributes...
	update_node_attributes(nod);

	// If tree is unbalanced then balance it.
	int left_height =  nod->left?nod->left->height:0;
	int right_height = nod->right?nod->right->height:0;
	
	if(abs(left_height-right_height) > 1){
#ifdef DEBUG 
		printf("tree unbalanced at nod\n");
		print_node(nod);
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
	else printf("Delete Failed. Node not found.\n");
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
		delete_node_data(nod->data);
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
		delete_node_data(nod->data);
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
		

		// Swap temp->data with nod->data, and delete temp node.
		delete_node_data(nod->data);
		nod->data = temp->data;
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
		int result = compare(data,temp->data);
		if(result == 0) return temp;
		else if(result < 0) temp = temp->left;
		else if(result > 0) temp = temp->right;
	}
	return NULL;
}


node* Avl_tree::right_rotate(node *nod){
#ifdef DEBUG
	printf("right rotating node..\n");
	print_node(nod);
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
#ifdef DEBUG
	printf("left rotating node...\n");
	print_node(nod);
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
	print_node(nod);
	inorder(nod->right);
}


void Avl_tree::inorder_traversal(){
	printf("Inorder traversal...\n");
	inorder(root);
}


static void print_node_addr(node *nod){
	printf("node = %p\n",nod);
}








int my_comparator(void *p1, void *p2){
	int a1 = *(int*)p1;
	int a2 = *(int*)p2;
	if(a1 > a2) return 1;
	if(a1 == a2) return 0;
	if(a1 < a2) return -1;
}

void my_node_printer(node *nod){
	if(!nod){
		printf("NULL\n");
		return;
	}
	printf("data = %d, height = %d, size = %d, parent = %d\n",*(int*)(nod->data),
		nod->height,nod->size,nod->parent?*(int*)(nod->parent->data):-1);
}


void my_data_deleter(void *data){
	//TODO 
}

int main(){
	Avl_tree tree(&my_comparator,&my_node_printer);
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++){
		scanf("%d",a+i);
		printf("inserting %d\n",a[i]);
		tree.insert_data((void*)(a+i));
		
		tree.inorder_traversal();
		cout<<endl;
	}


	while(1){
		int n;
		cin>>n;
		tree.delete_data(&n);
		tree.inorder_traversal();
	}



}
