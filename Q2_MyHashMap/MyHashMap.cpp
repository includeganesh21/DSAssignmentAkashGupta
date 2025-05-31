#include <bits/stdc++.h>
using namespace std;

class MyHashMap {
private:
    static const int SIZE = 10007; // A prime number for bucket size
    vector<list<pair<int, int>>> buckets;

    int hashFunc(int key) {
        return key % SIZE;
    }

public:
    MyHashMap() {
        buckets.resize(SIZE);
    }

    void put(int key, int value) {
        int idx = hashFunc(key);
        for (auto& kv : buckets[idx]) {
            if (kv.first == key) {
                kv.second = value; // Update existing key
                return;
            }
        }
        buckets[idx].push_back({key, value}); // Insert new key-value
    }

    int get(int key) {
        int idx = hashFunc(key);
        for (auto& kv : buckets[idx]) {
            if (kv.first == key)
                return kv.second;
        }
        return -1; // Not found
    }

    void remove(int key) {
        int idx = hashFunc(key);
        auto& bucket = buckets[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return;
            }
        }
    }
};

// Example usage:
int main() {
    MyHashMap hashmap;
    hashmap.put(1, 10);
    hashmap.put(2, 20);
    cout << hashmap.get(1) << endl;  // Output: 10
    cout << hashmap.get(3) << endl;  // Output: -1
    hashmap.put(2, 30);
    cout << hashmap.get(2) << endl;  // Output: 30
    hashmap.remove(2);
    cout << hashmap.get(2) << endl;  // Output: -1
    return 0;
}
