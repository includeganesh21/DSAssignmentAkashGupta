#include <bits/stdc++.h>
using namespace std;

// LRU Cache Class
class LRUCache {
public:
    // Doubly linked list node class
    class node {
    public:
        int key;
        int val;
        node* next;
        node* prev;

        node(int _key, int _val) {
            key = _key;
            val = _val;
        }
    };

    node* head = new node(-1, -1); // Dummy head node
    node* tail = new node(-1, -1); // Dummy tail node
    int cap;                       // Capacity of the cache
    unordered_map<int, node*> m;  // Key to node mapping

    // Constructor
    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    // Adds a node right after the head
    void addnode(node* newnode) {
        node* temp = head->next;
        newnode->next = temp;
        newnode->prev = head;
        head->next = newnode;
        temp->prev = newnode;
    }

    // Removes a node from the list
    void deletenode(node* delnode) {
        node* delprev = delnode->prev;
        node* delnext = delnode->next;
        delprev->next = delnext;
        delnext->prev = delprev;
    }

    // Retrieves the value of the key if present, else returns -1
    int get(int key_) {
        if (m.find(key_) != m.end()) {
            node* resnode = m[key_];
            int res = resnode->val;
            m.erase(key_);
            deletenode(resnode);       // Move node to front
            addnode(resnode);
            m[key_] = head->next;
            return res;
        }
        return -1;
    }

    // Inserts a new key-value pair or updates an existing one
    void put(int key_, int value) {
        if (m.find(key_) != m.end()) {
            node* existingnode = m[key_];
            m.erase(key_);
            deletenode(existingnode);  // Remove old node
        }
        if (m.size() == cap) {
            // Remove least recently used node
            m.erase(tail->prev->key);
            deletenode(tail->prev);
        }

        addnode(new node(key_, value));  // Insert new node at front
        m[key_] = head->next;
    }
};

// Sample test code
int main() {
    LRUCache lru(2);  

    lru.put(1, 1);
    lru.put(2, 2);
    cout << lru.get(1) << endl;    // returns 1
    lru.put(3, 3);                 // evicts key 2
    cout << lru.get(2) << endl;    // returns -1 (not found)
    lru.put(4, 4);                 // evicts key 1
    cout << lru.get(1) << endl;    // returns -1 (not found)
    cout << lru.get(3) << endl;    // returns 3
    cout << lru.get(4) << endl;    // returns 4

    return 0;
}
