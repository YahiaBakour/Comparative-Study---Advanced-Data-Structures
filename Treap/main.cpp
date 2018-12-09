//Author: Yahia Bakour
#include "Treap.h"
#include <iostream>
#include<bits/stdc++.h> 
#include <fstream>
#include <string>

using namespace std;

// ADDS FILENUMBERS TO A VECTOR
vector<int> addtextfiletovector(string filename) {
  vector<int> V;
  string x;
  ifstream input;
  input.open(filename);
  while (getline(input, x)) {
	 if(x.length()){
    int i = stoi(x);
    V.push_back(i);
	 }
  }
  input.close();
  cout<<"Done importing file"<<endl;
  return V;
}
int main(int argc, char *argv[]) {
  srand (time(NULL));
	string filename;
	int answer;
	if (argc == 1){
		cout <<"INVALID INPUT, Need text file with keys you want to add in order as command line arguement" << endl;
		return 0;
	}
	filename = argv[1];
	vector<int> V1 = addtextfiletovector(filename);
	Treap_Node* N;
	string cont;
	Treap T2(V1);
 do
    {
        cout<<"\nYahia's Treap (Randomized Binary Search Tree)\n";
        cout<<"1. Insert a key "<<endl;
        cout<<"2. Delete a key "<<endl;
        cout<<"3. Search for a key "<<endl;
        cout<<"4. Find Minimum"<<endl;
        cout<<"5. Find Maximum"<<endl;
        cout<<"6. Successor of a Node"<<endl;
        cout<<"7. Predecessor of a Node"<<endl;
		cout <<"8. Display Treap" << endl;
		cout <<"9. Reset Tree" << endl;
		
        int choice;
        cout<<"Enter your Choice: ";
        cin>>choice;
		cout << endl;
		while(!cin){
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
			cout<<"Not a valid Option,Enter a valid Choice: ";
			cin>>choice;
			cout << endl;
		}
		
        switch (choice)
        {
			
			case 1:
				cout<<"Enter integer to insert: ";
				cin>>answer;
				T2.insert(answer);
				break;
			case 2:
				cout<<"Enter integer to delete: ";
				cin>>answer;
				T2.Delete(answer);
				break;
			case 3:
				cout <<"Enter Key to search for: ";
				cin>>answer;
				if(T2.Membership_testing(answer)){
					cout <<" KEY " << answer <<" HAS BEEN FOUND " << endl;
				}
				else{
					cout <<" KEY " << answer <<"  WASN'T FOUND " << endl;
				}
				break;
			case 4:
				cout <<"Minimum Key in the Treap is : "<< T2.Find_Min() << "\n" << endl;
				break;
			case 5:
				cout <<"Maximum Key in the Treap is : "<< T2.Find_Max() << "\n" << endl;
				break;
			case 6:
				cout <<"Enter Key to which you want the successor of " << endl;
				cin >> answer;
				N =T2.Search(T2.root,answer);
				if(N == nullptr){
					cout <<"Logic Error: The key you entered doesn't exist" << endl;
					break;
				} 
				if(N->value != answer){
					cout << "Node with key " << answer << " isn't in the tree"<<endl;
					break;
				} else{
					if(answer == T2.Find_Max()){
						cout << "Logic Error: Cannot Find Successor of maximum element in tree" << endl;
					}
					else{
					cout <<"Successor Of " << answer <<" is : "<< T2.Successor(N)->value << "\n" << endl;
				}
				}				
				break;
				
			case 7:
				cout <<"Enter Key to which you want the Predecessor of " << endl;
				cin >> answer;
				N =T2.Search(T2.root,answer);
				if(N == nullptr){
					cout <<"Logic Error: The key you entered doesn't exist" << endl;
					break;
				} 
				if(N->value != answer){
					cout << "Node with key " << answer << " isn't in the tree"<<endl;
					break;
				} else {
				if(answer == T2.Find_Min()){
					cout << "Logic Error: Cannot Find Predecessor of Minimum Element in Tree" << endl;
				}
				else{
				cout <<"Predecessor Of " << answer <<" is : "<< T2.Predecessor(N)->value << "\n" << endl;
				}
				}
				break;
			case 8:
				cout<<"\nThe Tree here is displayed horizantally (root is leftmost Treap_Node) \n" << endl;
				T2.disp();
				break;
			case 9:
				cout<<"\n Tree is being blown to bits \n"<<endl;
				T2.~Treap();
				break;

		}
		cout << "\n " << endl;
		cout << "Do you want to carry on exploring the wonderful Treap ? (Yes or No)"<< endl;
		cin >> cont;
	} while(cont== "Yes" ||cont== "yes" ||cont== "Y" ||cont== "y"  );
  return 0;
}