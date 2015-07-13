# Interview-Algorithms
Contain the general interview algorithms

1. Binary Search Tree (BST)
BST: binary search tree is a sorted tree. For the key of each node:
1) is larger than the key in its left subtree, and
2) is smaller than the key in its right subtree.

algorithms implemented in this for BST includes:

1) insert (both recursive and non-recursive solution)

2) search

3) display (both display in order and display by layer)

4) destory

5) convert a bst to a doubly lined list

6) get the height of a bt/bst

7) check whether the bst is height-balanced

8) get the diameter of a bt/bst

9) check whether the bt/bst is a unival tree (all nodes have the same value)

Diameter: It is the number of nodes on the longest path between two leaves in
          the tree. note that there may be more than one path in each tree.

The diameter of a tree T is the largest value of the following quantities:
* the diameter of T’s left subtree
* the diameter of T’s right subtree
* the longest path between leaves that goes through the root of T
  (this can be computed from the heights of the subtrees of T)

General insert/search/ operations, time complexity: O(log(n))


2. Linked list: general operation time complexity is O(n)
algorithms implemented for linked list include: 

1) insert/add a node

2) reverse a linked list (1->2->3 => 3->2->1)

3) copy the linked list with a random pointer without changing original list

4) reverse pair/two (1->2->3->4->5 => 2->1->4->3->5)

5) find the Nth node from the end of the list

6) print

7) merge two sorted list into one sorted list

