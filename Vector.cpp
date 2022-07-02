#include<iostream>
using namespace std;
template<typename T>
class MyVector {
	int Size;
	int index;
	int Capacity;
	int Max_Size;
	T* array= 0;
public:

	// Default Constructor

	MyVector()
	{
		Max_Size = 1000;
		Size = 0;
		Capacity = 10;
		index = 0;
		array = new T[Capacity];
	}

	// Parametrized Constructor

	MyVector(int size)
	{
		Max_Size = 1000;
		Size = size;
		Capacity = Size + 10;
		index = 0;
		array = new T[Capacity];
	}

	// Copy Constructor
	
	MyVector(const MyVector<T>& rhsVector)
	{
		Size = rhsVector.Size;
		Capacity = rhsVector.Capacity;
		Max_Size = rhsVector.Max_Size;
		array = new T[Capacity];
		for (int i = 0; i < Size; i++)
		{
			array[i] = rhsVector.array[i];
		}
		index = Size;
	}

	// Iterator Class

	class MyIterator {
		T* Pointer;
	public:

		// Defualt Constructor

		MyIterator()
		{
			Pointer = 0;
		}

		// Parametrized Constructor

		MyIterator(T* Location)
		{
			Pointer = Location;
		}

		//Not Equal Operator

		bool operator!=(MyIterator otherPointer)
		{
			if (Pointer != otherPointer.Pointer)
				return true;
			return false;
		}

		// Pre Increment Operator

		MyIterator& operator++()
		{
			Pointer++;
			return *this;
		}
		
		// Post Increment Operator

		MyIterator& operator++(int i)
		{
			MyIterator Copy;
			Copy.Pointer = this->Pointer;
			Pointer++;
			return Copy;
		}

		//
		
		MyIterator& operator--()
		{
			--Pointer;
			return *this;
		}

		// *Operator

		T& operator*()
		{
			return *Pointer;
		}

		// Operator +

		MyIterator& operator+(int number)
		{
			this->Pointer+=number;
			return *this;
		}

		// Operator -

		MyIterator& operator-(int number)
		{
			this->Pointer -= number;
			return *this;
		}

		// Operator "-"

		int operator-(MyIterator& SecondIterator)
		{
			return (Pointer - SecondIterator.Pointer);
		}
	};

	// Function Begin

	MyIterator begin()
	{
		return MyIterator(array);
	}

	// Function End

	MyIterator end()
	{
		T* End;
		if (Size > 0)
		{
			End = array + Size;
		}
		else
		{
			End = array + Size;
		}
		return MyIterator(End);
	}

	// Overloaded Assignment Operator

	MyVector<T>& operator=(MyVector<T>& rhsVector)
	{
		if (this->Size > 0)
		{
			delete[]this->array;
			this->array = 0;
		}
		this->Size = rhsVector.Size;
		this->Capacity = rhsVector.Capacity;
		array = new T[Size];
		for (int i = 0; i < Size; i++)
		{
			array[i] = rhsVector.array[i];
		}
		return *this;
	}

	// Function Size

	int size()
	{
		return Size;
	}

	// Function Maximum Size

	int max_size()
	{
		return Max_Size;
	}

	// Function Empty

	bool empty()
	{
		return (Size > 0) ? 1 : 0;
	}

	// Overloaded Subscript Operator

	T& operator[](int i)
	{
		if (i >= 0 && i < Size)
		{
			return array[i];
		}
	}

	// Function At

	T& at(int i)
	{
		if (i >= 0 && i < Size)
		{
			return array[i];
		}
		else 
		{
			throw - 1;
		}
	}

	// Function Front

	T& front()
	{
		if (index == 0)
		{
			index++;
			return array[0];
		}
		return array[0];
	}

	// Function Back

	T& back()
	{
		return array[Size - 1];
	}

	// Function Data

	T* data()
	{
		return array;
	}
	
	// Function Push Back

	void push_back(T value)
	{
		array[index] = value;
		index++;
		if (index >= Size)
		{
			Size = index;
			if (Size >= Capacity && Size < Max_Size)
			{
				Capacity = Capacity + 10;
				T* NewArray = new T[Capacity];
				for (int i = 0; i < Size; i++)
				{
					NewArray[i] = array[i];
				}
				delete[]array;
				array = NewArray;
			}
		}
	}

	// Function pop back

	void pop_back()
	{
		if (index > 0)
		{
			index--;
			array[index] = 0;
			Size--;
		}
	}

	// Assign Function

	void assign(int n, T value)
	{
		for (int i = 0; i < n; i++)
		{
			array[i] = value;
		}
		Size = n;
		index = n;

	}

	// Assign Funtion
	
	void assign(MyIterator& start, MyIterator& terminate)
	{
		MyIterator PointerVaraiable;
		PointerVaraiable = start;
		int i = 0;
		for (; PointerVaraiable != terminate; PointerVaraiable++)
		{
			array[i] = *PointerVaraiable;
			i++;
		}
		index = i;
		for (; i < Size; i++)
		{
			array[i] = 0;
		}
		Size = index;
	}

	// Insert Function

	MyIterator insert(MyIterator& start,T value)
	{
		if ((Size + 1) < Capacity)
		{
			MyIterator itr;
			itr = this->begin();
			int InsertingIndex = start - itr;
			int i = 0;
			for (i = Size - 1; i >= InsertingIndex; i--)
			{
				array[i + 1] = array[i];
			}
			array[InsertingIndex] = value;
			Size++;
			index++;
			return start;
		}

		else
		{
			MyIterator itr;
			itr = this->begin();
			int InsertingIndex = start - itr;
			Capacity = Capacity + 10;
			T* NewArray = new T[Capacity];
			for (int i = 0; i < Size; i++)
			{
				NewArray[i] = array[i];
			}
			delete[]array;
			array = NewArray;
			int i = 0;
			for (i = Size - 1; i >= InsertingIndex; i--)
			{
				array[i + 1] = array[i];
			}
			array[InsertingIndex] = value;
			Size++;
			index++;
			return MyIterator(&array[InsertingIndex]);
		}
		
	}
	
	// Erase Function

	void erase(MyIterator& start, MyIterator& End)
	{
		int StartIndexErasing = 0, LastErasingIndex = 0, position = 0;
		MyIterator itr;
		itr = this->begin();
		StartIndexErasing = start - itr;
		position = StartIndexErasing;
		LastErasingIndex = End - itr;
		for (int i = LastErasingIndex + 1; i < Size; i++)
		{
			array[position] = array[i];
			position++;
		}
		Size = position;
		index = position;
	}
	
	// Erase Function

	void erase(MyIterator& address)
	{
		MyIterator itr;
		itr = this->begin();
		int StartingIndex = address - itr;
		for (int i = StartingIndex; i < this->Size - 1; i++)
		{
			array[i] = array[i + 1];
		}
		Size--;
		index--;
	}

	// Clear Function
	
	void clear()
	{
		for (int i = 0; i < Size; i++)
		{
			array[i] = 0;
		}
		Size = 0;
		index = 0;
	}

	// Equal Equal Operator for Vectors

	bool operator==(MyVector<T>& SecondVector)
	{
		if (this->Size == SecondVector.Size)
		{
			for (int i = 0; i < Size; i++)
			{
				if (this->array[i] != SecondVector.array[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	// Not Equal Operator for Vectors

	bool operator!=(MyVector<T>& SecondVector)
	{
		if (this->Size == SecondVector.Size)
		{
			for (int i = 0; i < Size; i++)
			{
				if (this->array[i] != SecondVector.array[i])
				{
					return true;
				}
			}
			return false;
		}
		return true;
	}

	// Sort Function

	void Sort()
	{
		T block;
		int StartingIndex = 0, LastIndex = 0, minimum = 0;
		for (int i = 0; i < Size - 1; i++)
		{
			minimum = i;
			for (int j = i + 1; j < Size; j++)
			{
				if (array[j] < array[minimum])
				{
					minimum = j;
				}
			}
			block = array[i];
			array[i] = array[minimum];
			array[minimum] = block;
		}
	}

	// Print Function
	
	void print()
	{
		for (int i = 0; i < Size; i++)
		{
			cout << array[i] << endl;
		}
	}

	// Destructor

	~MyVector()
	{
		delete[]array;
		array = 0;
		Size = 0;
		index = 0;
	}
};

template<>
class MyVector<bool>
{
	int Size;
	int index;
	int Capacity;
	int Max_Size;
	bool* array = 0;
public:

	// Default Constructor

	MyVector()
	{
		Max_Size = 1000;
		Size = 0;
		Capacity = 10;
		index = 0;
		array = new bool[Capacity];
	}

	// Parametrized Constructor

	MyVector(int size)
	{
		Max_Size = 1000;
		Size = size;
		Capacity = Size + 10;
		index = 0;
		array = new bool[Capacity];
	}

	// Copy Constructor

	MyVector(const MyVector<bool>& rhsVector)
	{
		Size = rhsVector.Size;
		Capacity = rhsVector.Capacity;
		Max_Size = rhsVector.Max_Size;
		array = new bool[Capacity];
		for (int i = 0; i < Size; i++)
		{
			array[i] = rhsVector.array[i];
		}
		index = Size;
	}

	// Overloaded Assignment Operator

	MyVector<bool>& operator=(MyVector<bool>& rhsVector)
	{
		if (this->Size > 0)
		{
			delete[]this->array;
			this->array = 0;
		}
		this->Size = rhsVector.Size;
		this->Capacity = rhsVector.Capacity;
		array = new bool[Size];
		for (int i = 0; i < Size; i++)
		{
			array[i] = rhsVector.array[i];
		}
		return *this;
	}

	// Iterator Class

	class MyIterator {
		bool* Pointer;
	public:

		// Defualt Constructor

		MyIterator()
		{
			Pointer = 0;
		}

		// Parametrized Constructor

		MyIterator(bool* Location)
		{
			Pointer = Location;
		}

		//Not Equal Operator

		bool operator!=(MyIterator otherPointer)
		{
			if (Pointer != otherPointer.Pointer)
				return true;
			return false;
		}

		// Pre Increment Operator

		MyIterator& operator++()
		{
			Pointer++;
			return *this;
		}

		// Post Increment Operator

		MyIterator& operator++(int i)
		{
			MyIterator Copy;
			Copy.Pointer = this->Pointer;
			Pointer++;
			return Copy;
		}

		//

		MyIterator& operator--()
		{
			--Pointer;
			return *this;
		}

		// *Operator

		bool& operator*()
		{
			return *Pointer;
		}

		// Operator +

		MyIterator& operator+(int number)
		{
			this->Pointer += number;
			return *this;
		}

		// Operator -

		MyIterator& operator-(int number)
		{
			this->Pointer -= number;
			return *this;
		}

		// Operator "-"

		int operator-(MyIterator& SecondIterator)
		{
			return (Pointer - SecondIterator.Pointer);
		}
	};

	// Function Begin

	MyIterator begin()
	{
		return MyIterator(array);
	}

	// Function End

	MyIterator end()
	{
		bool* End;
		if (Size > 0)
		{
			End = array + Size;
		}
		else
		{
			End = array + Size;
		}
		return MyIterator(End);
	}

	// Function Size

	int size()
	{
		return Size;
	}

	// Function Maximum Size

	int max_size()
	{
		return Max_Size;
	}

	// Function Empty

	bool empty()
	{
		return (Size > 0) ? 1 : 0;
	}

	// Overloaded Subscript Operator

	bool& operator[](int i)
	{
		if (i >= 0 && i < Size)
		{
			return array[i];
		}
	}

	// Function At

	bool& at(int i)
	{
		if (i >= 0 && i < Size)
		{
			return array[i];
		}
		else
		{
			throw - 1;
		}
	}

	// Function Front

	bool& front()
	{
		if (index == 0)
		{
			index++;
			return array[0];
		}
		return array[0];
	}

	// Function Back

	bool& back()
	{
		return array[Size - 1];
	}

	// Function Data

	bool* data()
	{
		return array;
	}

	// Function Push Back

	void push_back(bool value)
	{
		array[index] = value;
		index++;
		if (index >= Size)
		{
			Size = index;
			if (Size >= Capacity && Size < Max_Size)
			{
				Capacity = Capacity + 10;
				bool* NewArray = new bool[Capacity];
				for (int i = 0; i < Size; i++)
				{
					NewArray[i] = array[i];
				}
				delete[]array;
				array = NewArray;
			}
		}
	}

	// Function pop back

	void pop_back()
	{
		if (index > 0)
		{
			index--;
			array[index] = 0;
			Size--;
		}
	}

	// Assign Function

	void assign(int n, bool value)
	{
		for (int i = 0; i < n; i++)
		{
			array[i] = value;
		}
		Size = n;
		index = n;

	}

	// Assign Funtion

	void assign(MyIterator& start, MyIterator& terminate)
	{
		MyIterator PointerVaraiable;
		PointerVaraiable = start;
		int i = 0;
		for (; PointerVaraiable != terminate; PointerVaraiable++)
		{
			array[i] = *PointerVaraiable;
			i++;
		}
		index = i;
		for (; i < Size; i++)
		{
			array[i] = 0;
		}
		Size = index;
	}

	// Insert Function

	MyIterator insert(MyIterator& start, bool value)
	{
		if ((Size + 1) < Capacity)
		{
			MyIterator itr;
			itr = this->begin();
			int InsertingIndex = start - itr;
			int i = 0;
			for (i = Size - 1; i >= InsertingIndex; i--)
			{
				array[i + 1] = array[i];
			}
			array[InsertingIndex] = value;
			Size++;
			index++;
			return start;
		}

		else
		{
			MyIterator itr;
			itr = this->begin();
			int InsertingIndex = start - itr;
			Capacity = Capacity + 10;
			bool* NewArray = new bool[Capacity];
			for (int i = 0; i < Size; i++)
			{
				NewArray[i] = array[i];
			}
			delete[]array;
			array = NewArray;
			int i = 0;
			for (i = Size - 1; i >= InsertingIndex; i--)
			{
				array[i + 1] = array[i];
			}
			array[InsertingIndex] = value;
			Size++;
			index++;
			return MyIterator(&array[InsertingIndex]);
		}

	}

	// Erase Function

	void erase(MyIterator& start, MyIterator& End)
	{
		int StartIndexErasing = 0, LastErasingIndex = 0, position = 0;
		MyIterator itr;
		itr = this->begin();
		StartIndexErasing = start - itr;
		position = StartIndexErasing;
		LastErasingIndex = End - itr;
		for (int i = LastErasingIndex + 1; i < Size; i++)
		{
			array[position] = array[i];
			position++;
		}
		Size = position;
		index = position;
	}

	// Erase Function

	void erase(MyIterator& address)
	{
		MyIterator itr;
		itr = this->begin();
		int StartingIndex = address - itr;
		for (int i = StartingIndex; i < this->Size - 1; i++)
		{
			array[i] = array[i + 1];
		}
		Size--;
		index--;
	}

	// Clear Function

	void clear()
	{
		for (int i = 0; i < Size; i++)
		{
			array[i] = 0;
		}
		Size = 0;
		index = 0;
	}

	// Equal Equal Operator for Vectors

	bool operator==(MyVector<bool>& SecondVector)
	{
		if (this->Size == SecondVector.Size)
		{
			for (int i = 0; i < Size; i++)
			{
				if (this->array[i] != SecondVector.array[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	// Not Equal Operator for Vectors

	bool operator!=(MyVector<bool>& SecondVector)
	{
		if (this->Size == SecondVector.Size)
		{
			for (int i = 0; i < Size; i++)
			{
				if (this->array[i] != SecondVector.array[i])
				{
					return true;
				}
			}
			return false;
		}
		return true;
	}

	// Sort Function

	void Sort()
	{
		bool block;
		int StartingIndex = 0, LastIndex = 0, minimum = 0;
		for (int i = 0; i < Size - 1; i++)
		{
			minimum = i;
			for (int j = i + 1; j < Size; j++)
			{
				if (array[j] < array[minimum])
				{
					minimum = j;
				}
			}
			block = array[i];
			array[i] = array[minimum];
			array[minimum] = block;
		}
	}

	// Print Function

	void print()
	{
		for (int i = 0; i < Size; i++)
		{
			cout << array[i] << endl;
		}
	}

	// Destructor

	~MyVector()
	{
		delete[]array;
		array = 0;
		Size = 0;
		index = 0;
	}
};
