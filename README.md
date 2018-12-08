# Scapegoat-Tree-vs-Treap
Comparative study of advanced data structures featuring Scapegoat Trees and Randomized binary search trees


## Definitions & Algorithms: 
Adapted From Wikipedia:

#### Treap :

> The treap and the randomized binary search tree are two closely related forms of binary search tree data structures that maintain a dynamic set of ordered keys and allow binary searches among the keys. After any sequence of insertions and deletions of keys, the shape of the tree is a random variable with the same probability distribution as a random binary tree; in particular, with high probability its height is proportional to the logarithm of the number of keys, so that each search, insertion, or deletion operation takes logarithmic time to perform. The treap was first described by Raimund Seidel and Cecilia R. Aragon in 1989, its name is a portmanteau of tree and heap. It is a Cartesian tree in which each key is given a (randomly chosen) numeric priority. As with any binary search tree, the inorder traversal order of the nodes is the same as the sorted order of the keys. The structure of the tree will be determined by the priority of each node, either using the MAXHEAP or MINHEAP properties. The heap property will be ensured using left and right rotations. This will ensure that the BST and MAXHEAP properties are both kept in check.


#### Scape Goat Tree :

> The Scapegoat tree is a self-balancing binary search tree, invented by Arne Anderssonnand again by Igal Galperin and Ronald L. Rivest. It provides worst-case O(log n) lookup time, and O(log n) amortized insertion and deletion time. Unlike most other self-balancing binary search trees which provide worst case O(log n)  ~~(Red-Black-Trees or Avl-Trees)~~ lookup time, scapegoat trees have no additional per-node memory overhead compared to a regular binary search tree: a node stores only a key and two pointers to the child nodes. This makes scapegoat trees easier to implement and, due to data structure alignment, can reduce node overhead by up to one-third. Instead of balancing after every insertion/deletion/search, scapegoat trees will rarely but **expensively** find a scapegoat (using equations that utilize a preset parameter α) and will rebuild the entire subtree (into a balanced shape) about the scapegoat.


#### Supported Operations:
Where x is with the key of a node carrying certain information.
- Search (x)
- Insert (x) 
- Delete (x)
- Predecessor (x)
- Successor (x)
- Replicate_Sub_Tree (x)
- Count Nodes (x)
- Find Min ()
- Find Max ()

### Implementation/Algorithms:
___
First Let Us Define the common operations that both types of trees will build upon:

#### Common Operations (BST):

#### Search(x):
Apply the standard BST Search that relies on the BST Search Property where:
```
For every Node N with key K:
Every Node to the right of N has key x >= K
Every Node to the left of N has key x < K
```
Psuedocode:
```C++
Void Search(Node* Root, int key) {
  if (root == nullptr)
    Not Found
    return;
  else if (Root->value == key)
    Found
    return;
  else if (key >= Root->value)
    Search(Root->right, key);
  else if (key < Root->value)
    Search(Root->left, key);
}
```

#### Insert (x):

We simply use the search algorithm and attach it to where we fall off the tree (Hit a NULL leaf).

#### Delete(x):

1 - Find node N containing x

2 - If Node N has no children --> Delete the node

3 - If node N has one child --> Attach parent and child together --> Delete the Node 

4 - If node N has 2 children --> Swap N And Successor(N) --> Delete(N) // Recursive call

#### Find Min (x):

Keep going left from the root, the node where preceeding the NULL leaf will contain the minimum key.


#### Find Max (x):

Keep going right from the root, the node where preceeding the NULL leaf will contain the minimum key.


#### Successor (x): //Return the next largest key after x in the tree
```
Start at root of tree:
- If there is a right subtree --> Return it's minimum using above algorithm
-  Else, Keep going up the tree until you reach a node with it's parent on the right --> Return Parent
```

#### Predecessor (x): //Return the next largest key preceding x in the tree
```
Start at root of tree:
- If there is a left subtree --> Return it's maximum using above algorithm
-  Else, Keep going up the tree until you reach a node with it's parent on the left --> Return Parent
```

#### Replicate_Sub_Tree (x): //Just a fun function, use it if you need to
```
- Start at node K with key x
- Create a new node N with key x
- Recursively go down the left and right subtrees of K and replicate the subtree starting with node N --> Return N at the end as the root of the new replicated subtree.
```
#### Count Nodes (x):
Count the number of nodes starting with node that has key x --> Recursively
```C++
Count_Nodes (Root):
  if(Root){
  return 1 + Count_Nodes(Root->right) + Count_Nodes(Root->left);
  }
  else{
  return 0;
  }
```

___


### Treap Specific Algorithms:

Let Us Define Tree Rotations First:

![alt text](https://github.com/YahiaBakour/Scapegoat-Tree-vs-Treap/blob/master/Images/Tree_rotation.png)

#### Insert (x) :

**Steps:**

1 - Create a Node with key X and Randomized priority P

2 - Perform a regular BST Insert  

3 - Rotate node up until MaxHeap Property Satisfied

```
Create a Node N with key x and random priority 
Insert N into the TREAP using regular BST insert
while(N->Priority < N->Parent->Priority){
	if (N == N->Parent->right){
		leftrotate(N->Parent);
		}
	else{
		rightrotate(N->Parent);
	}
}
```

#### Delete (x) :

Steps for deletion:

1 - If the node containing key x has 2 children --> follow the following algorithm to rotate it down until it has 1 child or no children
```C++
  while(Node->right != nullptr && Node->left != nullptr){
	  if(Node->right->priority >= Node->priority){
		  leftrotate(temp);
	  } else{
		  rightrotate(temp);
	  }
  }
```
Then delete it using the regular BST delete algorithm (For one child and no children)


___

### Scape Goat Tree Specific Algorithms:

First Let us define a Scapegoat tree specific function Size(Node):
```
Size(Node):
  if(Node) return 1 + Size(Node->right) + Size(Node->left)
  else return 0
```


#### Insert (x):

1 - Insert using regular BST Insert but make sure to calculate the depth of the node

2 - If the node causes the tree to violate the following property --> Find a scapegoat and rebalance upon it:

```
height(tree) ≤ ⌊log1/α(size(tree))⌋
```

where α is a parameter decided upon prior to the creation of the tree:

- an α of 0.5 would be a perfectly balanced BST

- an α of 1 would be a linked list


3 - To find a scapegoat, we must keep going up the tree untill we find a node with the following property

```
size(left) ≤ α*size(node)
size(right) ≤ α*size(node)
```



#### Delete(x):

We perform a regular BST delete and check the following condition: 
```
if (NodeCount ≤ α*MaxNodeCount):
  rebuild entire tree about root
```

where the maximum number of nodes in the treap is defined by the following:
```
MAXNODES = (MAXNODES < CURRNODES) ? CURRNODES : MAXNODES;
```
So the maximum number of nodes will only differ from the current number of nodes if we delete nodes.


### Results:

<img src="https://github.com/YahiaBakour/Scapegoat-Tree-vs-Treap/blob/master/Images/Insertion%20Time%20vs%20Input%20Size.png" ><img src="https://github.com/YahiaBakour/Scapegoat-Tree-vs-Treap/blob/master/Images/search%20time%20vs%20input%20size.png" ><img src="https://github.com/YahiaBakour/Scapegoat-Tree-vs-Treap/blob/master/Images/Delete%20Time%20vs%20input%20size.png" >

Things to Note:

- This is my implementation of both datastructures, they could be improved with a more sophistocated implementation.
- All scapegoat trees are lagging in speed when compared to the treap. This is due to the rebuilding operation in the scapegoat tree where we rebuild the entire subtree about a node. 

**Libraries Used:**
- CSV Parser from https://github.com/AriaFallah/csv-parser, used for parsing Zipcode CSV data

**References:**
- https://www.geeksforgeeks.org/binary-search-tree-data-structure/
- https://en.wikipedia.org/wiki/Scapegoat_tree
- https://en.wikipedia.org/wiki/Treap
- http://jeffe.cs.illinois.edu/teaching/algorithms/notes/10-treaps.pdf
- http://akira.ruc.dk/~keld/teaching/algoritmedesign_f08/Artikler/03/Galperin93.pdf

