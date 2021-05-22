#include <iostream>
#include <iterator>
#include <initializer_list>

class List {

private:

    class Node
    {
    public:
        int data;
        Node* pNext, * pPrev;

        Node(int data = 0, Node* Next = nullptr, Node* Prev = nullptr) {
            this->data = data;
            this->pNext = Next;
            this->pPrev = Prev;
        }
    };

    int size;
    Node* Head, * Tail, * last;


public:

    List() {    
        size = 0;
        Head = nullptr;
        Tail = nullptr;
        last = new Node(0, nullptr, Tail);        
    }

    int GetSize() {
        return size;
    }

    bool IsEmpty() { 
        return (size == 0);
    }

    int operator[](int index) const { 
        int counter = 0;
        Node* temp = this->Head;
        while (temp != nullptr) {
            if (counter == index) {
                return temp->data;
            }
            temp = temp->pNext;
            counter++;
        }
    }

    List& operator=(List& other) {
        Clear();
        size = 0;
        last = new Node(0, nullptr, nullptr);
        Head = nullptr;
        Tail = nullptr;
        for (auto& it : other) {
            Push_back(it);
        }
        return *this;
    }

    List(List& other) {
        Clear();
        size = 0;
        last = new Node(0, nullptr, nullptr);
        Head = nullptr;
        Tail = nullptr;
        for (auto it : other) {
            Push_back(it);
        }
    }


    void Push_back(int value) {

        Node* temp = new Node;
        temp->pNext = last;
        temp->data = value;

        if (size == 0)
        {
            temp->pPrev = nullptr;
            Head = Tail = temp;
        }
        else
        {
            temp->pPrev = Tail;
            Tail->pNext = temp;
            Tail = temp;
            last->pPrev = Tail;
        }

        size++;
    }

    void Push_front(int value) {

        Head = new Node(value, Head);
        size++;

    }

    void Pop_front() {

        Node* temp = Head;
        Head = Head->pNext;

        if (Head!=nullptr)
        {
            Head->pPrev = nullptr;
        }
        else
        {
            Tail = nullptr;
        }

        delete temp;
        size--;

    }

    void Pop_back() {

        Node* temp = Tail;
        Tail = Tail->pPrev;

        if (Tail!=nullptr)
        {
            Tail->pNext = last;
            last->pPrev = Tail;
        }
        else
        {
            Head = nullptr;
        }

        delete temp;
        size--;

    }

    void Clear() {
        while (size)
        {
            Pop_back();
        }
    }

    List(const std::initializer_list<int>& list) : List() {
        size = 0;
        Head = nullptr;
        Tail = nullptr;
        for (int value : list) {
            Push_back(value);
        }
    }

    ~List() {
        Clear();
        delete last;
    }

    

    class Iterator : std::iterator<std::bidirectional_iterator_tag, int>
    {
    private:
        Node* ptr;
    public:
        Iterator(Node* ptr = nullptr) {
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
            ptr = ptr->pNext;
            return *this;
        }
        Iterator& operator++(int) 
        {
            auto answer = this;
            ptr = ptr->pNext;
            return *answer;
        }
        Iterator& operator--()
        {
            ptr = ptr->pPrev;
            return *this;
        }
        Iterator& operator--(int) 
        {
            auto answer = this;
            ptr = ptr->pPrev;
            return *answer;
        }
        int& operator*()
        {
            return ptr->data;
        }
        int operator*() const
        {
            return ptr->data;
        }
    };

    Iterator begin() {
        return Iterator(Head);
    }
    Iterator end() {
        return Iterator(last);
    }


};

int main() {
    List arr1 = { 1, 2, 3 };
    std::cout << *(--arr1.end()) << std::endl;

    List arr = { 1, 2, 3 };
    List carr = arr;
    *(++carr.begin()) = 0;
    for (int item : arr) std::cerr << item << ' ';
    std::cerr << '\n'; 
    for (int item : carr) std::cerr << item << ' ';
    
    return 0;
}