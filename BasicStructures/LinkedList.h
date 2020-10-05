#pragma once
/*
 * linkedList.h
 *
 * Implementation of a double linked list.
 *
 * We have the ability to get the first and last entries and navigate
 * through the entries in the linked list.
 *
 * There are actually three classes here:
 *
 * listNode<DataType>
 *
 * listNodeIterator<DataType>

 * and
 *
 * linkedList<DataType>
 *
 * The listNodeIterator is the iterator for the new linked list class.
 *
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>

 // forward declaration of the template class linkedList
template<class DataType>
class linkedList;
// forward declaration of iterator
template<class DataType>
class linkedListIterator;

// listNode class
template<class DataType>
class listNode
{
	// make DoubleLinkedList<DataType> a friend class
	friend class linkedList<DataType>;
	friend class linkedListIterator<DataType>;
private:
	// contains the actual data
	DataType dataType;
	// pointer to the next item in the list or nullptr 
	// if at the end
	listNode<DataType>* pNext;
	// pointer to the previous item in the list or nullptr 
	// if at the start
	listNode<DataType>* pPrevious;
public:
	// default constructor
	listNode();
	// constructor with data
	listNode(const DataType& newItem);
protected:
	// get the next node
	listNode* next() const
	{
		return pNext;
	}

	// get the previous node
	listNode* previous() const
	{
		return pPrevious;
	}

	// return the data stored in the node as a const
	const DataType& data() const
	{
		return dataType;
	}
	// return the data stored in the node
	DataType& data()
	{
		return dataType;
	}
	// update the next node
	void next(listNode* nextNode)
	{
		pNext = nextNode;
	}
	// update the previous node
	void previous(listNode* previousNode)
	{
		pPrevious = previousNode;
	}
};

// the linkedListIterator is the iterator for class linkedList.
//
// most of this code has been provided for you. 
// the exceptions are the operator--() operator--(int) member fuctions and
// and the operator== and operator!= member functions. 
template<class DataType>
class linkedListIterator
{
	typedef DataType 								   value_type;
	typedef DataType& reference;
	typedef const DataType& const_reference;
	typedef DataType* pointer;
	typedef const DataType* const_pointer;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef std::ptrdiff_t 							difference_type;
	typedef std::size_t								size_type;
	typedef linkedListIterator						iterator;
	typedef const linkedListIterator	  			const_iterator;

	friend class linkedList<DataType>;
private:
	listNode<DataType>* current = nullptr;
public:
	linkedListIterator(listNode<DataType>* current)
		: current(current)
	{
	}

	virtual ~linkedListIterator()
	{
	}

	reference operator*()
	{
		assert(current != nullptr);
		return current->data();
	}

	const_reference operator*() const
	{
		assert(current != nullptr);
		return current->data();
	}

	pointer operator->()
	{
		assert(current != nullptr);
		return &(current->data());
	}

	const_pointer operator->() const
	{
		assert(current != nullptr);
		return &(current->data());
	}

	iterator operator++()
	{
		if (current != nullptr)
		{
			current = current->next();
		}
		return *this;
	}

	iterator operator++(int)
	{
		iterator it = *this;
		if (current != nullptr)
		{
			current = current->next();
		}
		return it;
	}

	// you need to implement the following - they can be inlined if you want
	iterator operator--()
	{
		if (current != nullptr)
		{
			current = current->previous();
		}

		return *this;
	}


	iterator operator--(int)
	{
		iterator it = *this;
		if (current != nullptr)
		{
			current = current->previous();
		}

		return it;
	}

	bool operator==(const_iterator& other) const
	{
		return current == other.current;
	}

	bool operator!=(const_iterator& other) const
	{
		return current != other.current;
	}

};

// linkedList class
template<class DataType>
class linkedList
{
public:
	// 		typedef DataType 								   value_type;
	// 		typedef DataType& 								reference;
	// 		typedef const DataType& 						const_reference;
	// 		typedef DataType* 								pointer;
	// 		typedef const DataType* 						const_pointer;
	// 		typedef std::bidirectional_iterator_tag	iterator_category;
	// 		typedef std::ptrdiff_t 							difference_type;
	// 		typedef std::size_t								size_type;
	typedef linkedListIterator<DataType>		iterator;
	typedef const linkedListIterator<DataType> const_iterator;

private:
	listNode<DataType>* firstNode;
	listNode<DataType>* lastNode;
	int count;
	// your instance data goes here. Things like the pointers to the first and last nodes 
	//  as well as the count of nodes
public:
	// default constructor
	linkedList();
	// copy constructor
	linkedList(const linkedList& other);
	// assignment operator
	const linkedList& operator=(const linkedList& other);
	// destructor
	virtual ~linkedList();
	// return the number of nodes in the list
	std::size_t size() const;
	// return true if the list is empty
	bool empty() const;
	// display the contents of the list to std::cout
	void print() const
	{
		print(std::cout);
	}
	// display the contents of the list to the ostream&
	void print(std::ostream& out) const;

	// iterators
	iterator begin()
	{
		return iterator(firstNode);
	}

	const_iterator begin() const
	{
		return iterator(firstNode);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	const_iterator end() const
	{
		return iterator(nullptr);
	}

	// dump the contends in debug format to passed in 
	// ostream - usage to cout would be:
	//   list.debug(std::cout);
	void debug(std::ostream& out) const;
public:
	// add an item to the front of the list
	virtual void push_front(const DataType& newItem);
	// add an item to the back of the list
	virtual void push_back(const DataType& newItem);
	// remove an item from the front of the list
	virtual void pop_front();
	// remove an item from the back of the list
	virtual void pop_back();
	// insert newItem before the node specified by the iterator
	virtual void insert_before(iterator iter, const DataType& newItem);
	// insert newItem after the node specified by the iterator
	virtual void insert_after(iterator iter, const DataType& newItem);
	// find the node and return the iterator for that element.
	// Return end() if not found
	virtual iterator find(const DataType& existingItem);
	// remove the node equal to currentItem
	virtual bool erase(const DataType& currentItem);
	// remove the node by address existingNode
	virtual iterator erase(iterator iter);
	// return the iterator for the last node
	virtual iterator back()
	{
		return linkedListIterator<DataType>(lastNode);
	}
	virtual const_iterator back() const
	{
		return linkedListIterator<DataType>(lastNode);
	}
	virtual void clear();
	virtual void copy(const linkedList<DataType>& other);
protected:
private:
	
	// any helper functions you need should eithee be protected or private
};

// the constructors for the listNode class are included here
// default constructor
template <class DataType>
listNode<DataType>::listNode()
	: dataType(), pNext(nullptr), pPrevious(nullptr)
{
}

// constructor with data
template <class DataType>
listNode<DataType>::listNode(const DataType& newItem)
	: dataType(newItem), pNext(nullptr), pPrevious(nullptr)
{
}

// note the code for the debug() function is included
// display a debug version of the list
template<class DataType>
void linkedList<DataType>::debug(std::ostream& out) const
{
	const unsigned int ADDRWIDTH = 10;
	out << "START DEBUG" << std::endl;
	out << "first  =" << std::setw(ADDRWIDTH) << firstNode;
	out << ", last=" << std::setw(ADDRWIDTH) << lastNode;
	out << ", # nodes=" << size() << std::endl;
	unsigned int count = 1;

	for (auto current = firstNode; current != nullptr; current = current->next())
	{
		out << "node " << std::setw(2) << count;
		out << "=" << std::setw(ADDRWIDTH) << current;
		out << ", next=" << std::setw(ADDRWIDTH)
			<< current->next();
		out << ", previous=" << std::setw(ADDRWIDTH)
			<< current->previous();
		out << ", value=" << current->data() << std::endl;
		count++;
	}
	out << "END DEBUG" << std::endl;
}


// I have included a few function headers and bodies here where the syntax is odd
// Your implementation of non-inlined member funcctions needs to go there. 
// default constructor


// this is one where the C++ stynax gets very odd. Since we are returning back an interator we
// need to qualify it with the class it is in (linkedList<DataType>::iterator and we 
// have ot include the typename so the C++ comiler knows this is a typename and not some other
// template class usage. 


template<class DataType>
linkedList<DataType>::linkedList()
	: firstNode(nullptr), lastNode(nullptr), count(0)
{
}

template<class DataType>
linkedList<DataType>::linkedList(const linkedList& other)
{
	copy(other);
	count = other.count;
}

template<class DataType>
const linkedList<DataType>& linkedList<DataType>::operator=(const linkedList& other)
{
	if (&other != this)
	{
		clear();
		copy(other);
		count = other.count;

		return *this;
	}
	else return *this;

}



template<class DataType>
 linkedList<DataType>::~linkedList()
{
	 clear();
	 delete firstNode;
	 delete lastNode;
}

template<class DataType>
std::size_t linkedList<DataType>::size() const
{
	return count;
}

template<class DataType>
bool linkedList<DataType>::empty() const
{
	return firstNode == nullptr;
}

template<class DataType>
void linkedList<DataType>::print(std::ostream& out) const
{
	for (linkedListIterator<DataType> it = begin(); it != end(); it++)
	{
		std::cout << *it << " ";
	}
}


template<class DataType>
void linkedList<DataType>::push_front(const DataType& newItem)
{
	
	if (firstNode)
	{
		listNode<DataType>* newNode = new listNode<DataType>(newItem);

		listNode<DataType>* temp = firstNode;

		firstNode = newNode;
		firstNode->next(temp);
		temp->previous(firstNode);
		
		count++;

		temp = nullptr; // delete unused pointer
		delete temp;

	}
	else
	{
		firstNode = new listNode<DataType>(newItem);
		lastNode = firstNode;
		count++;
	}
}

template<class DataType>
void linkedList<DataType>::push_back(const DataType& newItem)
{
	if (lastNode)
	{
		listNode<DataType>* newNode = new listNode<DataType>(newItem);
		listNode<DataType>* temp = lastNode;

		lastNode = newNode;
		lastNode->previous(temp);
		temp->next(lastNode);

		count++;

		temp = nullptr;//delete unused pointer
		delete temp;
	}
	else
	{
		firstNode = new listNode<DataType>(newItem);
		lastNode = firstNode;
		count++;
	}
}

template<class DataType>
 void linkedList<DataType>::pop_front()
{
	 if (lastNode)
	 {
		 if (firstNode == lastNode)
		 {
			 delete firstNode;

			 firstNode = nullptr;//clean up
			 lastNode = nullptr;

			 count--;
			 return;
		 }

		 listNode<DataType>* temp = firstNode;
		 firstNode = firstNode->next();
		 firstNode->previous(nullptr); //clean up
		 count--;

		 delete temp;
		 return;
	 }
	 else
	 {
		 return;
	 }
}

template<class DataType>
void linkedList<DataType>::pop_back()
{
	if (lastNode)
	{
		if (firstNode == lastNode)
		{
			delete firstNode;

			firstNode = nullptr;
			lastNode = nullptr;

			count--;
			return;
		}

		listNode<DataType>* temp = lastNode;
		lastNode = lastNode->previous();
		lastNode->next(nullptr); //clean up

		count--;

		delete temp;
		return;
	}
	else
	{
		return;
	}
}


// find the node and return the address to the node. Return
// nullptr if not found
template<class DataType>
typename linkedList<DataType>::iterator linkedList<DataType>::find(const DataType& existingItem)
{
	linkedListIterator<DataType> it = begin();
	
	for (int i = 0; i < count; i++)
	{
		if (*it == existingItem)
		{
			return it;
		}
		else
		{
			++it;
		}
	}

	return nullptr;
}

template<class DataType>
 void linkedList<DataType>::insert_before(iterator iter, const DataType& newItem)
{

	 if (iter == end() || iter == begin())
	 {
		 push_front(newItem);
	 }
	 else
	 {
		 listNode<DataType>* temp = iter.current->previous();
		 listNode<DataType>* newNode = new listNode<DataType>(newItem);

		 iter.current->previous(newNode);

		 newNode->next(iter.current);
		 newNode->previous(temp);
			
		 temp->next(newNode);

		 count++;

		 newNode = nullptr;		
		 delete newNode;

		 temp = nullptr;
		 delete temp;
	 }

}

template<class DataType>
 void linkedList<DataType>::insert_after(iterator iter, const DataType& newItem)
{
	 if(iter == end() || iter == back())
	 {
		 push_back(newItem);
	 }
	 else
	 {
		 listNode<DataType>* temp = iter.current->next();
		 listNode<DataType>* newNode = new listNode<DataType>(newItem);
		 
		 iter.current->next(newNode);
		
		 newNode->next(temp);
		 temp->previous(newNode);

		 count++;

		 newNode = nullptr;
		 delete newNode;
		 
		 temp = nullptr;
		 delete temp; 
	 }
}

 // remove the node equal to currentItem
 template<class DataType>
 bool linkedList<DataType>::erase(const DataType& currentItem)
 {	
	 linkedListIterator<DataType> it = find(currentItem);
	 if (it == nullptr)
	 {
		 return false;
	 }

	 erase(it);
	 return true;
 }

 // remove the node by iterator
 template<class DataType>
 typename linkedList<DataType>::iterator linkedList<DataType>::erase(linkedList<DataType>::iterator iter)
 {
	 if (iter == end())
	 {
		 return nullptr;
	 }
	 else if (iter == back())
	 {		
		 pop_back();

		 linkedListIterator<DataType> it(lastNode);
		 return it;

	 }
	 else if (iter == begin())
	 {
		 
		 std::cout << "true" << std::endl;
		 pop_front();

		 linkedListIterator<DataType> it(firstNode);
		 return it;
	 }
	 else
	 {
 
		 listNode<DataType>* node = iter.current;
		 (node->previous())->next(node->next());
		 (node->next())->previous(node->previous());

		 count--;

		 linkedListIterator<DataType> it = linkedListIterator<DataType>(node->next());
		 delete node;
	
		 return it;
	 }
 }

 template<class DataType>
 void linkedList<DataType>::clear()
 {
	 int c = count;

	 for (int i = 0; i < c; i++)
	 {
		 pop_front();
	 }
 }

 template<class DataType>
 void linkedList<DataType>::copy(const linkedList<DataType>& other)
 {
	 std::cout << "in copy";
	 
	 listNode<DataType>* nodeToCopy = other.firstNode;	 

	 listNode<DataType>* curNode = new listNode<DataType>(nodeToCopy->data()); 
	 listNode<DataType>* nextNode = new listNode<DataType>(nodeToCopy->next()->data());

	 curNode->previous(nullptr);
	 curNode->next(nextNode);

	 firstNode = curNode;

	 nodeToCopy = nodeToCopy->next();

	 int c = other.count;
	 for (int i = 0; i < (c-2); i++)
	 {
		nextNode->previous(curNode);
		nodeToCopy = nodeToCopy->next();
		nextNode->next(new listNode<DataType>(nodeToCopy->data()));
		curNode = nextNode;
		nextNode = nextNode->next();	 
	 }
	 nextNode->previous(curNode);
	 lastNode = nextNode;
	 

 }



// all of your member function need to be before the #endif
#endif /* DOUBLELINKEDLIST_H_ */

