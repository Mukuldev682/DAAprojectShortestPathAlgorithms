# Shortest Path Algorithms Visualizer (DAA Project)

## 📌 Project Overview

This project is developed as part of the **Design and Analysis of Algorithms (DAA)** course.
It demonstrates the implementation and visualization of **Shortest Path Algorithms** using the **C programming language**. The system reads graph data from input files, applies shortest path algorithms, and produces results showing the minimum distance between nodes.

The project helps students understand how shortest path algorithms work internally and how they can be applied to solve graph problems.

---

## 🎯 Objectives

* Implement shortest path algorithms in C.
* Analyze the performance of graph algorithms.
* Visualize shortest path results using a simple interface.
* Provide input and output files for testing graph data.

---

## ⚙️ Technologies Used

* **C Programming Language**
* **Graph Algorithms**
* **GTK (for basic GUI interaction)**
* **HTML (for simple visualization interface)**
* **VS Code Project Configuration**

---

## 📂 Project Structure

```
DAA(shortest path algo)/
│
├── algorithms.c           # Implementation of shortest path algorithms
├── daa.c                  # Main program file
├── graph.txt              # Input graph data
├── generated_graph.txt    # Generated graph data
├── input.txt.txt          # Additional input file
├── output.txt             # Program output results
├── result1.txt            # Stored results
├── app.html               # Basic visualization interface
│
├── build/                 # Compiled build files
├── .vscode/               # VS Code configuration
│
└── executables (.exe)     # Compiled program files
```

---

## 🧠 Algorithm Implemented

### Floyd–Warshall Algorithm

The project mainly implements the **Floyd–Warshall algorithm**, which computes the shortest paths between **all pairs of vertices** in a weighted graph.

**Key Idea:**

* It uses **dynamic programming**.
* Updates the shortest path by checking if going through an intermediate vertex gives a shorter path.

### Algorithm Complexity

* **Time Complexity:** O(V³)
* **Space Complexity:** O(V²)

Where **V** is the number of vertices in the graph.

---

## ▶️ How to Run the Project

### Step 1: Compile the Code

```bash
gcc daa.c algorithms.c -o shortest_path
```

### Step 2: Run the Program

```bash
./shortest_path
```

### Step 3: Provide Graph Input

Edit the **graph.txt** or **input file** to provide graph data.

---

## 📊 Input Format

The input file contains a **graph represented as an adjacency matrix** where:

* Each row represents a vertex
* Each column represents the distance to another vertex

Example:

```
0 3 999 7
8 0 2 999
5 999 0 1
2 999 999 0
```

Here **999 represents infinity (no direct edge).**

---

## 📤 Output

The program calculates the **shortest distance between all pairs of vertices** and saves the result in:

```
output.txt
```

Example output:

```
Shortest distance matrix:
0 3 5 6
5 0 2 3
3 6 0 1
2 5 7 0
```

---

## 🚀 Future Improvements

* Add visualization of graph paths.
* Implement more algorithms:

  * Dijkstra’s Algorithm
  * Bellman-Ford Algorithm
* Improve GUI for better interaction.
* Add real-time graph generation.

---

## 👨‍💻 Authors

Developed as a **DAA academic project** by students for learning graph algorithms and shortest path computation.

---

## 📚 Learning Outcomes

Through this project we learned:

* Graph representation in C
* Implementation of shortest path algorithms
* File handling in C
* Algorithm analysis and optimization concepts
* Basic integration of algorithm logic with visualization
