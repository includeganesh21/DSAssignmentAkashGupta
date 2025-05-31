
---

### ✅ `Q1_LRUCache/README.md` (Detailed per-question readme)

```markdown
# Q1: Least Recently Used (LRU) Cache

## 🧩 Problem

Implement an **LRU (Least Recently Used) Cache** that supports the following operations in `O(1)` average time complexity:

- `get(key)`: Return the value if key exists, else return `-1`.
- `put(key, value)`: Insert or update the value. Evict the least recently used item if the cache exceeds capacity.

---

## 📘 Constraints

- 1 <= capacity <= 3000  
- 0 <= key, value <= 10^4  
- Up to 10^5 operations  
- All operations must be O(1)

---

## 💡 Approach

We use:

- A **doubly linked list** to maintain the usage order (most recent at front).
- An **unordered map** to provide O(1) access by key.

Whenever a key is accessed or updated, its node is moved to the front. When capacity is reached, we remove the node at the end (least recently used).

---

## 🔍 Sample Usage

```cpp
LRUCache cache(2);
cache.put(1, 1);
cache.put(2, 2);
std::cout << cache.get(1) << std::endl; // 1
cache.put(3, 3);                        // evicts key 2
std::cout << cache.get(2) << std::endl; // -1
