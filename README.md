# programming
There are some programming topics.

## Topic 1
This topic is to compare the executive time of different sorted array.  

There are three array by different sorting.  

### In sorting.c
caseA is ascending, caseB is descending, and caseC is random.  
This file use bubble sort, selection sort, and heap sort.  
Calculating the average time to nine decimal places.  

The result shows:  

<img src=https://github.com/neneyhsw/programming/blob/main/sorting_results.png width="400" height="300">  

## Topic 2
This topic design a binary search tree.  

### In binary_search_tree.c
This program use different inorder, preorder, and postorder travelsal.  
Users have 5 options, include print travelsal, insert node, delete node, Search node, and leave.  
when the user choose 1 to 4, it will show the tree in terminal.  
This file is implemented by pointer and linked list.  
The tree figure refer to below:  

reference: https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console


The Tree in cmd shows:  

<img src=https://github.com/neneyhsw/programming/blob/main/show_tree.png width="400" height="350">  

## Topic 3 (Two Sum)
### In two_sum.cpp
This problem is Two Sum.  
The answer needs to be returned the index of list from the input list.  
In two_sum.cpp, there are two solutions.  
One solves two sum problem by two for loop. Its time complexity is O(n^2).  
Another solution use hash map. It can improve time complexity to O(n).

Problem reference: https://leetcode.com/problems/two-sum/  

## Topic 4 (Gale Shapley Algorithm)
### In Gale_Shapley_Algorithm.cpp
This problem is stable marriage problem.  
It needs to macth N man and N woman by their preference.  
It has two strategies, man proposes to woman and woman proposes to man.  
