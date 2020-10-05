#pragma once
#include <string>
#include <iostream>

#ifndef BINARYTREE
#define BINARYTREE

template< class T >
class BinaryTreeCPP;

template< class T >
class BinaryTreeNode
{

friend class BinaryTreeCPP<T>; //forward declaration

private:
	//\\\\\\\\\\\\\\\\\\\\\ Essential Methods\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
	BinaryTreeNode() : Right(nullptr), Left (nullptr) {}; 
	BinaryTreeNode(T data) : Right(nullptr), Left (nullptr)
	{ 
		Data = data; 	
	}

	//Destruction is handled by Binary Tree.
	//Copy Constructor and Assignment operator are not needed, because only Binary Tree has access.
	//We don't use assignment or copying in the actual binary tree.

	//\\\\\\\\\\\\\\\\\\\\\\\\ Operator Overloads\\\\\\\\\\\\\\\\\\\\\\\\\//
	bool operator>( BinaryTreeNode<T>& lhs)
	{
		if (this->Data > lhs.Data)
		{
			return true;
		}

		return false;
	}

	bool operator<(BinaryTreeNode<T>& lhs)
	{
		if (this->Data < lhs.Data)
		{
			return true;
		}

		return false;
	}

	bool operator==(BinaryTreeNode<T>& lhs)
	{
		if (this->Data == lhs.Data)
		{
			return true;
		}

		return false;
	}

	//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
	void SetRight(BinaryTreeNode<T>* right)
	{
		Right = right;
	}

	void SetLeft(BinaryTreeNode<T>* left)
	{
		Left = left;
	}

	void SetData(T data)
	{
		Data = data;
	}
	//getters are not wanted because BinaryTree is a friend. No other class should have access.



private:
	BinaryTreeNode<T>* Right;
	BinaryTreeNode<T>* Left;
	T Data;

};


template< class T >
class BinaryTreeCPP
{

public:
	BinaryTreeCPP() : Size(0) { } //Default Constructor
	BinaryTreeCPP(T data) : Size(1)
	{
		Head = new BinaryTreeNode<T>(data);
	}

	BinaryTreeCPP(const BinaryTreeCPP<T>& ref) //Copy Constructor
	{
		//Pre order traversal	
		T* list = new T[ref.Size];
		int i = 0;
		PreOrder(ref.Head, list, i);

		//iterate through traversal and copy data into new tree
		for (int i = 0; i < ref.Size; i++)
		{
			//creates the head if there isn't one.
			//also increments size for each element added.

			Add(list[i]); 		
		}
		
		//deallocate the list
		delete[] list;
		
	}

	~BinaryTreeCPP()
	{
		ClearTree(Head);
		Head = nullptr;
		Size = 0;
	}

	
	BinaryTreeCPP<T> operator=(BinaryTreeCPP<T> rhs) //Copy Constructor is called implicitly 
	{		
		//Swap pointers with the copy. Copy gets deleted at the end of the function.
		Swap(*this, rhs);

		return *this;
	}

	//could do this recursively, but don't need to
	bool Add(T data)
	{
		BinaryTreeNode<T>* item = new BinaryTreeNode<T>(data);
		//create the item to add

		BinaryTreeNode<T>* curElement = Head;

		while (curElement)
		{
			if (*curElement > *item)
			{
				//go to the left.
				if (curElement->Left)
				{
					curElement = curElement->Left;
				}
				else
				{
					Size++;
					curElement->SetLeft(item);
					return true;
				}
			}
			else if (*curElement < *item)
			{
				//go right
				if (curElement->Right)
				{
					curElement = curElement->Right;
				}
				else
				{
					Size++;
					curElement->SetRight(item);
					return true;
				}
				
			}
			else
			{
				//don't add
				delete item;
				return false;
			}
		}

		//if here, then there was no head for the list.
		Head = item;
		Size++;

		item = nullptr;
		return true;
	}

	//used by external classes, calls our private version to hide BinaryTreeNode.
	void PreOrder()
	{
		PreOrder(Head);		
	}

	void InOrder()
	{
		InOrder(Head);
	}

	void PostOrder()
	{
		PostOrder(Head);
	}
	

private:

	int Size;
	BinaryTreeNode<T>* Head;

	//swap the heads of two binary trees. used in in assignment overload.
	void Swap(BinaryTreeCPP<T>& one, BinaryTreeCPP<T>& two)
	{
		BinaryTreeNode<T>* temp = one.Head;

		one.Head = two.Head;
		two.Head = temp;

		temp = nullptr; //not sure if necessary
	}



	//this version is called by the external class PreOrder call.
	void PreOrder(BinaryTreeNode<T>* node)
	{
		if (node)
			std::cout << node->Data << " ";
		else
			return;

		PreOrder(node->Left);
		PreOrder(node->Right);
	}

	void InOrder(BinaryTreeNode<T>* node)
	{
		
		
		if (node)
		{
			InOrder(node->Left);

			std::cout << node->Data << " ";

			InOrder(node->Right);
		}			
		else
			return;
			
	}

	void PostOrder(BinaryTreeNode<T>* node)
	{
		if (node)
		{
			PostOrder(node->Left);
			PostOrder(node->Right);
			
			std::cout << node->Data << " ";
		}		
		else
			return;
	}


	//potential failure. Not checking if index is valid for outList size.
	//this version of PreOrder is called by the copy constructor to get a copy of all the entries.
	void PreOrder(BinaryTreeNode<T>* node, T*& outList, int& index)
	{
		if (node)
		{			
			outList[index] = node->Data;
			index++;
		}
		else
			return;

		PreOrder(node->Left, outList, index);
		PreOrder(node->Right, outList, index);
	}









	//called by the destructor. performs an post order traversal delete
	void ClearTree(BinaryTreeNode<T>* node)
	{
		if (node)
		{
			ClearTree(node->Left);
			ClearTree(node->Right);

			delete node;			
		}
		else
		{
			return;
		}
	}
	

};




#endif // !BINARYTREE
