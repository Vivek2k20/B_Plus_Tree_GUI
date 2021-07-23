# B+ Tree
Implementing B+ tree using C++.
This is a GUI Version developed using Winforms of .NET Framework on Visual Studio 2019.
A Simpler,Easy to run CLI Version of the same has also been developed. You can view the project
here : https://github.com/Vivek2k20/B_plus_Tree
- [X] Import
- [x] Search 
- [X] Insert
- [X] Delete
- [X] Structuring the main Function


## Usage :

1.  Open the Project on Visual Studio 2019 as C++ WinForms(.NET Framework) Project.

2.  Make sure that you do/have the following things : 

	a.	Windows Implementation of bits/stdc++.h and dirent.h in your MSVC compiler.
	
	b.	In the Linker section of the properties of the project,SDL Checks are turned OFF
	
  	c.  	VS2019 adds "/FORCE:UNRESOLVED" as an additional option during compilation in the commandline.
	
  	d.  	The C/C++ language version is set to 17.

3. 	After ensuring the above,Just run the project.





## Summary- What is the project all about? 

This project is small version of database system. Where we efficiently implement the B+ Tree for fast and efficient access
of files in the disc. Your database tuples will be stored as a .txt file in DBFiles folder corresponding FILE* will be saved in the 
leaf node. Above step is done to mimic the disc-block access. If we want to make more tables then we can make that many BPTree objects !!
The code can easily be scaled to implement B+ Tree for other types of records(PDF,Image,etc) in real life environments. The import option
also enables inserting of multiple existing records into the B+ Tree at the same time.

## Assumptions in our Tree :

1.	We are making a right biased tree. By this we mean if maxLimits are even we will split them
	in such a way that right sibling has one element greater.

2.	Insertion is based on the primary key. Hence all the properties of the primary key has to be followed.
	No dublicate insertion has to be done with same primary key!

3.	We are saving the \*ptr2next explicitly while ideally it is saved as the last pointer in the pointerset. But here as we 
	are using union to save the memory and seperate the leaf and non-leaf nodes, because of this \*ptr2next is explicitly
	saved !!


## Some UseFul Properties of B+ Tree:

1. B+ Tree Unlike B Tree is defined by two order values one for leaf node and another for non-leaf node.
	Minimum 50% should hold on B+ Tree Node.
	
	a.	For Non-Leaf Nodes-
		i.	ceil(maxInternalLimit/2)<= #of children <= maxInternalLimit
		ii.	ceil(maxInternalLimit/2)-1<= #of keys <= maxInternalLimit-1
		
	b.	For Leaf Nodes-
		i.	ceil(maxLeafLimit/2)<= #of keys <= maxLeafLimit
		ii.	since Leaf node will point to the dataPtr. It will be of same size as maxLeafLimit to correspond
			to every key !!!



## Search:

1.	If x is non-leaf node, we seek for the first *i* for which **keyValue** which is greater 
	than or equal-to the key k searched for. After that search continues in the node pointed 
	by ***iptr2Tree***.

2.	If all the **keyValue** are smaller than k then, we continue to search in the node pointed
	by ***(maxInternalLimit)ptr2Tree***.

3.	If x is a leaf-node, we search if k is present in the node!




## Insertion:

There are two convention being followed for the insertion(according to the google what i found out)
where, if the current node becomes full then -

1.	First give an element to the left sibling and if that doesn't
work give an element to the right sibling and if this also doesn't work split it.

2.	Simply Split into two nodes.

**Major Drawback of 1**
	Increases I/O, especially if we	check both siblings!!!


We have followed 2nd method which was comparatively easy to implement with relatively less hustle. So, 
here is the complete algorithm for [reference](http://www.cburch.com/cs/340/reading/btree/index.html?fbclid=IwAR0QFRcpIVL19PdMtZU0-wG18f-rwGS4lNvzpEAsdaZCL7BrNRBuFffiPJ0)

Descend to the leaf node where leaf fits :

a.	If the node has empty space, insert the key/reference pair into the node and We are DONE!

b.	If the node is already full, split it into two nodes, distributing the keys evenly. 

	i.	If the node is leaf,take the copy of minimum in the second node and repeat this algorithm to 
		insert it in parent node.
		
	ii.	If the node is non-leaf, exclude the middle value during split and insert the excluded value into 
		the	parent.
