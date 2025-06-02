# Student-Record-Management
A C++ command-line Student Management System that supports adding, updating, deleting, undoing, and printing student records using queue, stack, and binary search tree (BST) data structures. It includes persistent storage via file handling.

# Student Management System (C++ CLI Version)

A console-based Student Management System written in **C++** that allows users to manage student data using core data structures like **queue**, **stack**, and **binary search tree (BST)**. This system supports persistent storage via file handling and undo functionality using stacks.

---

# Features

- Add new student records (name, roll number, CGPA)
- Update student information with support for partial updates
- Delete student by roll number
- View all student data in ascending roll number order (inorder traversal of BST)
- Undo the last operation (Add, Update, or Delete)
- Persistent storage via `students.txt`

---

# Concepts Used

- **Queue**: For storing student records in FIFO order
- **Stack**: For storing states to implement undo functionality
- **BST (Binary Search Tree)**: For efficient searching and sorted data display
- **File Handling**: For loading and saving student data across sessions
- **OOP (Object-Oriented Programming)**: Inheritance and class-based structure

---

# How It Works

1. On program start, data is loaded from `students.txt`.
2. Users interact via a menu:
   - Add, Update, Delete, Undo, View, Exit
3. The queue is updated and pushed to a stack on every change.
4. BST is rebuilt from the queue for any data-dependent operation.
5. On exit, the data is saved back to `students.txt`.

---

# File Structure

StudentManagementSystem/
├── main.cpp
├── students.txt
└── README.md
