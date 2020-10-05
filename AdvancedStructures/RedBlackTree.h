#pragma once
#ifndef REDBLACK_H
#define REDBLACK_H

#include <iostream>
#include <string>

template< class T >
class RedBlackNode
{

template< class T >
friend class RedBlackTree;

public:
	RedBlackNode() : Parent(nullptr), Right(nullptr), Left(nullptr) {}
	RedBlackNode(T data) : Parent(nullptr), Right(nullptr), Left(nullptr)
	{
		Data = data;
		Red = true;
	}
	RedBlackNode(T data, RedBlackNode<T>* P) : Right(nullptr), Left(nullptr)
	{
		Data = data;
		Red = true;
		Parent = P;
	}


	T Data;
	bool Red;
	RedBlackNode<T>* Parent;
	RedBlackNode<T>* Right;
	RedBlackNode<T>* Left;
};



template< class T >
class RedBlackTree
{
public:
	RedBlackTree() : Root(nullptr), Size(0) {}
	RedBlackTree(T Data)
	{
		Root = new RedBlackNode(T);
		Size = 1;
	}
	
	RedBlackTree(const RedBlackTree<T>& ref) //Copy Constructor
	{
		Root = Copy(ref.Root);
		Size = ref.Size;
	}


	RedBlackTree<T> operator=(RedBlackTree<T> rhs) //Copy Constructor is called implicitly 
	{
		//Swap pointers with the copy. Copy gets deleted at the end of the function.
		Swap(*this, rhs);

		return *this;
	}
	
	virtual ~RedBlackTree()
	{
		std::cout << "destructing...\n";
		ClearTree(Root);
		Root = nullptr;
		Size = 0;
	}



	//The root of the tree must always be black.
	//handles
	//    B           B
	//      R   =>      R
	//    R               R
	//and returns the bottom R to be rebalanced.
	RedBlackNode<T>* SwapRight(RedBlackNode<T>* node)
	{
		RedBlackNode<T>* P = node->Parent;
		RedBlackNode<T>* GP = P->Parent;

		node->Parent = GP;
		GP->Right = node;

		if (node->Right)
		{
			P->Left= node->Right;
		}
		else
		{
			P->Left = nullptr;
		}

		node->Right = P;
		P->Parent = node;
		

		return P;
	}

	//handles
	//    B           B
	//   R   =>      R
	//    R         R      
	RedBlackNode<T>* SwapLeft(RedBlackNode<T>* node)
	{
		RedBlackNode<T>* P = node->Parent;
		RedBlackNode<T>* GP = P->Parent;

		node->Parent = GP;
		GP->Left = node;

		if (node->Left)
		{
			P->Right = node->Left;
			node->Left->Parent = P;
		}
		else
		{
			P->Right = nullptr;
		}

		node->Left = P;
		P->Parent = node;
		

		return P;
	}

	//handles
	//  B            B
	//    R   =>   R   R
	//      R
	RedBlackNode<T>* SingleRotateLeft(RedBlackNode<T>* node)
	{
		//node -> right becomes the new root
		//node becomes the left child of root
		//new root replaces the old as the parents child
		//left child of new root becomes the right child of node
		//invert the new parent's color to black

		//the node will have a parent always
		RedBlackNode<T>* GGP = nullptr;
		RedBlackNode<T>* GP = nullptr;
		RedBlackNode<T>* P = node->Parent;

		//if there is no GGP (the GP was the root, which has no P)
		if (node->Parent->Parent == Root)
		{
			std::cout << "Root swapping...\n";
			/////////////////////////////////////

			GP = Root;
		
			////////////////////////////////////

			//Shift the nodes
				
			if (P->Left)
			{
				GP->Right = P->Left;
				P->Left->Parent = GP;
			}
			else
			{
				GP->Right = nullptr;
			}
			
			P->Left = GP;			
			GP->Parent = P;

			P->Parent = nullptr;
			Root = P;
			///////////////////////////////////

			//Switch colors

			Root->Red = false;
			GP->Red = true;

			//////////////////////////////////

			return P;
		}
		//GGP exists
		else if (node->Parent->Parent->Parent)
		{
			std::cout << "GGP swapping...\n";
			GGP = node->Parent->Parent->Parent;
			GP = node->Parent->Parent;
			//////////////////////////////////////

			//if the parent has a left node
			//update the right node ptr for the GP, and set the new parent for P->left.

			if (P->Left)
			{
				//std::cout << "true\n";
				GP->Right = P->Left;
				P->Left->Parent = GP;
			}
			else
			{
				GP->Right = nullptr;
			}


			//Swap P->left with its parent
			P->Left = P->Parent;
			P->Left->Parent = P;

			//////////////////////////////////////

			//Change the GGP child to P, and P->parent to GGP.
			//First check if GP is a left or right child.
			bool isRight = true;
			if (GP->Data < GGP->Data)
			{
				isRight = false;
			}

			isRight ? GGP->Right = P : GGP->Left = P;
			P->Parent = GGP;

			///////////////////////////////////////
			
			//Swap colors where necessary (for P and GP)
			P->Red = false;
			GP->Red = true;

			Root->Red = false;
			//////////////////////////////////////
		
			//the new root of the three node combination is P.
			// GP               P
			//   P     =>    GP   N
			//     N

			return P;

			//////////////////////////////////////			
		}
		else
		{
			//a rotation is not possible if there is no GGP, or the root is not a GP.
			return nullptr;
		}
	}

	//handles
	//     B         B
	//   R    =>   R   R
 	// R
	RedBlackNode<T>* SingleRotateRight(RedBlackNode<T>* node)
	{
		//node -> right becomes the new root
		//node becomes the left child of root
		//new root replaces the old as the parents child
		//left child of new root becomes the right child of node
		//invert the new parent's color to black

		//the node will have a parent always
		RedBlackNode<T>* GGP = nullptr;
		RedBlackNode<T>* GP = nullptr;
		RedBlackNode<T>* P = node->Parent;

		//if there is no GGP (the GP was the root, which has no P)
		if (node->Parent->Parent == Root)
		{
			std::cout << "Root swapping...\n";
			/////////////////////////////////////

			GP = Root;

			////////////////////////////////////

			//Shift the nodes

			if (P->Right)
			{
				GP->Left = P->Right;
				P->Right->Parent = GP;
			}
			else
			{
				GP->Left = nullptr;
			}

			P->Right = GP;
			GP->Parent = P;

			P->Parent = nullptr;
			Root = P;
			///////////////////////////////////

			//Switch colors

			Root->Red = false;
			GP->Red = true;

			//////////////////////////////////

			return P;

		}
		//GGP exists
		else if (node->Parent->Parent->Parent)
		{
			std::cout << "GGP swapping...\n";
			GGP = node->Parent->Parent->Parent;
			GP = node->Parent->Parent;
			//////////////////////////////////////

			//if the parent has a left node
			//update the right node ptr for the GP, and set the new parent for P->left.

			if (P->Right)
			{
				//std::cout << "true\n";
				GP->Left = P->Right;
				P->Right->Parent = GP;
			}
			else
			{
				GP->Left = nullptr;
			}


			//Swap P->right with its parent
			P->Right = P->Parent;
			P->Right->Parent = P;

			//////////////////////////////////////

			//Change the GGP child to P, and P->parent to GGP.
			//First check if GP is a left or right child.
			bool isRight = true;
			if (GP->Data < GGP->Data)
			{
				isRight = false;
			}

			isRight ? GGP->Right = P : GGP->Left = P;
			P->Parent = GGP;

			///////////////////////////////////////

			//Swap colors where necessary (for P and GP)
			P->Red = false;
			GP->Red = true;

			Root->Red = false;
			//////////////////////////////////////

			//the new root of the three node combination is P.
			// GP               P
			//   P     =>    GP   N
			//     N

			return P;

			//////////////////////////////////////			
		}
		else
		{
			//a rotation is not possible if there is no GGP, or the root is not a GP.
			return nullptr;
		}
	}

	//handles
	//    B             R                             
	//  R   R     =>  B   B      
	//        R             R
	//Also handles the opposite case where the uncle is a right child
	void PushBlack(RedBlackNode<T>* node)
	{
		//node must have a GP for this to be called.

		RedBlackNode<T>* GP = node->Parent->Parent;

		//invert GP color.
		//invert P and Uncle

		GP->Right->Red = GP->Red;
		GP->Left->Red = GP->Red;

		GP->Red = !GP->Red;	

		Root->Red = false;
	}

	//Add the data into the tree.
	//Not recursive
	void Add(T data)
	{

		if (!Root)
		{
			Root = new RedBlackNode<T>(data);
			Root->Red = false;

			Size++;
		}

		RedBlackNode<T>* iter = Root;
		RedBlackNode<T>* P = iter->Parent;
		bool RightChild = false;

		while (iter)
		{
			if (data > iter->Data)
			{
				P = iter;
				iter = iter->Right;		
								
				RightChild = true;
			}
			else if (data < iter->Data)
			{
				P = iter;
				iter = iter->Left;				
				
				RightChild = false;
			}
			else
			{
				//data already contained
				return;
			}
		}

		//create the new node with the parent as the last valid element
		RedBlackNode<T>* newNode = new RedBlackNode<T>(data, P);
		RightChild ? P->Right = newNode : P->Left = newNode;
		Size++;

		
		//Check conditions for balancing and balance the tree accordingly.
		Balance(newNode);
	}

	/*this method checks multiple conditions on node.
	* PSUEDOCODE:
	*if node's parent is red, then a rebalance is required.
	*---if the node's parent is a right child:
	*------if the node is a right child:
	*---------if node's uncle is red:
	*------------push black down from grandparent
	*------------perform rebalance on grandparent
	*---------else (no uncle or black uncle):
	*------------single rotate left
	*------else (node is a left child):
	*---------swap node and node's parent
	*---------perform an SRL on parent
	*---else (parent is a left child)
	*------(the same stuff, but on a left child)...
	*/
	void Balance(RedBlackNode<T>* node)
	{
		//P = parent
		//GP = grandparent

		//the node we just added is inherently red.
		//any node that Balance is being called on is inherently red.

		RedBlackNode<T>* P = node->Parent;

		if (!P) { return;
		}
		RedBlackNode<T>* GP = P->Parent;

		if (!GP) { return; }

		//std::cout << P->Data << " " << GP->Data << " - Here\n";

		//New Node is inherently red
		if (P->Red)
		{
			
			//P is a right child
			if (P->Data > GP->Data)
			{
				//handles
				//   B
				// X   R
				//       R
				if (node->Data > P->Data)
				{
					//take advantage of Short circuit. Black GP and a red Uncle.
					if (!(GP->Red) && GP->Left && GP->Left->Red)
					{
						std::cout << "Push Black & Attempt Rebalance on GP\n";
						PushBlack(node);
						Balance(GP);
					}
					//no uncle, or black uncle
					else
					{
						//node is a right child. SRL
						if (node->Data > P->Data)
						{
							std::cout << "SRL\n";
							SingleRotateLeft(node);
						}
					}
				}
				//handles
				//    B
				//  X   R
				//     R
				else
				{
					std::cout << "Swap Right & Attempt Rebalance\n";
					Balance(SwapRight(node));
				}
				
			}
			//P is a left child
			else
			{
				//handles
				//    B
				//  R   X
				// R       
				if (node->Data < P->Data)
				{
					//take advantage of Short circuit. Black GP and a red Uncle.
					if (!(GP->Red) && GP->Right && GP->Right->Red)
					{
						std::cout << "Push Black & Attempt Rebalance on GP\n";
						PushBlack(node);
						Balance(GP);
					}
					//no uncle, or black uncle
					else
					{
						//node is a left child. SRL
						if (node->Data < P->Data)
						{
							std::cout << "SRR\n";
							SingleRotateRight(node);
						}
					}
				}
				//handles
				//    B
				//  R   X
				//   R
				else
				{
					std::cout << "Swap Left & Attempt Rebalance\n";
					Balance(SwapLeft(node));
				}
			}
		}


	}

	void PreOrder()
	{
		PreOrder(Root);
	}

	//this version is called by the external class PreOrder call.
	void PreOrder(RedBlackNode<T>* node)
	{
		if (node)
			std::cout << node->Data << "-" << node->Red << " ";
		else
			return;

		PreOrder(node->Left);
		PreOrder(node->Right);
	}


private:
	RedBlackNode<T>* Root;
	int Size;

	//swap the heads of two binary trees. used in in assignment overload.
	void Swap(RedBlackTree<T>& one, RedBlackTree<T>& two)
	{
		RedBlackNode<T>* temp = one.Root;

		one.Root = two.Root;
		two.Root = temp;

		temp = nullptr; //not sure if necessary
	}

	//called by the destructor. performs an post order traversal delete
	void ClearTree(RedBlackNode<T>* node)
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

	  RedBlackNode<T>* Copy( RedBlackNode<T>* node )
       {
            if(!node)  
                return nullptr;
			else
			{
				RedBlackNode<T>* copy = new RedBlackNode<T>(node->Data);
				copy->Red = node->Red;
				copy->Left = Copy(node->Left);
				copy->Right = Copy(node->Right);

				return copy;
			}
               
        }

};






#endif