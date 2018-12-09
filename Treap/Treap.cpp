//Author: Yahia Bakour

#include "Treap.h"

/*
CONSTRUCTOR: Create an Empty Treap
*/
Treap::Treap() {root = nullptr; }

/*
CONSTRUCTOR: Create a One Treap_Node Treap with the value of the Treap_Node as num
*/
Treap::Treap(int num) {
  root = new Treap_Node;
  root->value = num;
  root->left = root->right =  root->Parent = nullptr;
}

/*
CONSTRUCTOR: Create a Treap by inserting integers from the vector into the Treap in order
*/
Treap::Treap(vector<int>& List) {
  root = new Treap_Node;
  root->value = List[0];
  root->left = root->right = nullptr;
  for (int i = 1; i < List.size(); i++) insert(List[i]);
}

/*
DESTRUCTOR: Destroys the entire tree
*/
Treap::~Treap(){DestroyTreeRecursive(root);root = nullptr;}


void Treap::DestroyTreeRecursive(Treap_Node* Root){
	if(Root){
		DestroyTreeRecursive(Root->left);
		DestroyTreeRecursive(Root->right);
		delete Root;
	}
}


/*
Used for quick membership testing
*/
bool Treap::Membership_testing(int key){
	if(Search(root,key) != nullptr && Search(root,key)->value == key) return true;
	else return false;
}

/*
Searches throughout Treap using Regular BST Search, Returns where Treap_Node should be placed or where Treap_Node is located
*/
Treap_Node* Treap::Search(Treap_Node* Root, int key) {
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
Utility Function: Rotate Left on this Treap_Node
*/
void Treap::leftrotate(Treap_Node* P){
	if(P->right == nullptr) return;
	Treap_Node* Q = P->right;
	if(root -> value == P->value){
		root = Q;
		if(Q->left != nullptr)Q->left->Parent = P;
		P->right = Q->left;
		Q->left = P;
		P->Parent = Q;
		root->Parent = nullptr;
	} else {
		if(P->value >= P->Parent->value) P->Parent->right = Q;
		if(P->value < P->Parent->value) P->Parent->left = Q;
		Q->Parent = P->Parent;
		if(Q->left != nullptr)Q->left->Parent = P;
		P->right = Q->left;
		Q->left = P;
		P->Parent = Q;
	}
}

/*
Utility Function: Rotate Right on this Treap_Node
*/
void Treap::rightrotate(Treap_Node* Q){
	if(Q->left == nullptr) return;
	Treap_Node* P = Q->left;
	if(root-> value == Q ->value){
		root = P;
		if(P->right != nullptr)P->right->Parent = Q;
		Q->left = P->right;
		P->right = Q;
		Q->Parent = P;
		root->Parent = nullptr;
	} else {
		if(Q->value >= Q->Parent->value) Q->Parent->right = P;
		if(Q->value < Q->Parent->value)  Q->Parent->left = P;
		P->Parent = Q->Parent;
		if(P->right != nullptr)P->right->Parent = Q;
		Q->left = P->right;
		P->right = Q;
		Q->Parent = P;
	}
}

/*
Insert num as a new value to the Treap, Rotate if necessary to preserve max heap property
*/
void Treap::insert(int num) {
  Treap_Node* N = new Treap_Node(num);
  if (root == nullptr) {
    root = N;
  } else {
    N->Parent = Search(root, num);
    if (num >= N->Parent->value)
      N->Parent->right = N;
    else if (num < N->Parent->value)
      N->Parent->left = N;
  }
  while(N != root && N->priority >= N->Parent->priority){
	if (N == N->Parent->right){
		leftrotate(N->Parent);
		}
	else{
		rightrotate(N->Parent);
	}
  }
}


/*
Insert Node to the Treap, Rotate if necessary to preserve max heap property
*/
void Treap::insert(Treap_Node* Treap_Node) {
	int num = Treap_Node->value;
  if (root == nullptr) {
    Treap(num);
  } else {
    Treap_Node->Parent = Search(root, num);
    if (num >= Treap_Node->Parent->value)
      Treap_Node->Parent->right = Treap_Node;
    else if (num < Treap_Node->Parent->value)
      Treap_Node->Parent->left = Treap_Node;
  }
  while(Treap_Node != root && Treap_Node->priority >= Treap_Node->Parent->priority){
	if (Treap_Node == Treap_Node->Parent->right){
		leftrotate(Treap_Node->Parent);
		}
	else{
		rightrotate(Treap_Node->Parent);
	}
  }
}

/*
Replicate the Treap IF Given the root of the new tree and root of the original, returns the root of the newly copied tree/subtree
*/
Treap_Node* Replicate_Sub_Tree(Treap_Node* Rootofnewtree,
                         Treap_Node* Rootoforiginal) {  // FUNCTION TO COPY A TREE
  Treap_Node* NEWTreap_Node = new Treap_Node;
  if (Rootoforiginal != nullptr) {
    NEWTreap_Node->value = Rootoforiginal->value;
    NEWTreap_Node->left = Replicate_Sub_Tree(NEWTreap_Node->left, Rootoforiginal->left);
    NEWTreap_Node->right = Replicate_Sub_Tree(NEWTreap_Node->right, Rootoforiginal->right);
    return NEWTreap_Node;
  } else {
    NEWTreap_Node = nullptr;
    return NEWTreap_Node;
  }
}

/*
Counts the number of Nodes in the Treap
*/
void Treap::Count(Treap_Node* Root) {
  if (Root == nullptr) return;
  numberofTreap_Nodes++;
  Count(Root->left);
  Count(Root->right);
}

int Treap::Count_Treap_Nodes() {
  numberofTreap_Nodes = 0;
  Count(root);
  return numberofTreap_Nodes;
}

/*
Returns the Min Value in the Treap
*/
int Treap::Find_Min() {
  Treap_Node* p = new Treap_Node;
  p = root;
  if (p->left == nullptr) return p->value;
  while (p->left != nullptr) {
    p = p->left;
  }
  return p->value;
}

/*
Returns the Max Value in the Treap
*/
int Treap::Find_Max() {
  Treap_Node* p = new Treap_Node;
  p = root;
  if (p->right == nullptr) return p->value;
  while (p->right != nullptr) {
    p = p->right;
  }
  return p->value;
}

/*
Returns the Predecessor of the given Treap_Node in the Treap
*/
Treap_Node* Treap::Predecessor(Treap_Node* predecessee) {
  if (predecessee->left != nullptr) {
    Treap_Node* p = new Treap_Node;
    p = predecessee->left;
    if (p->right == nullptr) return p;
    while (p->right != nullptr) {
      p = p->right;
    }
    return p;
  } else {
    Treap_Node* p = new Treap_Node;
    p = predecessee;
    while (p->value < p->Parent->value) {
      p = p->Parent;
    }
    return p->Parent;
  }
}

/*
Returns the successor of the given Treap_Node in the Treap
*/
Treap_Node* Treap::Successor(Treap_Node* sucessee) {
  if (sucessee->right != nullptr) {
    Treap_Node* p = new Treap_Node;
    p = sucessee->right;
    if (p->left == nullptr) return p;
    while (p->left != nullptr) {
      p = p->left;
    }
    return p;
  } else {
    Treap_Node* p = new Treap_Node();
    p = sucessee;
    while (p->value > p->Parent->value) {
      p = p->Parent;
    }
    return p->Parent;
  }
}

/*
Deletes the Treap_Node with the Given Key in the Treap
*/
void Treap::Delete(int key) {
  if(root == nullptr){cout <<"Trying to delete in an empty tree is a grave offense, Repent at once" << endl; return;}
  
  Treap_Node* temp = Search(root, key);
  if (temp->value != key) {cout <<"KEY "<<key <<" could not be deleted because it isn't in the tree" << endl;return;}
  
  if(temp == root && temp->right == nullptr && temp->left == nullptr){
	  root = nullptr;
	  return;
  }
  // case 1: 2 children --> Rotate Treap_Node down to leaf or Treap_Node with one child
  while(temp->right != nullptr && temp->left != nullptr){
	  if(temp->right->priority >= temp->priority){
		  leftrotate(temp);
	  } else{
		  rightrotate(temp);
	  }
  }
  // case 2: it is a leaf
  if (temp->right == nullptr && temp->left == nullptr) {
    if (temp->value >= temp->Parent->value) {
		temp->Parent->right = NULL;
		return;
	}
    if (temp->value < temp->Parent->value){
		temp->Parent->left = NULL;
		return;
	}
  }
  // case 3: one child
  if (temp->left == nullptr && temp->right != nullptr) {
	if (temp == root){
		root = temp->right;
		root->Parent = nullptr;
		temp->right = nullptr;
		return;
	}
	else{
	if(temp->Parent->left && temp->Parent->left == temp) temp->Parent->left = temp->right;
	if(temp->Parent->right && temp->Parent->right == temp) temp->Parent->right = temp->right;
    temp->right->Parent = temp->Parent;
	}
	free(temp);
	return;
  }

  if (temp->right == nullptr && temp->left != nullptr) {
	if (temp == root){
		root = temp->left;
		root->Parent = nullptr;
		temp->left = nullptr;
	}
	else{
	if(temp->Parent->left && temp->Parent->left == temp) temp->Parent->left = temp->left;
	if(temp->Parent->right && temp->Parent->right == temp) temp->Parent->right = temp->left;
    temp->left->Parent = temp->Parent;
	}
	free(temp);
	return;
  }

  return;
}

/*
Displays Treap horizantally, Not my Code
*/
void Treap::disp() { display(root, 10); }
void Treap::display(Treap_Node* p, int indent) {
  if (p != NULL) {
    if (p->right) {
      display(p->right, indent + 4);
    }
    if (indent) {
      std::cout << setw(indent) << ' ';
    }
    if (p->right) std::cout << " /\n" << setw(indent) << ' ';
	std::cout << p->value;
	/*
	if(p->Parent) cout << " -- Parent : " << p->Parent->value;
	if(p->right) cout << " -- Right : " << p->right->value;
	if(p->left) cout << " -- Left : " << p->left->value;
	*/
	cout <<endl;

    if (p->left) {
      std::cout << setw(indent) << ' ' << " \\\n";
      display(p->left, indent + 4);
    }
  }
}
