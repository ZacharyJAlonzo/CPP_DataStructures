#ifndef QUEUE_H
#define QUEUE_H

template<class T>
class queue;

template<class T>
class queueEntry
{
	friend class queue<T>;


private:
	T Data;
	queueEntry<T>* Next;

protected:
	queueEntry(const T& newData, queueEntry<T>* newNext = nullptr)
	{
		Data = newData;
		if (newNext)
			Next = newNext;
		else
			Next = nullptr;	
	}

	virtual ~queueEntry() {}

	virtual void next(queueEntry<T>* pNext)
	{
		Next = pNext;
	}

	virtual T& data()
	{
		return Data;
	}
	virtual const T& data() const
	{
		return Data;
	}

	virtual queueEntry<T>* next()
	{
		return Next;
	}




};


template<class T>
class queue
{
private:
	queueEntry<T>* first;
	queueEntry<T>* last;
	std::size_t  count;

public:
	queue()
		:first(nullptr), last(nullptr), count(0) {}

	~queue()
	{
		clear();
	}


	queue(const queue& other)
	{
		count = other.size();

		first = new queueEntry<T>(other.first->Data);

		queueEntry<T>* cur = first;


		queueEntry<T>* temp = other.first;
		while (temp->next())
		{
			cur->next(new queueEntry<T>(temp->next()->data()));
			cur = cur->next();

			temp = temp->next();
		}
		last = cur;

	}


	const queue& operator=(const queue& other)
	{
		if (this != &other)
		{
			count = other.size();

			first = new queueEntry<T>(other.first->Data);

			queueEntry<T>* cur = first;


			queueEntry<T>* temp = other.first;
			while (temp->next())
			{
				cur->next(new queueEntry<T>(temp->next()->data()));
				cur = cur->next();

				temp = temp->next();
			}
			last = cur;
		}
		return *this;
		
	}



	const T& front() const
	{
			return first->Data;
	}

	T& front()
	{
			return first->Data;
	}

	const T& back() const
	{
			return last->Data;
	}

	T& back()
	{
			return last->Data;		
	}

	bool empty() const
	{
		if (count == 0)
			return true;
		return false;
	}

	std::size_t size() const
	{
		return count;
	}


	void push(const T& value)
	{
		if (!first)
		{
			first = new queueEntry<T>(value);
			last = first;
			count++;
			return;
		}
		else
		{
			queueEntry<T>* temp = new queueEntry<T>(value);
			last->next(temp);

			last = temp;
			count++;
					
		}
	}



	void pop()
	{
		if (count != 0)
		{
			queueEntry<T>* temp = first;
			first = temp->next();
			delete temp;
			count--;
		}
		else return;
	}

	void clear()
	{	
		int c = (int)count;
		for (int i = 0; i < c; i++)
		{
			pop();
		}
	}

	void debug() const
	{
		std::cout << "size: " << size() << "\n";
		queueEntry<T>* temp = first;

		for (unsigned int i = 0; i < (int)count; i++)
		{
			std::cout << "temp is:" << temp->data() << "\n";
			temp = temp->next();
		}
	}

	void debug(std::ostream& out) const
	{
		out << "size: " << size() << "\n";
		queueEntry<T>* temp = first;

		for (unsigned int i = 0; i < (int)count; i++)
		{
			out << "temp is:" << temp->data() << "\n";
			temp = temp->next();
		}
	}

	void traverse(void (*applicationFunction) (const T& nextItem))
	{
		queueEntry<T>* temp = first;
		for (int i = 0; i < (int)count; i++)
		{
			applicationFunction(temp->data());
			temp = temp->next();
		}
	}



};





#endif