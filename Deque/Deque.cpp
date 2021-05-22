#include <iostream>
#include <vector>

#define cout std::cout

class Block
{
private:
	int* cell;

public:
	Block()
	{
		cell = new int[5];
	}

	int& Cell(const int index)
	{
		return cell[index];
	}


};

class Deque: Block
{
private:
	std::vector<Block*> blocks;
	int N;// N - amount of blocks
	int front;
	int back;
	int size;
	int block_number;
	int cell_index;
	bool Checking()
	{
		return (back / 5 == front / 5 && back % 5 < front % 5);
	}

	void Resize(bool route)
	{
		if (route) {
			for (int i = 0; i < N; ++i) {
				Block* temp = new Block;
				blocks.insert(blocks.begin() + back / 5, temp);
			}
		}
		else {
			for (int i = 0; i < N; ++i) {
				Block* temp = new Block;
				blocks.insert(blocks.begin() + (front + 1) / 5, temp);
			}
		}
		front += N * 5;
		N *= 2;
	}

	void Clear()
	{
		for (int i = 0; i < N; ++i) {
			delete[] blocks[i];
		}
		blocks.clear();
		N = 5;
		front = 0;
		back = 0;
		size = 0;
	}


public:

	Deque()
	{
		N = 5;
		front = 0;
		back = 0;
		for (int i = 0; i < N; ++i) {
			Block* temp = new Block;
			blocks.push_back(temp);
		}
	}

	int& operator[](const int index)
	{
		if (index < back) {
			block_number = (front + index) / 5;
			cell_index = (front + index) % 5;
			return (*blocks[block_number]).Cell(cell_index);
		}
		else {
			block_number = (index - back) / 5;
			cell_index = (index - back) % 5;
			return (*blocks[block_number]).Cell(cell_index);
		}
	}

	void Push_back(int value)
	{
		if (back) {
			if (Checking()) {
				Resize(true);
			}
			block_number = back / 5;
			cell_index = back % 5;
			(*blocks[block_number]).Cell(cell_index) = value;			
		}
		else {
			(*blocks[0]).Cell(0) = value;
		}

		size++;
		back++;
	}

	 void Push_front(int value)
	{
		if (front) {
			--front;
			if (Checking()) {
				Resize(false);
			}
			block_number = front / 5;
			cell_index = front % 5;
			(*blocks[block_number]).Cell(cell_index) = value;
			
		}
		else {
			front = N * 5 - 1;
			block_number = front / 5;
			cell_index = front % 5;
			(*blocks[block_number]).Cell(cell_index) = value;
		}
		size++;
	}

	void Pop_back()
	{
		if (back) {
			size--;
			back--;
		}
		else
			cout << "empty!";
	}

	void Pop_front()
	{
		if (front < 5 * N) {
			size--;
			front++;
		}
		else
			cout << "empty!";
	}

	int Size()
	{
		return size;
	}

	bool Empty()
	{
		return (size == 0);
	}

	~Deque()
	{
		Clear();
	}

	class Iterator : std::iterator<std::random_access_iterator_tag, int>
	{
	public:
		Iterator(Deque* d, int i)
		{
			this->ptr = d;
			this->index = i;
		}

		Iterator& operator=(const Iterator& it)
		{
			this->ptr = it.ptr;
			this->index = it.index;
			return *this;
		}

		Iterator& operator+(int step)
		{
			Iterator temp(*this);
			temp.index += step;
			return temp;
		}

		Iterator operator-(int step)
		{
			Iterator temp = *this;
			temp.index -= step;
			return temp;
		}

		Iterator& operator++()
		{
			++this->index;
			return *this;
		}

		Iterator& operator--()
		{
			--this->index;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp = *this;
			++this->index;
			return temp;
		}

		Iterator operator--(int)
		{
			Iterator temp = *this;
			--this->index;
			return temp;
		}

		bool operator!=(const Iterator& it)
		{
			if (this->ptr != it.ptr || this->index != it.index)
				return true;
			return false;
		}

		bool operator==(const Iterator& it)
		{
			if (this->ptr == it.ptr && this->index == it.index)
				return true;
			return false;
		}

		bool operator>(const Iterator& it)
		{
			return (this->ptr->operator[](this->index) > it.ptr->operator[](it.index));
		}

		bool operator<(const Iterator& it)
		{
			return (this->ptr->operator[](this->index) < it.ptr->operator[](it.index));
		}

		bool operator>=(const Iterator& it)
		{
			return (this->ptr->operator[](this->index) >= it.ptr->operator[](it.index));
		}

		bool operator<=(const Iterator& it)
		{
			return (this->ptr->operator[](this->index) <= it.ptr->operator[](it.index));
		}

		int& operator*()
		{
			return this->ptr->operator[](this->index);
		}

		int& operator[](const int step)
		{
			return this->ptr->operator[](this->index + step);
		}

	private:
		Deque* ptr;
		int index;
	};

	Iterator begin()
	{
		Iterator temp(this, 0);
		return temp;
	}

	Iterator end()
	{
		Iterator temp(this, this->Size());
		return temp;
	}

};




int main()
{
	Deque dq1;
	dq1.Push_front(1);
	dq1.Push_front(2);
	dq1.Push_front(3);
	dq1.Push_front(4);
	dq1.Push_front(0);
	dq1.Push_back(5);
	dq1.Push_back(6);
	dq1.Push_back(7);
	dq1.Push_back(8);
	dq1.Push_back(555);


	for (int i = 0; i < dq1.Size(); ++i) {
		cout << dq1[i] << " ";
	}

	cout << '\n';

	cout << *(dq1.begin()) << '\n';
	cout << *(--dq1.end());



	return 0;
}
