
# Q1: Least Recently Used (LRU) Cache

## 🧩 Problem Statement

Design and implement a **Least Recently Used (LRU) Cache**. A cache has a fixed capacity, and when it exceeds that capacity, it must evict the **least recently used** item to make space for the new one.

Implement the following operations:

- `get(key)`: Return the value of the key if it exists in the cache, otherwise return `-1`.
- `put(key, value)`: Update or insert the value. If the cache is full, remove the least recently used item before inserting.

---

## 🔧 Function Signatures

```cpp
class LRUCache {
public:
    LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);
};
````

---

## 📘 Constraints

* `1 <= capacity <= 3000`
* `0 <= key, value <= 10^4`
* Maximum number of operations: `10^5`
* All operations must be done in **O(1)** time complexity

---

## 💡 Example

**Input:**

```cpp
LRUCache lru(2);  
lru.put(1, 1);
lru.put(2, 2);
lru.get(1);       // returns 1
lru.put(3, 3);    // evicts key 2
lru.get(2);       // returns -1
lru.put(4, 4);    // evicts key 1
lru.get(1);       // returns -1
lru.get(3);       // returns 3
lru.get(4);       // returns 4
```

**Output:**

```
1
-1
-1
3
4
```
## 📁 Source Code

👉 [LRUCache.cpp](./LRUCache.cpp)

---

## 🛠️ How to Compile

```bash
g++ LRUCache.cpp -o lru
./lru
```


