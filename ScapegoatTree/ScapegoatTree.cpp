//Author : Yahia Bakour
#include "ScapegoatTree.h"

/*
CONSTRUCTOR: Create an Empty Binary Search Tree
*/
SGT::SGT() {root = nullptr; ALPHA = 0.6;}

/*
CONSTRUCTOR: Create an Empty Binary Search Tree with an alpha
*/
SGT::SGT(double alpha) {root = nullptr; ALPHA = alpha;}

/*
CONSTRUCTOR: Create an Empty Binary Search Tree with one SGT_Node num and alpha
*/
SGT::SGT(int num, double alpha) {
  NumberofSGT_Nodes = 1;
  root = new SGT_Node;
  root->value = num;
  root->left = root->right = root->Parent = nullptr;
  ALPHA = alpha;
}

/*
CONSTRUCTOR: create a SGT by inserting ints from the vector into the SGT in order
*/
SGT::SGT(vector<int>& List, double alpha) {
  NumberofSGT_Nodes = 1;
  root = new SGT_Node;
  root->value = List[0];
  root->left = root->right = root->Parent = nullptr;
  ALPHA = alpha;
  for (int i = 1; i < List.size(); i++) insert(List[i]);
}
/*
Destructor: Destroy Tree Recursive
*/
SGT::~SGT(){
	DestroyTreeRecursive(root);
	root = nullptr;
}


void SGT::DestroyTreeRecursive(SGT_Node* Root){
	if(Root){
		DestroyTreeRecursive(Root->left);
		DestroyTreeRecursive(Root->right);
		delete Root;
	}
}


/* 
Function: Searches throughout SGT using Regular BST Search,Returns SGT_Node if found, returns nullptr otherwise
*/
SGT_Node* SGT::Search(SGT_Node* Root, int key) {
  if (root == nullptr)
    return root;
  else if ((Root->value > key && Root->left == nullptr) || (Root->value <= key && Root->right == nullptr))
    return Root;  // IF ABOUT TO FALL OFF TREE
  else if (Root->value == key)
    return Root;
  else if (key > Root->value)
    Search(Root->right, key);
  else if (key < Root->value)
    Search(Root->left, key);
}

/* 
Utility for insert:
- Search and alter depth
- logfunc 
- Insert into vector in preorder
- Build balanced
- Rebuild
*/
double Logfunc(double alpha, double x) {return (log(x) / log(1.0/alpha));}

SGT_Node* SGT::Search_and_alter_depth(SGT_Node* Root, int key, int &depth) {
  if (root == nullptr)
    return root;
  else if ((Root->value > key && Root->left == nullptr) || (Root->value < key && Root->right == nullptr)){ return Root;} 
  else if (Root->value == key) return Root;
  else if (key > Root->value){ depth++; Search_and_alter_depth(Root->right, key,depth);}
  else if (key < Root->value){ depth++; Search_and_alter_depth(Root->left, key,depth);}
}

void Insertintovector_inorder(SGT_Node* N, vector<SGT_Node*> &Vec ){
	if(N == nullptr) return; 
	Insertintovector_inorder(N->left, Vec);
	Vec.push_back(N);
	Insertintovector_inorder(N->right, Vec);
}

SGT_Node* SGT::Balance(vector<SGT_Node*> &vec, int i, int n){
		if (n == 0) return nullptr;
		int j = n / 2;
		vec[i + j]->left = Balance(vec, i, j);
		if (vec[i + j]->left != nullptr) vec[i + j]->left->Parent = vec[i + j];
		vec[i + j]->right = Balance(vec, i + j + 1, n - j - 1);
		if (vec[i + j]->right != nullptr) vec[i + j]->right->Parent = vec[i + j];
		return vec[i + j];
}
		
void SGT::rebuildTree(SGT_Node* N){
	SGT_Node* p = N->Parent;
	vector<SGT_Node*> vec;
	Insertintovector_inorder(N,vec);
	int ns = vec.size();
	 if (p == nullptr) {root = Balance(vec, 0, ns);root->Parent = nullptr;}
		else if (p->right == N){p->right = Balance(vec, 0, ns); p->right->Parent = p;}
		else {p->left = Balance(vec, 0, ns);p->left->Parent = p;}
}

/*
Insert num into SGT
*/
void SGT::insert(int num) {
  int depth = 0;
  NumberofSGT_Nodes++;
  SGT_Node* N = new SGT_Node;
  N->value = num;
  N->left = N->right = N->Parent = nullptr;
  
  if (root == nullptr) {
    root = N;
	} 
  else { 
    N->Parent = Search_and_alter_depth(root, num, depth);
    N->left = N->right = nullptr;
    N->value = num;
    if (num >= N->Parent->value)
      N->Parent->right = N;
    else if (num < N->Parent->value)
      N->Parent->left = N;
  
  int size_p,size_pRight,size_pLeft;
  if (depth > Logfunc(ALPHA,Size(root))){ // Check if height balanced
        // Find Scapegoat 
        SGT_Node *p = N->Parent; 
        while (Size(p->left) <= ALPHA*Size(p) && Size(p->right) <= ALPHA*Size(p)) 
            p = p->Parent;  
        // Rebuild tree rooted under scapegoat 

		if( p->Parent != nullptr )
        rebuildTree(p->Parent);
		else {
		rebuildTree(p);
		}
  }
	}
  MaxSGT_NodeCount = (MaxSGT_NodeCount < NumberofSGT_Nodes) ?  NumberofSGT_Nodes : MaxSGT_NodeCount;
}

/*
Insert Node into SGT
*/
void SGT::insert(SGT_Node* N) {
  int num = N->value;
  int depth = 0;
  NumberofSGT_Nodes++;
  
  if (root == nullptr) {
    root = N;
	} 
  else { 
    N->Parent = Search_and_alter_depth(root, num, depth);
    N->left = N->right = nullptr;
    N->value = num;
    if (num >= N->Parent->value)
      N->Parent->right = N;
    else if (num < N->Parent->value)
      N->Parent->left = N;
  if (depth > Logfunc(ALPHA,NumberofSGT_Nodes)){ // Check if height balanced
        // Find Scapegoat 
        SGT_Node *p = N->Parent; 
		
        while (Size(p->left) <= ALPHA*Size(p) && Size(p->right) <= ALPHA*Size(p)) 
            p = p->Parent;  
        // Rebuild tree rooted under scapegoat 

		if( p->Parent != nullptr )
        rebuildTree(p->Parent);
		else {
		rebuildTree(p);
		}
  }
	}
  MaxSGT_NodeCount = (MaxSGT_NodeCount < NumberofSGT_Nodes) ?  NumberofSGT_Nodes : MaxSGT_NodeCount;
}

/*
Function: Replicate the SGT IF Given the root of the new tree and root of the original, returns the root of the newly copied tree/subtree
*/
SGT_Node* Replicate_Sub_Tree(SGT_Node* Rootofnewtree, SGT_Node* Rootoforiginal) {  // FUNCTION TO COPY A TREE
  SGT_Node* NEWSGT_Node = new SGT_Node;
  if (Rootoforiginal != nullptr) {
    NEWSGT_Node->value = Rootoforiginal->value;
    NEWSGT_Node->left = Replicate_Sub_Tree(NEWSGT_Node->left, Rootoforiginal->left);
    NEWSGT_Node->right = Replicate_Sub_Tree(NEWSGT_Node->right, Rootoforiginal->right);
  } else {
    NEWSGT_Node = nullptr;
  }
    return NEWSGT_Node;
}

/*
Function/Utility: Find size of a SGT_Node (Size = number of Nodes under it (including the node itself))
*/
int SGT::Size(SGT_Node* R){
	if( R == nullptr) return 0;
	return 1 + Size(R->left) + Size(R->right);
}

/*
Function: Counts the total number of SGT_Nodes in the SGT
*/
void Count(SGT_Node* Root, int &numberofSGT_Nodes) {
  if (Root == nullptr) return;
  numberofSGT_Nodes++;
  Count(Root->left,numberofSGT_Nodes);
  Count(Root->right,numberofSGT_Nodes);
}

int SGT::Count_SGT_Nodes() {
  int numberofSGT_Nodes = 0;
  Count(root,numberofSGT_Nodes);
  return numberofSGT_Nodes;
}

/*
Function: Returns the Min Value in the SGT
*/
int SGT::Find_Min() {
  SGT_Node* p = new SGT_Node;
  p = root;
  if (p->left == nullptr) return p->value;
  while (p->left != nullptr) p = p->left;
  return p->value;
}

/*
Function: Returns the Max Value in the SGT
*/
int SGT::Find_Max() {
  SGT_Node* p = new SGT_Node;
  p = root;
  if (p->right == nullptr) return p->value;
  while (p->right != nullptr) p = p->right;
  return p->value;
}

/*
Function: Returns the successor of the given SGT_Node in the SGT
*/

SGT_Node* SGT::Successor(SGT_Node* sucessee) {
  if (sucessee->right != nullptr) {
    SGT_Node* p = new SGT_Node;
    p = sucessee->right;
    if (p->left == nullptr) return p;
    while (p->left != nullptr) {
      p = p->left;
    }
    return p;
  } else {
    SGT_Node* p = new SGT_Node;
    p = sucessee;
    while (p->value > p->Parent->value) {
      p = p->Parent;
    }
    return p->Parent;
  }
}

/*
Function: Returns the predecessor of the given SGT_Node in the SGT
*/

SGT_Node* SGT::Predecessor(SGT_Node* predecessee) {
  if (predecessee->left != nullptr) {
    SGT_Node* p = new SGT_Node;
    p = predecessee->left;
    if (p->right == nullptr) return p;
    while (p->right != nullptr) {
      p = p->right;
    }
    return p;
  } else {
    SGT_Node* p = new SGT_Node;
    p = predecessee;
    while (p->value < p->Parent->value) {
      p = p->Parent;
    }
    return p->Parent;
  }
}

/*
Function: Deletes SGT_Node with the given int key in the SGT, Rebalance if needed
*/
void SGT::Delete(int key) {
  NumberofSGT_Nodes--;
  SGT_Node* temp = Search(root, key);
  if (temp == nullptr || temp->value != key) {
	cout << "\n Could not be deleted because, key doesn't exist in the tree" << endl;
	NumberofSGT_Nodes++;
    return;
  }
  if(temp == root && temp->right == nullptr && temp->left == nullptr){
	  temp = nullptr;
  }
  // case 1: it is a leaf
  if (temp->right == nullptr && temp->left == nullptr) {
    if (temp->value > temp->Parent->value) temp->Parent->right = nullptr;
    if (temp->value < temp->Parent->value) temp->Parent->left = nullptr;
	return;
  }
  // case 2: one child
  if (temp->left == nullptr && temp->right != nullptr) {
	if (temp == root){
		root = temp->right;
		root->Parent = nullptr;
		temp->right = nullptr;
	}
	else{
	if(temp->value >= temp->Parent->value) temp->Parent->right = temp->right;
	if(temp->value < temp->Parent->value) temp->Parent->left = temp->right;
    temp->right->Parent = temp->Parent;
	}
	return;
  }

  if (temp->right == nullptr && temp->left != nullptr) {
	if (temp == root){
		root = temp->left;
		root->Parent = nullptr;
		temp->left = nullptr;
	}
	else{
	if(temp->value >= temp->Parent->value) temp->Parent->right = temp->left;
	if(temp->value < temp->Parent->value) temp->Parent->left = temp->left;
    temp->left->Parent = temp->Parent;
	}
	return;
  }
  // case 3: 2 children
  if (temp->right != nullptr && temp->left != nullptr) {
    SGT_Node* success = Successor(temp);
    int k = key;
    temp->value = success->value;
    success->value = k;
	NumberofSGT_Nodes++;
	Delete(success);
	}

  //Check if need to rebuild tree
  if (NumberofSGT_Nodes <= ALPHA * MaxSGT_NodeCount){
	  rebuildTree(root);
	  MaxSGT_NodeCount = NumberofSGT_Nodes;
  }
}

/*
Function: Deletes the given SGT_Node in the SGT, Rebalance if needed
*/
void SGT::Delete(SGT_Node* N) {
  NumberofSGT_Nodes--;
  if (N == nullptr){
	cout << "\n Could not be deleted because Delete was given a nullptr" << endl;
	NumberofSGT_Nodes++;
    return;
  }
  // case 1: it is a leaf
  if (N->right == nullptr && N->left == nullptr) {
	if(N->Parent->left && N->Parent->left == N) N->Parent->left = nullptr;
	if(N->Parent->right && N->Parent->right == N) N->Parent->right = nullptr;
	free(N);
	return;
  }
  // case 2: one child
  if (N->left == nullptr && N->right != nullptr) {
	if (N == root){
		root = N->right;
		root->Parent = nullptr;
		N->right = nullptr;
	}
	else{
	if(N->Parent->left && N->Parent->left == N) N->Parent->left = N->right;
	if(N->Parent->right && N->Parent->right == N) N->Parent->right = N->right;
    N->right->Parent = N->Parent;
	}
	free(N);
	return;
  }

  if (N->right == nullptr && N->left != nullptr) {
	if (N == root){
		root = N->left;
		root->Parent = nullptr;
		N->left = nullptr;
	}
	else{
	if(N->Parent->left && N->Parent->left == N) N->Parent->left = N->left;
	if(N->Parent->right && N->Parent->right == N) N->Parent->right = N->left;
    N->left->Parent = N->Parent;
	}
	free(N);
	return;
  }
  // case 3: 2 children
  if (N->right != nullptr && N->left != nullptr) {
    SGT_Node* success = Successor(N);
    int k = N->value;
    N->value = success->value;
    success->value = k;
	Delete(success);
	}

  //Check if need to rebuild tree
  if (NumberofSGT_Nodes <= ALPHA * MaxSGT_NodeCount){
	  rebuildTree(root);
	  MaxSGT_NodeCount = NumberofSGT_Nodes;
  }
}


// Displays SGT horizantally, Not my Code
void SGT::disp() { display(root, 5); }
void SGT::display(SGT_Node* p, int indent) {
  if (p != NULL) {
    if (p->right) {
      display(p->right, indent + 4);
    }
    if (indent) {
      cout << setw(indent) << ' ';
    }
    if (p->right) cout << " /\n" << setw(indent) << ' ';
		cout << p->value << "\n ";
    if (p->left) {
		cout << setw(indent) << ' ' << " \\\n";
		display(p->left, indent + 4);
    }
  }
}
