//Author: Yahia Bakour
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>   
#include <Windows.h>   
#include "parser.h"
#include "../Treap/Treap.h"
#include "../Treap/Treap.cpp"
#include "../ScapegoatTree/ScapegoatTree.h"
#include "../ScapegoatTree/ScapegoatTree.cpp"

using namespace std;

//Zipcode,Zipcode Type, City, State, Country
vector<vector<string>> CSV_ZipCode_Data;
ofstream results;

int insertsize;
int searchsize;
int deletesize;

/*
Function to print Scape Goat Tree data with a particular alpha
*/
void scapegoat_data(double alpha){
	results.open("Results.txt",ios_base::app); //Append to results.txt instead of rewriting
	LARGE_INTEGER frequency;        			// ticks per second
	LARGE_INTEGER t1, t2;           			// ticks
	double elapsedTime;							//Used for time calculations
	int counter;								//Used for printing to results.txt
	
	SGT ScapegoatTree(stoi(CSV_ZipCode_Data[1][0]),alpha);
	ScapegoatTree.root->zipcode_type = CSV_ZipCode_Data[1][1];
	ScapegoatTree.root->city = CSV_ZipCode_Data[1][2];
	ScapegoatTree.root->state = CSV_ZipCode_Data[1][3];
	ScapegoatTree.root->country = CSV_ZipCode_Data[1][4];


	results << " \n \nScapegoat Tree Results with alpha : " << alpha<< endl;
	counter = 0;
						// ################### Insert Time #####################
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
	  for(int i = 2; i != insertsize ; i++){
			counter ++;
			int current_zip = stoi(CSV_ZipCode_Data[i][0]);
			SGT_Node* Payload = new SGT_Node(current_zip,CSV_ZipCode_Data[i][1],CSV_ZipCode_Data[i][2],CSV_ZipCode_Data[i][3],CSV_ZipCode_Data[i][4] );
			ScapegoatTree.insert(Payload);
	  }
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	results <<"Time Taken To Insert " << counter << " Zipcodes is : "<< elapsedTime << endl;


						// ################### Search Time #####################
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
		for(int i = 2 ; i != searchsize; i++){ SGT_Node* Found = ScapegoatTree.Search(ScapegoatTree.root,stoi(CSV_ZipCode_Data[i][0]));}
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	results <<"Time Taken To search for all zipcodes is: "<< elapsedTime << endl;


						// ################### Delete Time #####################
	counter = 0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
		for(int i = 2; i != deletesize ; i++){ScapegoatTree.Delete(stoi(CSV_ZipCode_Data[i][0])); counter ++;}
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	results <<"Time Taken To Delete " << counter << " zipcodes is: "<< elapsedTime << endl;
	
	results.close();
}


/*
Function to print Treap data
*/
Treap_data(){
	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;
	int counter;
	
	results << "Treap Results " << endl;

	Treap TREAP(stoi(CSV_ZipCode_Data[1][0]));
	TREAP.root->zipcode_type = CSV_ZipCode_Data[0][1];
	TREAP.root->city = CSV_ZipCode_Data[1][2];
	TREAP.root->state = CSV_ZipCode_Data[1][3];
	TREAP.root->country = CSV_ZipCode_Data[1][4];

 
				// ################### Insert Time #####################
	counter = 0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
	  for(int i = 2; i != insertsize; i++){
			int current_zip = stoi(CSV_ZipCode_Data[i][0]);
			Treap_Node* Payload = new Treap_Node(current_zip,CSV_ZipCode_Data[i][1],CSV_ZipCode_Data[i][2],CSV_ZipCode_Data[i][3],CSV_ZipCode_Data[i][4]);
			TREAP.insert(Payload);
			counter ++;
	  }
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	results <<"Time Taken To Insert " << counter << " Zipcodes is : "<< elapsedTime << endl;


				// ################### Search Time #####################
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
		for(int i = 2 ; i != searchsize ; i++) Treap_Node* Found = TREAP.Search(TREAP.root,stoi(CSV_ZipCode_Data[i][0]));
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	results <<"Time Taken To search for all zipcodes is: "<< elapsedTime << endl;


				// ################### Delete Time #####################
	counter = 0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
		for(int i = 2; i != deletesize ; i++){ TREAP.Delete(stoi(CSV_ZipCode_Data[i][0])); counter ++; }
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	
	results <<"Time Taken To Delete " << counter << " zipcodes is: "<< elapsedTime << endl;
	
}



 
int main(int argc, char *argv[])
{
	srand(time(NULL));				//Used to garantuee random Treap structure
	
	if (argc == 1){ cout <<"Invalid Execution, Need CSV file as command line arguement" << endl; return 0;} //Null Guard
	clock_t start, end;
	long double time;
	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;				// elapsed time from windows.h
	string filename = argv[1];
	ifstream f(filename);
	aria::csv::CsvParser parser(f);
	double newalpha = 0.55;			//Used for first SGT iteration

	
	// Input Data Into Vector From CSV File
	for (auto& row : parser) {
		vector<string> Zipcode_row;
		int i = 0;
		for (auto& field : row) {
			Zipcode_row.push_back(field);
		}
		Zipcode_row.push_back("US");
		CSV_ZipCode_Data.push_back(Zipcode_row);
	}
	
	//Open file for writing
	results.open("Results.txt");
	results << "All times are in milliseconds \n" << endl;

	insertsize = CSV_ZipCode_Data.size();			//Parameter for insertion sample size
	searchsize = CSV_ZipCode_Data.size();			//Parameter for search sample size
	deletesize = CSV_ZipCode_Data.size();			//Parameter for deletion sample size
	
	
	Treap_data();									//Create a Treap and run all tests on it, export results to file
	
	while(newalpha < 1){scapegoat_data(newalpha); newalpha = newalpha + 0.05;} //Create Scapegoat Trees of varying size and run all tests on it
	
	results.close();
    return 0;
}
