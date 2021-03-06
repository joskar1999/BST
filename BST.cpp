#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

struct BSTNode
{
	int key;
	BSTNode *left, *right, *top;
	int ratio;
};

class bst
{
private:

	void leftLeft(BSTNode * n)
	{
		BSTNode * x = n->left;
		BSTNode * y = n->top;
		n->left = x->right;
		if (n->left != NULL) n->left->top = n;
		x->right = n;
		x->top = y;
		n->top = x;
		if (y == NULL) root = x;
		else
		{
			if (y->left == n) y->left = x;
			else y->right = x;
		}
		if (x->ratio == 1)
		{
			n->ratio = 0;
			x->ratio = 0;
		}
		else
		{
			n->ratio = 1;
			x->ratio = -1;
		}
	}

	void rightRight(BSTNode * n)
	{
		BSTNode * x = n->right;
		BSTNode * y = n->top;
		n->right = x->left;
		if (n->right != NULL) n->right->top = n;
		x->left = n;
		x->top = y;
		n->top = x;
		if (y == NULL) root = x;
		else
		{
			if (y->right == n) y->right = x;
			else y->left = x;
		}
		if (x->ratio == -1)
		{
			n->ratio = 0;
			x->ratio = 0;
		}
		else
		{
			n->ratio = -1;
			x->ratio = 1;
		}
	}

	void rightLeft(BSTNode * n)
	{
		BSTNode * x = n->right;
		BSTNode * y = x->left;
		BSTNode * z = n->top;
		x->left = y->right;
		if (x->left != NULL) x->left->top = x;
		n->right = y->left;
		if (n->right != NULL) n->right->top = n;
		y->left = n;
		y->right = x;
		n->top = y;
		x->top = y;
		y->top = z;
		if (z == NULL) root = y;
		else
		{
			if (z->left == n) z->left = y;
			else z->right = y;
		}
		if (y->ratio == -1) n->ratio = 1;
		else n->ratio = 0;
		if (y->ratio == 1) x->ratio = -1;
		else x->ratio = 0;
		y->ratio = 0;
	}

	void leftRight(BSTNode * n)
	{
		BSTNode * x = n->left;
		BSTNode * y = x->right;
		BSTNode * z = n->top;
		x->right = y->left;
		if (x->right != NULL) x->right->top = x;
		n->left = y->right;
		if (n->left != NULL) n->left->top = n;
		y->right = n;
		y->left = x;
		n->top = y;
		x->top = y;
		y->top = z;
		if (z == NULL) root = y;
		else
		{
			if (z->left == n) z->left = y;
			else z->right = y;
		}
		if (y->ratio == 1) n->ratio = -1;
		else n->ratio = 0;
		if (y->ratio == -1) x->ratio = 1;
		else x->ratio = 0;
		y->ratio = 0;
	}

	BSTNode * MaxBST(BSTNode *n)
	{
		while (n->right != NULL) n = n->right;
		return n;
	}

	BSTNode * PredecessorBST(BSTNode * n)
	{
		BSTNode * x = NULL;
		if (n->left != NULL) return MaxBST(n->left);
		else
		{
			x = n->top;
			while (x != NULL && n == x->left)
			{
				n = x;
				x = x->top;
			}
			return x;
		}
	}

public:

	BSTNode * root;

	bst()
	{
		root = NULL;
	}

	void inorder(BSTNode * n)
	{
		if (n)
		{
			inorder(n->left);
			cout << n->key << "\t";
			inorder(n->right);
		}
	}

	void preorder(BSTNode * n)
	{
		if (n)
		{
			cout << n->key << "\t";
			preorder(n->left);
			preorder(n->right);
		}
	}

	void postorderDeletion(BSTNode *n)
	{
		if (n)
		{
			postorderDeletion(n->left);
			postorderDeletion(n->right);
			if(n != root) delete n;
			else root = NULL;
		}
	}

	void insertBST(int n)
	{
		BSTNode * cur, *tmp, *prev;
		bool isNotBalanced;
		cur = new BSTNode;       
		cur->left = NULL;
		cur->right = NULL; 
		cur->top = NULL;
		cur->key = n;
		cur->ratio = 0;
		tmp = root;              

		if (tmp == NULL) root = cur;
		else
		{                      
			while (true)
			{
				if (n < tmp->key)
				{
					if (tmp->left == NULL)
					{
						tmp->left = cur;
						break;
					}
					tmp = tmp->left;
				}
				else
				{
					if (tmp->right == NULL)
					{
						tmp->right = cur;
						break;
					}
					tmp = tmp->right;
				}
			}

			cur->top = tmp;

			if (tmp->ratio != 0) tmp->ratio = 0; 
			else
			{
				tmp->left == cur ? tmp->ratio = 1 : tmp->ratio = -1;
				prev = tmp->top;     
				isNotBalanced = false;
				while (prev)
				{
					if (prev->ratio != 0)
					{
						isNotBalanced = true;    
						break;       
					}
					prev->left == tmp ? prev->ratio = 1 : prev->ratio = -1;
					tmp = prev;      
					prev = prev->top;
				}

				if (isNotBalanced == true)          
				{               
					if (prev->ratio == 1)
					{
						if (prev->right == tmp) prev->ratio = 0;  
						else if (tmp->ratio == -1) leftRight(prev);
						else leftLeft(prev);
					}
					else
					{           
						if (prev->left == tmp) prev->ratio = 0;  
						else if (tmp->ratio == 1) rightLeft(prev);
						else rightRight(prev);
					}
				}
			}
		}
	}

	void route(int x)
	{
		BSTNode * current = root;
		while (current->key != x)
		{
			cout << current->key << "\t";
			if (x < current->key) current = current->left;
			else current = current->right;
		}
		printf_s("%d\t", current->key);
	}

	BSTNode * removeBST(BSTNode * n)
	{
		BSTNode  *tmp, *child, *prev;
		bool rotation;

		if (n->left != NULL && n->right != NULL)
		{
			child = removeBST(PredecessorBST(n));
			rotation = false;
		}
		else
		{
			if (n->left != NULL)
			{
				child = n->left; 
				n->left = NULL;
			}
			else
			{
				child = n->right; 
				n->right = NULL;
			}
			n->ratio = 0;
			rotation = true;
		}

		if (child != NULL)
		{
			child->top = n->top;
			child->left = n->left;  
			if (child->left != NULL)  child->left->top = child;
			child->right = n->right; 
			if (child->right != NULL)  child->right->top = child;
			child->ratio = n->ratio;
		}

		if (n->top != NULL) n->top->left == n ? n->top->left = child : n->top->right = child;
		else root = child;

		if (rotation == true)
		{
			prev = child;
			child = n->top;
			while (child != NULL)
			{
				if (child->ratio == 0)
				{
					child->left == prev ? child->ratio = -1 : child->ratio = 1;
					break;
				}
				else
				{
					if (((child->ratio == 1) && (child->left == prev)) || ((child->ratio == -1) && (child->right == prev)))
					{          
						child->ratio = 0;
						prev = child; 
						child = child->top;
					}
					else
					{
						child->left == prev ? tmp = child->right : tmp = child->left;
						if (tmp->ratio == 0)
						{        
							child->ratio == 1 ? leftLeft(child) : rightRight(child);
							break;
						}
						else if (child->ratio == tmp->ratio)
						{         
							child->ratio == 1 ? leftLeft(child) : rightRight(child);
							prev = tmp; 
							child = tmp->top;
						}
						else
						{         
							child->ratio == 1 ? leftRight(child) : rightLeft(child);
							prev = child->top; 
							child = prev->top;
						}
					}
				}
			}
		}
		return n;
	}

protected:
};

void randTable(int A[], int size)
{
	int r;
	vector<bool> tab(500000, false);
	for (int i = 0; i < size; i++)
	{
	label:
		r = (rand() * rand()) % 500000;
		if (tab[r] == false)
		{
			tab[r] = true;
			A[i] = r;
		}
		else goto label;
	}
}

int main()
{
	srand(time(NULL));
	int start, stop, *A;
	double time;
	bst bstTree;

	fstream file;
	file.open("wyniki2.txt", fstream::in | fstream::out | fstream::app);

	for (int i = 10000; i <= 10000; i += 10000)
	{
		A = new int[i];
		randTable(A, i);
		
		start = clock();

		for (int j = 0; j < i; j++)
		{
			bstTree.insertBST(A[j]);
		}

		stop = clock();
		time = double(stop - start) / 1000;
		file << "bst.insert: " << i << " time: " << time << endl;
		
		start = clock();

		for (int j = 0; j < i/10; j++)
		{
			bstTree.route(A[j]);
		}

		stop = clock();
		time = double(stop - start) / 1000;
		file << "bst.route: " << i/10 << " time: " << time << endl;

		start = clock();

		bstTree.postorderDeletion(bstTree.root);
		
		stop = clock();
		time = double(stop - start) / 1000;
		file << "bst.postorderDeletion: " << i << " time: " << time << endl;

		delete[] A;
	}

	file.close();
	return 0;
}
