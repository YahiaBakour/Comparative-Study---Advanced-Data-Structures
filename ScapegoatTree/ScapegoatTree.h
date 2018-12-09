#ifndef ScapegoatTree_h
#define ScapegoatTree_h
#include<bits/stdc++.h> 
#include <vector>
#include <string>

using namespace std;

struct SGT_Node {
	int value;
	string zipcode_type, city, state ,country;
	SGT_Node* left;
	SGT_Node* right;
	SGT_Node* Parent;

	SGT_Node(int key){
		value = key;
		left = right = Parent = nullptr;
		zipcode_type = city = state = country = "" ;
	};
	SGT_Node(){
		value = 0;
		left = right = Parent = nullptr;
		zipcode_type = city = state = country = "" ;
	};
};

class SGT {
	public:
		// Constructor
			SGT();

		// Constructor with alpha
			SGT(double alpha);

		// creates a one-SGT_Node SGT with the given key
			SGT(int number,double alpha);
			
		// Destructor
			~SGT();

		// constructs a SGT by inserting integers from the vector into the tree
			SGT(vector<int>& List, double alpha);

		// Search for given value starting at root and return SGT_Node or null
			SGT_Node* Search(SGT_Node* Root, int key);

		// Duplicate a tree starting at a certain SGT_Node and return the root of the new SGT
			SGT_Node* Replicate_Sub_Tree(SGT_Node* Rootofnewtree, SGT_Node* Rootoforiginal);

		//Gives size of tree given root
			int Size(SGT_Node* N);

		// Returns number of SGT_Nodes in the entire tree
			int Count_SGT_Nodes();

		//Used to rebuild the tree at a certain SGT_Node
			void rebuildTree(SGT_Node* N);

		// Insert Number as new key to the entire SGT
			void insert(int num);
			void insert(SGT_Node* num);

		// Deletes SGT_Node From SGT given key
			void Delete(int key);

		//Deletes SGT_Node From SGT given SGT_Node
			void Delete(SGT_Node* N);

		// Returns successor of a SGT_Node in BST
			SGT_Node* Successor(SGT_Node* sucessee);

		// Returns Predecessor of a SGT_Node in BST
			SGT_Node* Predecessor(SGT_Node* predecessee);

		// Finds SGT_Node holding minimum value in the BST
			int Find_Min();

		// Finds SGT_Node Holding maximum value in the BST
			int Find_Max();

		// Pretty Print the BST, disp() and display(SGT_Node* P, int indent) logic and code are not mine
			void disp();
		
		//Used to keep track of root in SGT Structure
			SGT_Node* root;	

	private:
		void DestroyTreeRecursive(SGT_Node* Root);
		void display(SGT_Node* P, int indent); 								// Used in Display function 
		SGT_Node* Balance(vector<SGT_Node*> &vec, int i, int n); 			//Used for rebuilding the SGT 
		SGT_Node* Search_and_alter_depth(SGT_Node* Root, int key, int &depth);  //Used in insert function to detect if we need to rebalance
		int MaxSGT_NodeCount = 0;											// MaxSGT_NodeCount used for SGT Delete Function	
		int NumberofSGT_Nodes = 0;											// Number of SGT_Nodes in the Data structure at any time
		double ALPHA;													// ALPHA used in the definition of a Scapegoat Tree
		
};
#endif
