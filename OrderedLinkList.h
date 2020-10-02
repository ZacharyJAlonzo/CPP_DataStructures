/*
 * orderedLinkedList.h
 *
 * Store the DataType values in sorted order. This ordering
 * is determined by the comparison operators of the DataType
 * class.
 *
 */

#ifndef ORDEREDLINKEDLIST_H_
#define ORDEREDLINKEDLIST_H_

#include <cstddef>

#include "linkedList.h"

template<class DataType>
class orderedLinkedList
{
public:
	typedef linkedList<DataType>              unorderedLinkedList;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef std::ptrdiff_t 					      difference_type;
	typedef std::size_t						      size_type;
	typedef typename unorderedLinkedList::iterator  iterator;
	typedef const iterator	  	               const_iterator;
private:
	// we are making use of the DoubleLinkedList class
	unorderedLinkedList list;
	void copy(const orderedLinkedList<DataType>& other);
	void clear();

public:
	// default constructor
	orderedLinkedList();
	// copy constructor
	orderedLinkedList(const orderedLinkedList& other);
	// assignment operator
	const orderedLinkedList& operator=(const orderedLinkedList& other);
	// destructor
	virtual ~orderedLinkedList();
	// iterators
	iterator begin()
	{
		return list.begin();
	}

	iterator end()
	{
		return list.end();
	}

	const_iterator begin() const
	{
		return list.begin();
	}

	const_iterator end() const
	{
		return list.end();
	}

	// number of items in the list
	virtual std::size_t size() const;
	// is the list empty (true) or does it have entries (false)
	virtual bool empty() const;
	// print the items in the list
	virtual void print() const;
	// display the contents of the list to the ostream&
	virtual void print(std::ostream& out) const;
	// display debug information on the passed in ostream
	virtual void debug(std::ostream& out) const;
	// find the element and return an interator for it
	virtual linkedListIterator<DataType> find(const DataType& existingItem);
	// remove the node equal to currentItem
	virtual bool erase(const DataType& currentItem);
	// remove the node by address existingNode
	virtual linkedListIterator<DataType> erase(iterator iter);
	// insert the new item into the list (in sorted order)
	// a duplicate entry will be ignored
	virtual void insert(const DataType& newItem);
	// get the last entry
	iterator back()
	{
		return list.back();
	}

	const_iterator back() const
	{
		return list.back();
	}
};

// Your implementation code goes here

template<class DataType>
orderedLinkedList<DataType>::orderedLinkedList()
{
}

template<class DataType>
orderedLinkedList<DataType>::orderedLinkedList(const orderedLinkedList& other)
{
	copy(other);
	list.count = other.size();
}

template<class DataType>
const orderedLinkedList<DataType>& orderedLinkedList<DataType>::operator=(const orderedLinkedList& other)
{
	if (&other != this)
	{
		clear();
		copy(other);
		list.count = other.size();
	}

	return *this;

}

template<class DataType>
orderedLinkedList<DataType>::~orderedLinkedList()
{
}


template<class DataType>
void orderedLinkedList<DataType>::insert(const DataType& newItem)
{
	
	for (iterator it = begin(); it != end(); ++it)
	{
		if (*it == newItem)
		{
			return;
		}		
		else if (*it > newItem)
		{
			list.insert_before(it, newItem);
			return;
		}
	}
		list.push_back(newItem);
	
}





template<class DataType>
std::size_t orderedLinkedList<DataType>::size() const
{
	return list.size();
}

template<class DataType>
bool orderedLinkedList<DataType>::empty() const
{
	return list.empty();
}

template<class DataType>
void orderedLinkedList<DataType>::print() const
{
	list.print(std::cout);
}

template<class DataType>
void orderedLinkedList<DataType>::print(std::ostream& out) const
{
	list.print(out);
}

template<class DataType>
 void orderedLinkedList<DataType>::debug(std::ostream& out) const
{
	 list.debug(out);
}

template<class DataType>
linkedListIterator<DataType> orderedLinkedList<DataType>::find(const DataType& existingItem)
{
	return list.find(existingItem);
}

template<class DataType>
bool orderedLinkedList<DataType>::erase(const DataType& currentItem)
{
	return list.erase(currentItem);
}

template<class DataType>
linkedListIterator<DataType> orderedLinkedList<DataType>::erase(iterator iter)
{
	return list.erase(iter);
}




template<class DataType>
void orderedLinkedList<DataType>::clear()
{
	int c = list.size();

	for (int i = 0; i < c; i++)
	{
		list.pop_front();
	}
}

template<class DataType>
void orderedLinkedList<DataType>::copy(const orderedLinkedList<DataType>& other)
{

	listNode<DataType>* nodeToCopy = other.list.firstNode;

	listNode<DataType>* curNode = new listNode<DataType>(nodeToCopy->data());
	listNode<DataType>* nextNode = new listNode<DataType>(nodeToCopy->next()->data());

	curNode->previous(nullptr);
	curNode->next(nextNode);

	list.firstNode = curNode;

	nodeToCopy = nodeToCopy->next();

	int c = other.count;
	for (int i = 0; i < (c - 2); i++)
	{
		nextNode->previous(curNode);
		nodeToCopy = nodeToCopy->next();
		nextNode->next(new listNode<DataType>(nodeToCopy->data()));
		curNode = nextNode;
		nextNode = nextNode->next();
	}
	nextNode->previous(curNode);
	list.lastNode = nextNode;


}




#endif /* ORDEREDLINKEDLIST_H_ */
#pragma once


