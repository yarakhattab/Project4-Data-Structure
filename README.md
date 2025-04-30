
---

# 📡 Network Routing Algorithms in C

This project implements a simple simulation of network routing using two algorithms: **Dijkstra's Algorithm** and **Breadth-First Search (BFS)**. The simulation uses a graph-based model to represent a network of routers and calculates the shortest path between two routers.

## 🚀 Features

- Graph representation using an adjacency matrix
- Dynamic addition of routers and edges (links with costs)
- Implementation of **Dijkstra's algorithm** using a Min-Heap for efficient pathfinding
- Implementation of **BFS** using a queue for basic routing
- Clear modular structure: custom Min-Heap and Queue data structures
- Handles up to 100 routers

## 🧠 Algorithms Implemented

### Dijkstra’s Algorithm
Finds the shortest path between two routers using a Min-Heap to optimize performance.

### Breadth-First Search (BFS)
Used for finding paths in unweighted graphs. Suitable for simpler routing scenarios.

## 🧱 Data Structures Used

- **Graph**: Represented using a 2D adjacency matrix.
- **Queue**: Custom linked list-based queue used in BFS.
- **Min-Heap**: Custom heap used for Dijkstra's algorithm to find the next closest router.

## 🗂 File Structure

- `main.c` — Core logic for graph creation, queue, heap, Dijkstra and BFS implementation.
- `graph struct` — Contains router names and cost matrix.
- `heap and queue structs` — Support efficient routing operations.



## 📄 Output

The shortest or first-found path between two routers will be printed along with the total cost, depending on the selected algorithm.

## 📚 Example

Suppose you have routers A, B, and C, with edges:

- A-B (cost 2)
- B-C (cost 3)
- A-C (cost 6)

Running Dijkstra from A to C will return the path A → B → C with total cost 5.

## ✍️ Author:
Name: Yara Khattab


📧 Email: yarakhattab16@gmail.com



🔗 GitHub: github.com/yarakhattab

---

Feel free to update it further based on your preferences. Let me know if you'd like any other changes! 😊


