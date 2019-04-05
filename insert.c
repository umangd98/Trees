#include<stdio.h>
#include<stdlib.h>

typedef struct Tree_tag
{
	int height; 
	int data;
	struct Tree_tag *left, *right;
}node;


int height(node *t)
{
	if(t==NULL)
	{
		return 0;
	}	
	return t->height;
}
int max(int a, int b)
{
	return (a>b)? a : b;
}
node* newNode(int data)
{
	node *new = (node*)malloc(sizeof(node));
	new->data = data;
	new->height=1;
	new->right=NULL;
	new->left=NULL;
	return new;
}
node* rightRotate(node *t2)
{
	node *t1=NULL;
	t1 = t2->left;
	t2->left = t1->right;
	t1->right = t2;
	t2->height = max(height(t2->left), height(t2->right))+1;
	t1->height = max(height(t1->left), height(t1->right))+1;
	return t1;
}

node* leftRotate(node *t2)
{
	node *t1=NULL;
	t1 = t2->right;
	t2->right = t1->left;
	t1->left = t2;
	t2->height = max(height(t2->left), height(t2->right))+1;
	t1->height = max(height(t1->left), height(t1->right))+1;
	return t1;
}

node* leftRightRotate(node *t)
{
	t->left = leftRotate(t->left);
	t = rightRotate(t);
	return t;
}

node* rightLeftRotate(node *t)
{
	t->right = rightRotate(t->right);
	t = leftRotate(t);
	return t;
}

int balance(node *t)
{
	if(t==NULL)
		{return 0;}
	return(height(t->left) - height(t->right));
}

node* insert(node *root, int key)
{
	if(root==NULL)
	{
		return(newNode(key));
	}
	else if(root->data>key)
	{
		root->left = insert(root->left,key);
	}
	else if(root->data<key)
	{
		root->right = insert(root->right,key);
	}
	else
	{
		return root;
	}
	root->height = 1 + max(height(root->left), height(root->right));
	int bal = balance(root);
	// printf("%d\n",bal);
	if(bal>1)
	{
		if(key<root->left->data)
		{
			root = rightRotate(root);
		}
		else
		{
			root = leftRightRotate(root);
		}
	}
	if(bal<-1)
	{
		if(key>root->right->data)
		{
			// printf("Reached rotate left\n");
			root = leftRotate(root);
		}
		else
		{
			root = rightLeftRotate(root);
		}
	}
	return root;
}

node* delete(node *root, int key)
{
	if(root==NULL)
	{
		return root;
	}
	else if(key<root->data)
	{
		root->left = delete(root->left, key);
	}
	else if(key>root->data)
	{
		root->right = delete(root->right, key);
	}
	else
	{
		node *t=root,*q;
		if(t->left==NULL)
		{
			root=t->right;
			free(t);
		}
		else if(t->right==NULL)
		{
			root = t->left;
			free(t);
		}
		else
		{
			for(q=t->right;q->left;q=q->left);
			q->left=t->left;
			root=t->right;
			free(t);
		}
	}
	root->height = 1 + max(height(root->left), height(root->right));
	int bal = balance(root);
	if(bal>1)
	{
		if(balance(root->left)>=0)
		{
			root = rightRotate(root);
		}
		else
		{
			root = leftRightRotate(root);
		}
	}
	if(bal<-1)
	{
		if(balance(root->right)<=0)
		{
			root = leftRotate(root);
		}
		else
		{
			root = rightLeftRotate(root);
		}
	}
	return root;
}

void preOrder(node *t)
{
	if(!t)
		return;
	else
	{
		printf("%d\n",t->data);
	}
	preOrder(t->left);
	preOrder(t->right);
}

main()
{
	node *root = NULL;
   root = insert(root, 9); 
    root = insert(root, 5); 
    root = insert(root, 10); 
    root = insert(root, 0); 
    root = insert(root, 6); 
    root = insert(root, 11); 
    root = insert(root, -1); 
    root = insert(root, 1); 
    root = insert(root, 2); 
	printf("preOrder traversal of AVL tree is:\n");
	preOrder(root);
	root = delete(root,10);
	printf("PreOrder Traversal after deletion of 10 \n");
	preOrder(root);
}