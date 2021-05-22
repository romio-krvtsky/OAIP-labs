#include <iostream>
#include <iterator>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

class Set {
private:
    Node* root;
    int size;
    Set* bst;

    Node* insert(Node* node, int d) {
        if (node == NULL) {
            node = new Node(d);
        }
        else if (d < node->data) {
            node->left = insert(node->left, d);
        }
        else if (d > node->data) {
            node->right = insert(node->right, d);
        }
        return node;
    }

    Node* find(Node* node, int d) {
        if (node == NULL || node->data == d) {
            return node;
        }
        else if (d < node->data) {
            return find(node->left, d);
        }
        else if (d > node->data) {
            return find(node->right, d);
        }
    }

    Node* clear(Node* node) {
        if (node == NULL) {
            return NULL;
        }
        else {
            clear(node->left);
            clear(node->right);
            delete node;
        }
        return NULL;
    }

    Node* minimum(Node* node) {
        if (node->left == NULL) {
            return node;
        }
        else {
            return minimum(node->left);
        }
    }

    Node* maximum(Node* node) {
        if (node->right == NULL) {
            return node;
        }
        else {
            return maximum(node->right);
        }
    }

    Node* erase(Node* node, int d) {
        Node* temp;
        if (node == NULL) {
            return NULL;
        }
        else if (d < node->data) {
            node->left = erase(node->left, d);
        }
        else if (d > node->data) {
            node->right = erase(node->right, d);
        }
        else if (node->left && node->right) {
            temp = minimum(node->right);
            node->data = temp->data;
            node->right = erase(node->right, node->data);
        }
        else {
            temp = node;
            if (node->left == NULL) {
                node = node->right;
            }
            else if (node->right == NULL) {
                node = node->left;
            }
            delete temp;
        }
        return node;
    }

public:

    Set() {
        root = NULL;
        size = 0;
    }

    void Insert(int d) {
        root = insert(root, d);
        ++size;
    }

    void Find(int d) {
        root = find(root, d);
    }

    void Erase(int d) {
        root = erase(root, d);
        --size;
    }

    int Next(int d) {
        Node* temp = root, * child = NULL;
        while (temp) {
            if (temp->data > d) {
                child = temp;
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        return child->data;
    }

    int Prev(int d) {
        Node* temp = root, * child = NULL;
        while (temp) {
            if (temp->data < d) {
                child = temp;
                temp = temp->right;
            }
            else {
                temp = temp->left;
            }
        }
        return child->data;
    }

    int Size() {
        return size;
    }

    bool Empty() {
        return size == 0;
    }

    ~Set() {
        root = clear(root);
    }

    class Iterator : std::iterator< std::bidirectional_iterator_tag, int> {
    private:
        int key;
        Set* bst;
    public:
        Iterator(Set **bst, int key) {
            this->key = key;
            this->bst = reinterpret_cast<Set *>(bst);
        }
        Iterator(const Iterator& it) {
            this->key = it.key;
            this->bst = it.bst;
        }
        Iterator& operator=(const Iterator& it) {
            this->key = it.key;
            this->bst = it.bst;
            return *this;
        }
        Iterator& operator++() {
            key = bst->Next(key);
            return *this;
        }
        Iterator& operator--() {
            key = bst->Prev(key);
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            key = bst->Next(key);
            return temp;
        }
        Iterator operator--(int) {
            Iterator temp = *this;
            key = bst->Prev(key);
            return temp;
        }
        bool operator==(const Iterator& it) {
            return (key == it.key && bst == it.bst);
        }
        bool operator!=(const Iterator& it) {
            return (key != it.key || bst != it.bst);
        }
        const int operator*() {
            return key;
        }
    };

    Iterator begin() {
        Iterator it(&bst, reinterpret_cast<int>(bst->minimum(root)));
        return it;
    }
    Iterator end() {
        Iterator it(&bst, reinterpret_cast<int>(bst->maximum(root)));
        return it;
    }

};
