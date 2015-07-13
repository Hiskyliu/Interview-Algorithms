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

