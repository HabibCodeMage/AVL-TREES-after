#pragma once
#ifndef AVL_H
#define AVL_H
#include<stddef.h>
#include<iostream>
#include"deque.h"
using namespace std;
template<typename T>
class AVL
{
private:
	struct node
	{
		T value;
		node* right;
		node* left;
		node* parent;
	};
private:
	void rotatewithleftchildoflefttree(node*& t) //left subtree of left child of alpha node
	{
		node* kl = t->left;
		t->left = kl->right;
		if(kl->right)
		{
			kl->right->parent = t;
		}
		kl->parent = t->parent;
		t->parent = kl;
		kl->right = t;
		t = kl;
	}
	void rotatewithrightchildofrighttree(node*& t)//right subtree ofright child rr
	{
		node* kl = t->right;
		t->right = kl->left;
		if (kl->left)
		{
			kl->left->parent = t;
		}
		kl->parent = t->parent;
		t->parent = kl;
		kl->left = t;
		t = kl;
	}
	void rotatewithleftsubtreechildofrightchild(node*& t)// leftsubtrre of right child of alpha
	{
		rotatewithleftchildoflefttree(t->right);
		rotatewithrightchildofrighttree(t);
	}
	void rotaterightsubtreeofleftchild(node*& t)
	{
		rotatewithrightchildofrighttree(t->left);
		rotatewithleftchildoflefttree(t);
	}
private:
	void preorder(node* ptr)
	{
		if (ptr)
		{
			cout << ptr->value << endl;
			if (ptr->left)
				preorder(ptr->left);
			if (ptr->right)
				preorder(ptr->right);
		}
	}
	void inorder(node* ptr)
	{
		if (ptr)
		{

			if (ptr->left)
				inorder(ptr->left);
			cout << ptr->value << endl;
			if (ptr->right)
				inorder(ptr->right);
		}
	}
	void postorder(node* ptr)
	{
		if (ptr)
		{

			if (ptr->left)
				postorder(ptr->left);
			if (ptr->right)
				postorder(ptr->right);
			cout << ptr->value<<endl;
		}
	}
private:
	node* root;
	void insert(node*& nodeptr, node*& newnode, node* parent)
	{
		if (nodeptr == NULL)
		{
			nodeptr = newnode;
			nodeptr->parent = parent;
		}
		else if (newnode->value < nodeptr->value)
		{
			insert(nodeptr->left, newnode, nodeptr);
			if (!(isbalance(position{ nodeptr })))
			{
				if (newnode->value < nodeptr->left->value)
				{
				   rotatewithleftchildoflefttree(nodeptr);
				}
				else
				{
					rotaterightsubtreeofleftchild(nodeptr);
				}
			}
			
		}
		else
		{
			insert(nodeptr->right, newnode, nodeptr);
			if (!(isbalance(position{ nodeptr })))
			{
				if (nodeptr->right->value < newnode->value)
					rotatewithrightchildofrighttree(nodeptr);
				else
					rotatewithleftsubtreechildofrightchild(nodeptr);
			}
		}
	}
	void makedeletion(node*& nodeptr)
	{
		node* temp;
		if (nodeptr->left == NULL && nodeptr->right == NULL)
		{
			if (nodeptr->parent->left == nodeptr)
			{
				nodeptr->parent->left = NULL;
			}
			else if (nodeptr->parent->right == nodeptr)
			{
				nodeptr->parent->right = NULL;
			}
			delete nodeptr;

		}
		else if (nodeptr->left == NULL)
		{
			temp = nodeptr;
			nodeptr = nodeptr->right;
			nodeptr->parent = temp->parent;
			delete temp;
		}
		else if (nodeptr->right == NULL)
		{
			temp = nodeptr;
			nodeptr = nodeptr->left;
			nodeptr->parent = temp->parent;
			delete temp;
		}
		else
		{
			temp = nodeptr->left;
			while (temp->right)
				temp = temp->right;
			nodeptr->value = temp->value;
			if (temp->parent->left == temp)
			{
				makedeletion(temp->parent->left);
			}
			if (temp->parent->right == temp)
			{
				makedeletion(temp->parent->right);
			}
		
		}
		
	}
	void balanceuptoroot(node*& parentvalue)
	{
		
		if (parentvalue == NULL)
			return;
		else
		{
			
			if (BF(position{ parentvalue }) == 2 && BF(position{ parentvalue->left }) == 1)
			{

				rotatewithleftchildoflefttree(parentvalue);

			}
			else if (BF(position{ parentvalue }) == 2 && BF(position{ parentvalue->right }) ==-1 )
			{

				rotaterightsubtreeofleftchild(parentvalue);

			}
			else if (BF(position{ parentvalue }) == 2 && BF(position{ parentvalue->right }) == 0)
			{
				rotatewithleftchildoflefttree(parentvalue);

			}
			else if (BF(position{ parentvalue }) == -2 && BF(position{ parentvalue->right }) == 1)
			{

				rotatewithleftsubtreechildofrightchild(parentvalue);

			}
			else if (BF(position{ parentvalue }) == -2 && BF(position{ parentvalue->right }) == -1)
			{
				rotatewithrightchildofrighttree(parentvalue);

			}
			else if (BF(position{ parentvalue }) == -2 && BF(position{ parentvalue->right }) == 0)
			{
				rotatewithrightchildofrighttree(parentvalue);

			}
		}
			
	}
	void deletenode(const T& value, node*& root)
	{
		if (root->value == value)
		{
			makedeletion(root);
		}
		else if (value < root->value)
		{
			deletenode(value, root->left);
			balanceuptoroot(root);
		}
		else
		{
			deletenode(value, root->right);
			balanceuptoroot(root);
		}
	}
	void deletsubtrees(node*& nodeptr)
	{
		if (nodeptr)
		{
			if (nodeptr->left != NULL)
				deletsubtrees(nodeptr->left);
			if (nodeptr->right != NULL)
				deletsubtrees(nodeptr->right);
			delete nodeptr;
			nodeptr = NULL;
		}
	}
	int depth(node* u)const
	{
		if (u == root)
			return 0;
		else
			return 1 + depth(u->parent);
	}
	int height(node* u)const
	{
		if (u == NULL)
			return -1;
		else
			return 1 + (height(u->left) > height(u->right) ? height(u->left) : height(u->right));
		/*if (u->left==NULL && u->right == NULL)
			return 0;
		else
		{
			int x = 0, y = 0;
			if (u->left != NULL)
				x = height(u->left);
			if (u->right != NULL)
				y = height(u->right);
			return 1 + (x > y ? x : y);
		}*/
	}
public:
	class position
	{
	private:
		node* v;
	public:
		position(node* u) :v(u)
		{}
		node* getfather()
		{
			return v->parent;
		}
		position left() const
		{
			return v->left;
		}
		position right() const
		{
			return v->right;
		}
		bool isexternal()
		{
			if (v->left == NULL && v->right == NULL)
				return true;
			return false;
		}
		bool isinternal()
		{
			return(v->left != NULL && v->right != NULL);
		}
		T& operator*()
		{
			return v->value;
		}
		friend class AVL;
	};
private:
  bool isbalance(const position& that) const
  {
	  
	  int bal=height(that.left()) - height(that.right());
	  return ((bal >= -1 && bal <= 1));
  }
  int BF(const position& that) const
  {

	  int bal = height(that.left()) - height(that.right());
	  return bal;
  }
public:
	AVL() :root(NULL)
	{}
	void insert(const T& value)
	{
		node* newnode = new node{ value };
		newnode->left = newnode->right = NULL;
		insert(root, newnode, NULL);
	}
	bool searchnode(const T& value)
	{
		node* traverse = root;
		while (traverse)
		{
			if (traverse->value == value)
				return true;
			else if (value < traverse->value)
				traverse = traverse->left;
			else
				traverse = traverse->right;
		}
		return false;
	}
	void removenode(const T& value)
	{
		if (root == NULL)
			throw"EMPTY TREE";
		if (!searchnode(value))
			throw"GIVEN VALUE NOT EXIST";
		deletenode(value, root);

	}
	void preorder(const position& ptr)
	{
		preorder(ptr.v);
	}
	void inorder(const position& ptr)
	{
		inorder(ptr.v);
	}
	void postorder(const position& ptr)
	{
		postorder(ptr.v);
	}
	 position Root()
	{
		return position(root);
	}
	int height(const position& obj) const
	{
		return height(obj.v);
	}
	int depth(const position& obj) const
	{
		return depth(obj.v);
	}
	void bredthfirst(const position& obj)
	{
		deque<node*> object;
		object.insertback(obj.v);
		while (!object.empty())
		{
			cout << object.front()->value<< endl;
			if (object.front()->left != NULL)
				object.insertback(object.front()->left);
			if (object.front()->right != NULL)
				object.insertback(object.front()->right);
			object.erasefront();
		}
	}
	~AVL()
	{
		deletsubtrees(root);
	}
};
#endif // !AVL_H