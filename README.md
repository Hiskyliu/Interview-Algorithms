# Interview-Algorithms
Contain the general interview algorithms

1. Binary Search Tree (BST)
BST: binary search tree is a sorted tree. For the key of each node:
1) is larger than the key in its left subtree, and
2) is smaller than the key in its right subtree.

General operations: insert/search/ operations, time complexity: O(log(n))

algorithms implemented for binary search tree includes:

1) insert (both recursive and non-recursive insertion solution)

2) search

3) display (both display in order and printing by layer)

4) destory/delete

5) convert a binary search tree to a doubly linked list

6) get the height of a binary search tree or binary tree

7) check whether the binary (search) tree is height-balanced

8) get the diameter of a binary search tree or binary tree

9) check whether the binary search tree is a unival tree (all nodes have the same value)

10) find/get the kth smallest element/value from a binary search tree

Diameter: It is the number of nodes on the longest path between two leaves in
          the tree. note that there may be more than one path in each tree.

The diameter of a tree T is the largest value of the following quantities:
* the diameter of T’s left subtree
* the diameter of T’s right subtree
* the longest path between leaves that goes through the root of T
  (this can be computed from the heights of the subtrees of T)


2. Linked list: time complexity for insertion/search is O(n)
algorithms implemented for linked list include: 

1) insert/add a node

2) reverse a linked list (1->2->3 => 3->2->1)

3) copy the linked list with a random pointer and without changing original list

4) reverse pair/two (1->2->3->4->5 => 2->1->4->3->5)

5) find the Nth node from the end of the list

6) print

7) merge two sorted list into one sorted list



3. Stack: Last in first out (LIFO)

Algorithms implemented for Stack include:

1) push an item into stack

2) pop an item from  stack

3) top get the top item

4) isEmpty() check

5) design a stack which, in addition to push and pop, also has a function min or max
   which returns the minimum or maxinum element in O(1) time


4. Queue: First in first out (FIFO)

Algorithms implemented for Queue include:

1) enqueue - add an item into the tail of the queue

2) dequeue - pop an item from the head of the queue

3) isEmpty check

4) top - get the head item of the queue

5) tail -  get the tail item of the queue

6  size - get the size of queue
