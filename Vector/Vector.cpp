#include <iostream>
#include<iterator>
#include<initializer_list>

using namespace std;

class new_vector {

private:
	int capacity_t;
	int size_t;
	int* array;

public:

	new_vector(int size_t = 0) {
		capacity_t = 32;
		array = new int[capacity_t];
		this->size_t = size_t;
	}

	bool Empty() {
		if (size_t == 0) {
			return true;
		}
		else return false;
	}

	int Size() {
		return size_t;
	}

	//copy constructor
	new_vector(const new_vector& new2) {
		size_t = new2.size_t;
		capacity_t = new2.capacity_t;
		array = new int[new2.size_t];
		for (int i = 0; i < size_t; ++i) {
			array[i] = new2.array[i];
		}
	}

	//overload assignment operator
	new_vector& operator = (const new_vector& new2) {
		this->size_t = new2.size_t;
		this->capacity_t = new2.capacity_t;

		if (this->array != nullptr) {
			delete[] this->array;
		}
		this->array = new int[new2.size_t];

		for (int i = 0; i < size_t; ++i) {
			this->array[i] = new2.array[i];
		}
		return *this;
	}


	int& operator[](int index) {
		if (index >= 0) {
			return array[index];
		}
		else cout << "error!";
	}

	//add an element to the end of the array
	void Push_back(const int value)
	{
		if (size_t == capacity_t)
		{
			capacity_t *= 2;
			int* new_arr = new int[capacity_t];
			for (int i = 0; i < size_t; i++) {
				new_arr[i] = array[i];
			}
			delete[] array;
			array = new_arr;
		}
		array[size_t] = value;
		size_t++;
	}

	//delete all elements
	void Clear() {
		delete[] array;
		size_t = 0;
		capacity_t = 32;
		array = new int[0];
	}

	//delete the last element
	void Pop_back() {
		size_t--;
	}
	//find any index containing a specific value
	int FindSpec(int specific) {
		for (int i = 0; i < size_t; ++i) {
			if (array[i] == specific) {
				cout << i;
				return i;
			}
		}
	}

	void Resize(int new_size) {
		if (new_size > capacity_t) {
			int* new_arr = new int[new_size + 1];
			size_t = new_size;
			capacity_t = new_size + 1;
			for (int i = 0; i < size_t; i++) {
				new_arr[i] = array[i];
			}
			delete[] array;
			array = new_arr;
		}
		else {
			size_t = new_size;
		}
	}

	void Erase(int index) {
		size_t--;
		for (int i = index; i < size_t; ++i) {
			array[i] = array[i + 1];
		}
	}

	void Show() {
		for (int i = 0; i < size_t; ++i) {
			cout << array[i] << '\t';
		}
	}

	new_vector(const initializer_list<int>& list) : new_vector() {
		for (int value : list) {
			Push_back(value);
		}
	}

	~new_vector() {
		delete[] array;
	}

	class Iterator : iterator<random_access_iterator_tag, int>
	{
	public:
		Iterator(int* ptr = NULL) {
			this->ptr = ptr;
		}
		Iterator(const Iterator& it) {
			this->ptr = it.ptr;
		}
		Iterator& operator=(const Iterator& it)
		{
			this->ptr = it.ptr;
			return *this;
		}
		bool operator == (const Iterator& it)
		{
			return (ptr == it.ptr);
		}
		bool operator!=(const Iterator& it)
		{
			return !(ptr == it.ptr);
		}
		Iterator& operator++()
		{
			if (++ptr == NULL) {
				throw "incremented an empty iterator";
			}
			return *this;
		}
		Iterator& operator++(int)
		{
			if (++ptr == NULL) {
				throw "incremented an empty iterator";
			}
			return *this;
		}
		Iterator& operator+=(int a) {
			ptr += a;
			return *this;
		}
		Iterator& operator-=(int a) {
			ptr -= a;
			return *this;
		}
		Iterator& operator--()
		{
			if (--ptr == NULL) {
				throw "incremented an empty iterator";
			}
			return *this;
		}
		Iterator& operator--(int)
		{
			if (--ptr == NULL) {
				throw "incremented an empty iterator";
			}
			return *this;
		}
		int& operator*()
		{
			return *ptr;
		}
		bool operator>(const Iterator& it)
		{
			return *ptr > *it.ptr;
		}
		bool operator<(const Iterator& it)
		{
			return *ptr < *it.ptr;
		}
		bool operator<=(const Iterator& it)
		{
			return *ptr <= *it.ptr;
		}
		bool operator>=(const Iterator& it)
		{
			return *ptr >= *it.ptr;
		}
		int& operator [](int a) {
			return *(ptr + a);
		}
	private:
		int* ptr;
	};

	Iterator begin() {
		return Iterator(array);
	}
	Iterator end() {
		return Iterator(array + size_t);
	}
};




int main() {	
	//testing of vector:
	new_vector One;
	cout << "Amount of elemets in the vector:";
	int n;
	cin >> n;
	int x;
	cout << "Enter elements:";
	for (int i = 0; i < n; ++i) {
		cin >> x;
		One.Push_back(x);
	}

	cout << "The element you want to add to the end of the vector:";
	int el;
	cin >> el;
	One.Push_back(el);

	cout << "Insert the element with value 5 by index:";
	int ind;
	cin >> ind;
	One[ind] = 5;

	cout << "Delete the element with index:";
	cin >> el;
	One.Erase(el);

	cout << '\n' << "Your vector" << '\n';
	One.Show();

	cout << endl << "The last element was deleted" << endl;
	One.Pop_back();
	One.Show();

	One.Resize(40);
	One.Show();

	new_vector Two = { 1,2 ,3 ,4 ,6 };
	Two.Show();

	return 0;
}