# Misinformation Detection System in C

## 📌 Project Overview

This project implements a **C-based system for modeling, analyzing, and simulating the propagation of information and misinformation within a network of news articles**.

The system represents citation relationships between articles using a **directed graph** and provides several tools for network analysis, information propagation simulation, and basic misinformation detection.

The project was developed as part of the **Algorithmique et Structures de Données 2 (ASD2)** course.

## 🚀 Features

### 🔗 Graph Management

* Create and initialize a directed graph
* Load and save a network from a text file
* Add and delete articles
* Add and remove citation relationships
* Display the complete network
* Dynamically resize graph data using `realloc`

### 📊 Network Analysis

* Find articles cited by a given article
* Find articles citing a given article
* Identify original sources
* Identify isolated articles
* Find the most cited article
* Sort articles by publication date
* Find the first article citing a given article
* Display the chronological propagation chain

### 🌐 Propagation Simulation

The propagation of information is simulated using **Breadth-First Search (BFS)**.

The system:

* Starts from a selected source article
* Explores connected articles level by level
* Tracks propagation depth
* Identifies the articles reached
* Calculates the total number of affected articles

### 🚨 Misinformation Detection

The project includes a basic keyword-based misinformation detection system.

Articles are analyzed using predefined suspicious expressions and keywords. A suspicion score is calculated and converted into a reliability score.

Articles are classified as:

* **SUSPECT** — reliability score below 40
* **DOUBTFUL** — reliability score between 40 and 69
* **RELIABLE** — reliability score of 70 or above

### ⭐ Bonus Features

* Simulate the removal of an article and analyze its impact on the network
* Identify an intermediate article that can be removed to block a propagation path
* Rank suspicious articles according to the number of citations they receive

## 🛠️ Technologies & Concepts

* **C Programming**
* Directed Graphs
* Adjacency Lists
* Singly Linked Lists
* Breadth-First Search (BFS)
* Dynamic Memory Allocation
* `malloc` / `realloc` / `free`
* Structures and Pointers
* File Handling
* String Processing
* Searching and Sorting Algorithms
* Modular Programming
* Input Validation

## 📂 Project Structure

```text
.
├── main.c
├── ELTARTICLE.c
├── ELTARTICLE.h
├── liste.c
├── liste.h
├── graphe.c
├── graphe.h
├── fakesdb.h
├── donnés.txt
└── README.md
```

### File Roles

| File              | Description                                 |
| ----------------- | ------------------------------------------- |
| `main.c`          | Interactive console interface and menu      |
| `ELTARTICLE.c/.h` | Article structure and article operations    |
| `liste.c/.h`      | Generic singly linked-list implementation   |
| `graphe.c/.h`     | Directed graph management and analysis      |
| `fakesdb.h`       | Suspicious expressions and keyword database |
| `donnés.txt`      | Article and citation network dataset        |

## 📄 Data Format

The project uses a text file to store articles and citation relationships.

```text
A <id> "<title>" <source> <score> <day> <month> <year> <hour> <minute>
C <source_id> <destination_id>
```

`A` represents an article, while `C` represents a directed citation relationship between two articles.

## 🎯 Academic Objective

This project applies fundamental **data structures and algorithmic concepts** to a real-world information-management problem.

It combines linked lists and directed graphs to model relationships between news articles and uses graph traversal algorithms to analyze and simulate the propagation of information.

## 👩‍💻 Authors

**Malak Touibi**
**Chayma Yahiaoui**

Algorithmique et Structures de Données 2 — ISG Tunis

