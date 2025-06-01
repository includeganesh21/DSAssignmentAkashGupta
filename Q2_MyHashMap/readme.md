# Q2: Implement a Simplified HashMap

## 🧩 Problem Statement

Implement a simplified version of a **HashMap** (also known as an unordered map or dictionary) **without using built-in hash table libraries** like `unordered_map`, `map`, or `dict`.

### Required Operations (all average-case O(1) time):

- `put(key, value)`: Insert or update the value associated with the key.
- `get(key)`: Return the value associated with the key; return `-1` if not found.
- `remove(key)`: Remove the key and its associated value from the map.

---

## 🔧 Function Signatures

```cpp
class MyHashMap {
public:
    MyHashMap();
    void put(int key, int value);
    int get(int key);
    void remove(int key);
};
````

---

## 📘 Constraints

* Keys and values are integers.
* `0 <= key, value <= 10^6`
* Keys are unique within the map.
* Maximum number of operations: `10^5`
* **Do not use built-in hash maps or dictionaries.**

---

## 💡 Example

```cpp
MyHashMap obj;
obj.put(1, 10);
obj.put(2, 20);
obj.get(1);       // returns 10
obj.get(3);       // returns -1
obj.put(2, 30);
obj.get(2);       // returns 30
obj.remove(2);
obj.get(2);       // returns -1
```

---

## 🔗 Solution File:

[MyHashMap.cpp](./MyHashMap.cpp)

---

## 🛠️ Compile and Run

```bash
g++ MyHashMap.cpp -o myhashmap
./myhashmap
```

