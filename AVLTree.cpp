

#include<iostream>
#include<pthread.h>
#include"AVLTree.h"

using namespace std;
using namespace mylib;

AVLTree::AVLTree()
{
    t=NULL;
}

AVLTree::~AVLTree()
{
    del();
}

void AVLTree::del()
{
   pthread_mutex_lock(&lock);
   del_(t);
   pthread_mutex_unlock(&lock);
}

void AVLTree::del_(struct Node *t)
{
    if(t==NULL) return;
    del_(t->left);
    del_(t->right);
    delete(t);
}


	
void AVLTree::createTree(char *file)
{
	pthread_mutex_lock(&lock);
	fstream f;
	f.open (file);
	string s,s1;
	while(f)
	{
		getline(f,s);
		s1=s;
		char *key=strtok(&s1[0],", ");
		if(s!="") t=insert(t,key,s);
	}
	pthread_mutex_unlock(&lock);
	
}

struct Node * AVLTree:: insert(struct Node *t,string key,string tuple)
{
    if(t==NULL)
    {
        t=new Node;
	t->key = key;
	char *tok=strtok(&tuple[0],", ");
	int i=0;
	while(tok!=NULL)
	{
            t->tuple[i++]=tok;
	    //cout<<t->tuple[i-1]<<endl;
            tok=strtok(NULL,", ");
	}
	t->left=NULL;
	t->right=NULL;
	t->height=1;
	return t;
    }
    char *a=&key[0];
    char *b=&t->key[0];
    if(key<t->key)//if(strcmp(a,b)<0)
    {
        t->left=insert(t->left,key,tuple);
    }  
    else if (key>t->key)//else if( strcmp(a,b)>0)
    {
	t->right=insert(t->right,key,tuple);
    }
    else return t;
    t->height=1+max(height(t->left),height(t->right));
    int balance = getBalance(t);
    // cout<<balance<<" <- balance "<<endl;

    if (balance > 1 && key < t->left->key)
    return rightRotate(t);

    if (balance < -1 && key > t->right->key)
    return leftRotate(t );

    if (balance > 1 && key >t->left->key)
    {
        t->left = leftRotate(t->left);
	return rightRotate(t);
    }
    if (balance < -1 && key < t->right->key)
    {
	t->right = rightRotate(t->right);
	return leftRotate(t);
    }
    return t;
}


struct Node * AVLTree::getRootNode()
{
    return t;   
}

void AVLTree:: preorder(struct Node *t)
{
    if(t!=NULL)
    {
        cout<<t->tuple[0]<<" "<<t->tuple[1]<<" "<<t->tuple[2]<<" "<<t->tuple[3]<<" height"<<t->height<<"\n";
        preorder(t->left);
	preorder(t->right);
    }

}


void AVLTree:: postorder(struct Node *t)
{
    if(t!=NULL)
    {
        postorder(t->left);
	postorder(t->right);
	cout<<t->tuple[0]<<" "<<t->tuple[1]<<" "<<t->tuple[2]<<" "<<t->tuple[3]<<"  height"<<t->height<<"\n";
    }
}


void AVLTree:: inorder(struct Node *t)
{
    if(t!=NULL)				       
    {
	inorder(t->left);
	cout<<t->tuple[0]<<" "<<t->tuple[1]<<" "<<t->tuple[2]<<" "<<t->tuple[3]<<" height"<<t->height<<"\n";
	inorder(t->right);
    }
}



int AVLTree:: height(struct Node *t)
{
   
    if(t==NULL) return 0;
    else return t->height;
   
}



int AVLTree:: getBalance(struct Node *t)
{

    if(t==NULL) return 0;	
    else return height(t->left)-height(t->right);	

}



struct Node * AVLTree:: rightRotate(struct Node *y)
{

    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
  
}



struct Node * AVLTree:: leftRotate(struct Node *x)
{

    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
  
}





string AVLTree:: search(struct Node *t,string key)
{
    while(t!=NULL)			      
    {
        if(key<t->key)
	{
	    return search(t->left,key);
	}
	else if(key>t->key)
	{
	    return search(t->right,key);
	}
	else return "query: "+t->tuple[0]+"\ntype: "+t->tuple[1]+"\nttl: "+t->tuple[2]+"\nIPaddr: "+t->tuple[3];
    }
    return "not found";
}

