#ifndef AVL_TREE_H
#define AVL_TREE_H





#include<bits/stdc++.h>
#include<cstring>
#include<iostream>
#include<pthread.h>

using namespace std;

namespace mylib
{

    struct Node 
    {
	string key;

	string tuple[4];

	Node *left;

	Node *right;

	int height;
    };
    class AVLTree
    {
	private:        

    	    struct Node * t;

	    pthread_mutex_t lock;

	    void del_(struct Node *t);

	    struct Node *rightRotate(struct Node *y);

	    struct Node *leftRotate(struct Node *x);

	    struct Node * insert(struct Node *t,string key,string tuple);

   	    int height(struct Node *t);

	    int getBalance(struct Node *t);

	public:

	    AVLTree();

	    ~AVLTree();

	    void del();

	    struct Node *getRootNode();

	    void createTree(char *file);

	    void preorder(struct Node *t);
	
	    void postorder(struct Node *t);

	    void inorder(struct Node *t);

  	    string search(struct Node *t,string key);

	};

}

#endif



