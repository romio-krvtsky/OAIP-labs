#include<bits/stdc++.h>
using namespace std;

template <typename Key, typename Value, typename Hasher = hash<Key>>
class Hashmap {

private:
    Hasher hash;
    int size;
    int max_size;
    forward_list<pair<const Key, Value>> *table;

public:

    Hashmap(int s) {
        max_size = s;
        table = new forward_list<pair<const Key, Value>>[max_size];
    }

    void Insert(pair<Key, Value> value) {
        int index = hash(value.first) % max_size;
        int size = 0;
        for (auto it : table[index]) {
            if (it.first == value.first) {
                throw domain_error("already exists");
            }
            ++size;
        }
        if (size >= max_size) {
            Rehash(max_size * 2);
            Insert(value);
        } else {
            table[index].push_front(value);
        }
    }

    void print() {

    }

    void Rehash(int newSize) {
        int oldSize = max_size;
        max_size = newSize;
        forward_list<pair<const Key, Value>> *oldList = table;
        table = new forward_list<pair<const Key, Value>>[max_size];

        for (int i = 0; i < max_size; ++i) {
            table[i] = forward_list<pair<const Key, Value>>();
        }

        for (int i = 0; i < oldSize; ++i) {
            for (auto it : oldList[i]) {
                Insert(it);
            }
        }
    }

    bool Contains(const Key key) {
        int index = hash(key) % max_size;
        for (auto it : table[index]) {
            if (it.first == key) {
                return true;
            }
        }
        return false;
    }

    void Erase(const Key key) {
        int index = hash(key) % max_size;
        auto temp = table[index].begin();
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).first == key) {
                if (it == table[index].begin()) {
                    table[index].pop_front();
                    break;
                }
                table[index].erase_after(temp);
            }
            break;
            temp = it;
        }
        --size;
    }

    void Display() {
        for (int i = 0; i < size; ++i) {
            for (auto it : table[i])
                cout << it.first << " --> " << it.second << '\n';
        }
    }

    void Clear() {
        delete[] table;
        size = 0;
    }

    ~Hashmap() {
        Clear();
    }
};
