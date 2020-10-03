#ifndef STACK_H
#define STACK_H

template<class T>
class stack;

template<class T>
class stackEntry
{
	friend class stack<T>;

private:
	T Data;
	stackEntry<T>* Next;

protected:
	stackEntry(const T& newdata, stackEntry<T>* newnext = nullptr)
	{
		Data = newdata;
		if (newnext)
			Next = newnext;
		else
			Next = nullptr;
	}

	virtual ~stackEntry()
	{
		//delete next;
		//next = nullptr;
	}
	
	virtual void next(stackEntry<T>* pnext)
	{
		Next = pnext;
	}

	virtual T& data()
	{
		return Data;
	}

	virtual const T& data() const
	{
		return Data;
	}

	virtual stackEntry<T>* next()
	{
		return Next;
	}

};


template<class T>
class stack
{
private:
	std::size_t Size;
	stackEntry<T>* Top;


public:
	stack()
		:Size(0), Top(nullptr) {}


	stack(const stack<T>& other)
	{
		Size = other.size();

		Top = new stackEntry<T>(other.top());
		stackEntry<T>* cur = Top;


		stackEntry<T>* temp = other.Top;
		while(temp->next())
		{
			cur->next(new stackEntry<T>(temp->next()->data()));
			cur = cur->next();

			temp = temp->next();
		}
		
	}


	const stack<T>& operator=(const stack<T>& rhs)
	{
		if (this != &rhs)
		{
			clear();
			Size = rhs.size();

			Top = new stackEntry<T>(rhs.top());
			stackEntry<T>* cur = Top;


			stackEntry<T>* temp = rhs.Top;
			while (temp->next())
			{
				cur->next(new stackEntry<T>(temp->next()->data()));
				cur = cur->next();

				temp = temp->next();
			}			
		}

		return *this;
	}



	void clear()
	{
		int c = (int)Size;

		for (int i = 0; i < c; i++)
		{
			pop();
		}
	}

	virtual ~stack()
	{
		clear();
	}

	const T& top() const
	{
		return Top->data();
	}

	T& top()
	{
		return Top->data();
	}


	bool empty() const
	{
		if (Size != 0)
			return false;

		return true;
	}


	std::size_t size() const
	{
		return Size;
	}

	void push(const T& value)
	{
		if (!Top)
		{
			//std::cout << "pushing value: " << value << "\n";
			Top = new stackEntry<T>(value);
			Size++;
			return;
		}
		
		//std::cout << "pushing value: " << value << "\n";
		stackEntry<T>* temp = new stackEntry<T>(value);
		temp->next(Top);	

		Top = temp;
	
		Size++;
	}

	void pop()
	{
		if (Size == 0)
		{
			return;
		}
		
		stackEntry<T>* temp = Top;
		if (Top->next())
			Top = Top->next();
		
		delete temp;
		Size--;
	}





	void debug() const
	{
		std::cout << "size: " << size() << "\n";
		stackEntry<T>* temp = Top;

		for(unsigned int i = 0; i < (int)Size; i++)
		{
			std::cout << "temp is:" << temp->data() << "\n";
			temp = temp->next();			
		}

	}

	void debug(std::ostream& out) const
	{
		out << "size: " << size() << "\n";
		stackEntry<T>* temp = Top;

		for (unsigned int i = 0; i < (int)Size; i++)
		{
			out << "temp is:" << temp->data() << "\n";
			temp = temp->next();
		}
	}


};






#endif