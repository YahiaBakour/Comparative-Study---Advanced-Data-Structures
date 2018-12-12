//Author: Yahia Bakour

#ifndef TREAP_h
#define TREAP_h
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <climits>
using namespace std;

struct Treap_Node {
	int value, priority;
	string zipcode_type, city, state, country;
	Treap_Node* left;
	Treap_Node* right;
	Treap_Node* Parent;

	Treap_Node(int key = 0, string zipcode_type = "", string city = "", string state = "",string country = ""){
		priority = rand() % 100000;
		value = key;
		left = right = Parent = nullptr;
		zipcode_type = zipcode_type;
		city = city;
		state = state;
		country = country;
	}
};

class Treap {
	public:
		// Constructor
		Treap();

		// creates a one-Treap_Node Treap with the given key
		Treap(int number);
		
		// constructs a Treap by inserting integers from the vector into the tree
		Treap(vector<int>& List);

		// Destructor
		~Treap();

		// Search for given value starting at root and return where Treap_Node should be placed, even if its a duplicate
		Treap_Node* Search(Treap_Node* Root, int key);

		// Duplicate a tree starting at a certain Treap_Node and return the root of the new Treap
		Treap_Node* Replicate_Sub_Tree(Treap_Node* Rootofnewtree, Treap_Node* Rootoforiginal);

		// Returns successor of a Treap_Node in Treap
		Treap_Node* Successor(Treap_Node* sucessee);

		// Returns Predecessor of a Treap_Node in Treap
		Treap_Node* Predecessor(Treap_Node* predecessee);

		// Returns number of Treap_Nodes in the entire tree
		int Count_Treap_Nodes();

		// Finds Treap_Node holding minimum value in the Treap
		int Find_Min();

		// Finds Treap_Node Holding maximum value in the Treap
		int Find_Max();
		
		// Membership Testing, returns true if Treap_Node with key exists, false otherwise
		bool Membership_testing(int key);

		// Insert Number as new key to the entire Treap
		void insert(int num);

		// Insert Treap_Node  to the entire Treap
		void insert(Treap_Node* num);

		// Deletes Treap_Node From Treap
		void Delete(int key);

		// Pretty Print the Treap, disp() and display(Treap_Node* P, int indent) logic and code are not mine
		void disp();
		
		// Pointer to the root of the Treap
		Treap_Node* root;
		
	private:
		int numberofTreap_Nodes;						//Just keeps track of number of treap nodes, used by count() function
		void DestroyTreeRecursive(Treap_Node* Root);	//Utility Function used by destructor
		void  rightrotate(Treap_Node* p);				//Utility Function used for right rotations (ZIG)
		void  leftrotate(Treap_Node* q);				//Utility Function used for left rotations (ZAG)
		void Count(Treap_Node* Root);					//Utiilty Function used by Count() Function
		void display(Treap_Node* P, int indent);		//Utility Function used by disp() Function

};

#endif
