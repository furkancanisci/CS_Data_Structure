# CS Data Structures - Analysis & Implementation

A comprehensive exploration of fundamental data structures with implementations in **Python** and **C++**, including detailed analysis, complexity metrics, and real-world scenarios.

## 📋 Project Overview

This project implements and analyzes three critical data structures used in computer science and databases:

1. **Hash Table** - Collision handling with chaining
2. **Heap & Priority Queue** - Emergency service simulation
3. **B+ Tree** - Database indexing and range queries

Each structure is implemented in both Python and C++ for comparison and learning.

---

## 🏗️ Project Structure

```
cs_data_structure/
├── README.md                    # This file
├── BPlusTree_Analysis.md        # Detailed roadmap and pseudocode
├── src/
│   ├── python/
│   │   ├── hash_table.py        # Hash table with chaining
│   │   ├── heap_priority_queue.py   # Emergency queue simulation
│   │   └── bplus_tree.py        # B+ tree implementation
│   └── c++/
│       ├── hash_table.cpp       # C++ hash table
│       ├── heap_priority_queue.cpp  # C++ priority queue
│       └── bplus_tree.cpp       # C++ B+ tree
```

---

## 📚 Data Structures

### 1. Hash Table (Chaining)

**Purpose**: Fast key-value lookups with collision handling.

**Features**:
- Custom hash function (character-weighted)
- Chaining for collision resolution
- `insert()`, `get()`, `delete()` operations

**Run Python version**:
```bash
python src/python/hash_table.py
```

**Run C++ version**:
```bash
g++ -std=c++17 src/c++/hash_table.cpp -o hash_table && ./hash_table
```

**Example Output**:
```
Bucket 0: [('Furkan', 'Computer Engineer')]
Bucket 1: [('Python', 'Language'), ('Data', 'Structure')]
Bucket 2: [('Gemini', 'AI Assistant')]
Bucket 3: [('Kocaeli', 'University')]
```

---

### 2. Heap & Priority Queue

**Purpose**: Process tasks/patients based on priority, not FIFO order.

**Scenario**: Hospital Emergency Department
- Patients arrive with varying severity levels (1-10)
- Higher severity treated first
- Tie-breaker: earlier arrival

**Features**:
- `push()` - Add patient with severity
- `pop()` - Get and remove highest priority patient
- `peek()` - View next patient without removal
- 24-event simulation with mixed operations

**Run Python version**:
```bash
python src/python/heap_priority_queue.py
```

**Run C++ version** (after fix):
```bash
g++ -std=c++17 src/c++/heap_priority_queue.cpp -o heap_pq && ./heap_pq
```

### 3. B+ Tree

**Purpose**: Efficient indexing for databases with support for range queries.

**Run Python version**:
```bash
python src/python/bplus_tree.py
```

**Run C++ version**:
```bash
g++ -std=c++17 src/c++/bplus_tree.cpp -o bplus_tree && ./bplus_tree
```

---

## 📊 Big O Complexity Cheat Sheet

| Data Structure | Search | Insert | Delete | Notes |
|---|---|---|---|---|
| Array (unsorted) | O(n) | O(1) append; O(n) insert position | O(n) | - |
| Array (sorted) | O(log n) binary | O(n) | O(n) | Maintain order cost |
| BST (average) | O(log n) | O(log n) | O(log n) | - |
| BST (worst) | O(n) | O(n) | O(n) | Unbalanced tree |
| AVL Tree | O(log n) | O(log n) | O(log n) | Self-balancing |
| B+ Tree | O(log n) | O(log n) | O(log n) | Optimized for I/O |
| Hash Table (avg) | O(1) | O(1) | O(1) | Good distribution |
| Hash Table (worst) | O(n) | O(n) | O(n) | All collisions |
| Heap | O(n) | O(log n) | O(log n) | insert worst: O(n) |

---

##  Key Takeaways

### Hash Tables
- ✅ O(1) average access
- ⚠️ Collision cost when poorly distributed
- 💡 Used in: Caches, symbol tables, databases for lookups

### Priority Queues (Heaps)
- ✅ O(1) peek at highest priority
- ✅ O(log n) insert/remove
- 💡 Used in: Task scheduling, Dijkstra's algorithm, OS process management

### B+ Trees
- ✅ Balanced growth (never O(n) lookup)
- ✅ Optimized for disk access patterns
- ✅ Excellent range query support
- 💡 Used in: Database indexes (PostgreSQL, MySQL, InnoDB)

---

## � License

This project is for educational purposes. Feel free to use and modify.

---

**Last Updated**: March 30, 2026

Happy Learning! 🚀
