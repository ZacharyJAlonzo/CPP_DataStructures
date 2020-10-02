
#include <cstring>
#include <string>

template<class K, class V>
class Map;

template < class K, class V >
class Pair
{

friend class Map<K, V>;

private:
	K Key = NULL;
	V Value = NULL;

	Pair() {}

	Pair(K key, V value)
	{
		Key = key;
		Value = value;
	}

	V GetValue() { return Value; }
	K GetKey() { return Key; }

	void SetValue(V value) { Value = value; }
	void SetKey(K key) { Key = key; }

};


template <class K, class V>
class Map
{

public:
	//Default constructor -- initializes array and sets size to 16.
	Map()
	{
		PairList = new Pair<K, V>[16];
		Size = 16;
		Index = 0;
	}

	~Map() { delete[] PairList; }


	//copy constructor
	Map(Map<K, V>& ref)
	{
		CopyList(ref);
	}

	//copy constructor called implicitly
	Map<K, V>& operator=(Map<K, V> rhs)
	{
		if (this == &rhs)
		{
			return this;
		}

		std::swap(this->PairList, rhs->PairList);
		return *this;
	}


	//Inserts the key-value pair into the Map.
	//Returns the previous mapped value for this key, or NULL if there was not one.
	V Put(K key, V value)
	{
		int index = ContainsKey(key);		
		if (index != -1) 
		{ 
			//save the replaced value.
			V ReplacedValue = PairList[index].Value;

			//replace the array value. No change to Index
			PairList[index] = Pair<K, V>(key, value);
			
			return ReplacedValue;
		} 

		//check size ratio
		double Ratio = (double)Size / (double)Index;
		if (Ratio <= 2.0)
		{
			//resize the array.
			Resize();
		}

		PairList[Index] = Pair<K, V>(key, value);
		Index++;
		return NULL;
	}

	//Delete the pair corresponding to this key.
	//Returns the removed value, or NULL if the key was not found.
	V Remove(K key)
	{	
		//if the key is not contained, exit
		int index = ContainsKey(key);
		if (index == -1) { return NULL; }
	
		//save the value for the return.
		V RemovedValue = PairList[index].Value;

		//memmove the array indexes	
		std::memmove(PairList + index, PairList + (index + 1), sizeof(Pair<K, V>) * (Size - (index + 1)) );

		//decrement the next index since the array is shifted backwards.
		Index--;

		return RemovedValue;
	}

	//Find the value corresponding to the key.
	//Returns the corresponding value, or NULL if the key was not found.
	V Find(K key)
	{
		int index = ContainsKey(key);

		if (index == -1) { return NULL; }

		return PairList[index].Value;
	}

	//Checks to see if a key is contained in the Map.
	//Returns an int corresponding to the index.
	int ContainsKey(K key)
	{
		//iterate through the list, up to the current Index. 
		for (int i = 0; i < Index; i++)
		{
			if (PairList[i].Key == key)
				return i;
		}

		//key was not found
		return -1;
	}


	std::string ToString()
	{
		std::string s = "";

		for (int i = 0; i < Index; i++)
		{
			s += PairList[i].Key+'0';
			s += "=";
			s += PairList[i].Value;
			s += ", ";
		}

		return s;
	}


private:
	//initial size of 16
	Pair<K, V>* PairList;
	int Size;
	int Index;


	void Resize()
	{
		int NewSize = Size * 2;
		Pair<K, V>* NewList = new Pair<K, V>[NewSize];

		std::memcpy(NewList, PairList, sizeof(Pair<K, V>) * Size);
		
		//deallocate old memory
		delete[] PairList;

		Size = NewSize;
		PairList = NewList;
	}


	void CopyList(Map<K, V>& ref)
	{
		PairList = new Pair<K, V>[ref.Size];
		Size = ref.Size;
		Index = 0;

		for (int i = 0; i < ref.Index; i++)
		{
			Put(ref.PairList[i].Key, ref.PairList[i].Value);
		}
	}


};