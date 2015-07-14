##Interview Algorithms
Contain the general interview algorithms

### Binary Search Tree (BST)
BST: binary search tree is a sorted tree. For the key of each node:
1. is larger than the key in its left subtree, and
2. is smaller than the key in its right subtree.

General operations: insert/search/ operations, time complexity: O(log(n))

algorithms implemented for binary search tree includes:
1. insert (both recursive and non-recursive insertion solution)
2. search
3. display (both display in order and printing by layer)
4. destory/delete
5. convert a binary search tree to a doubly linked list
6. get the height of a binary search tree or binary tree
7. check whether the binary (search) tree is height-balanced
8. get the diameter of a binary search tree or binary tree
9. check whether the binary search tree is a unival tree (all nodes have the same value)
10. find/get the kth smallest element/value from a binary search tree

**Diameter:** It is the number of nodes on the longest path between two leaves in
          the tree. note that there may be more than one path in each tree.

The diameter of a tree T is the largest value of the following quantities:
* the diameter of T’s left subtree
* the diameter of T’s right subtree
* the longest path between leaves that goes through the root of T (this can be computed from the heights of the subtrees of T)


###Linked list
time complexity for insertion/search is O(n)

algorithms implemented for linked list include: 
1. insert/add a node
2. reverse a linked list (1->2->3 => 3->2->1)
3. copy the linked list with a random pointer and without changing original list
4. reverse pair/two (1->2->3->4->5 => 2->1->4->3->5)
5. find the Nth node from the end of the list
6. print
7. merge two sorted list into one sorted list


###Stack: Last in first out (LIFO)
Algorithms implemented for Stack include:
1. push an item into stack
2. pop an item from a stack
3. top - get the top item
4. isEmpty - check stack whether is is empty
5. design a stack which, in addition to push and pop, also has a function min or max
   which returns the minimum or maxinum element in O(1) time
6. size - get the number of items in stack


###Queue: First in first out (FIFO)
Algorithms implemented for Queue include:
1. enqueue - add an item into the tail of the queue
2. dequeue - pop an item from the head of the queue
3. isEmpty check
4. top - get the head item of the queue
5. tail -  get the tail item of the queue
6. size - get the size of queue


### Dynamic Programming: the key is to find the State Transition Function (STF).
**Coins problem:** Given a list/array of coins, and their values (V1, V2, ... , VN),find the minimum number of coins, the sum of which is S.
``` 
	d[i]: the minimun number of coins the sum of which is i, so d[0] = 0.
coins[j]: the value of coin j.
     STF: d[i] = min(d[i-coins[j]] + 1), a[j]<=i.
```
** Longest Increasing Subsequence (LIS) problem:** The longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. For example, length of LIS for { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is {10, 22, 33, 50, 60, 80}.
```
d[i]: LIS for sequence a[0], a[1], ..., a[i].
 STF: d[i] = max(d[j] + 1, 1); 0<=j<i and a[j] < a[i].
```

**Maximum sum of non consecutive elements:** given an array, find the maximum sum of a subsequence with the constraint that no 2 numbers in the sequence should be adjacent in the array. So 3 2 7 10 should return 13 (sum of 3 and 10) or 3 2 5 10 7 should return 15 (sum of 3, 5 and 7).
```
d[i]: Maximum sum of subsequence end of a[i].
 STF: d[i] = max(d[i-1], d[i-2] + 1), 2<=i<n.
```

**Maximum sum contiguous subsequence:** find a contiguous subseqnence (A[i], A[i+1], …, A[j]) such that the sum of the elements in that subsequence is maximized. (Note that, in general, there may be more than one such optimal subsequence.).
```
  d[i]: Maximum sum contiguous subsequence a[0],a[1], ..., a[i].
   STF: d[i] = max(d[i-1], end[i]), 1<=i<n.
end[i]: the maximun sum contiguous subsequence end of a[i].
   STF: end[i] = max(end[i-1] + a[i], a[i]).
```

**Longest common subsequence (LCS):**  Given two sequences, find the length of longest subsequence present in both of them. A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous. For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are subsequences of “abcdefg”. So a string of length n has 2^n different possible subsequences.
```
LCS[i][j]: LCS of sequence Ai(a1, a2 ... ai) and Bj(b1, b2 ... bj)
               =0, i = 0 or j = 0

STF: LCS[i][j] = LCS[i-1][j-1] + 1, if a[i] = b[j]

               =max(LCS[i-1][j], LCS[i][j-1]), if a[i] != b[j]
```

###Trie Tree or prefix tree or dict tree
a trie tree, also called prefix tree (as they can be searched by prefixes) or radix tree,it is an ordered tree data structure that is used to store a dynamic set or associative array where the keys are usually strings.

**Typical scenarios:**
1. words frequency statistics;
2. Prefix matching;

In Trie, root node is associated with the empty string. All the child nodes/descendants
of a node have a common prefix.Values are normally not associated with every node, only
with leaves and some inner nodes that correspond to keys of interest.

Algorithms implemented for trie tree include:
1. insert a word into trie tree
2. search whether a word exists
3. get the count of common prefix
4 .get the total number of words

