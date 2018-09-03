/*
  Name: Patrick Rawlings
  Class at ECU:3300
  Assignment Due Date: 4/11/11
  Assignment Number: Program 4
  Professor: Dr. Ronnie Smith
  
  Description: The purpose of this program is to demonstrate the 
           
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

const int BUFFERSIZE = 512;

struct CityNode {
  char *name;
  char *state;
  bool isCapital;
  int pop;
  struct CityNode *next;

  CityNode() // default constructor
  {
    name = state = NULL;
    isCapital = false;
    pop = 0;
    next = NULL;
  }
};

typedef CityNode* PtrType;

#define DEBUG
bool debugON = true;   // global debugging flag



void deleteNode (PtrType& head, string cityInput)
{
	if(head!=NULL && head->next!=NULL) // Not finished.
	 {
			
			if (!(cityInput == head->name)) // Did not find match.
			deleteNode(head->next,cityInput);// Start recursion.

				else // Found match!  Now delete it.
				{
				cout<<"Debug: Found city name!"<<endl;
				PtrType tmpNode = head;
				
				tmpNode->next=head->next;

			 	if(head->next==NULL) tmpNode->next=NULL;

				delete []tmpNode->name; 
				delete []tmpNode->state;

				delete tmpNode;
				
				cout<<"The city was successfully deleted."<<endl<<endl;				
				}
	 }
	 else // Finished and did not find match.
	 {
	  cout<<"The city you entered is not in the list being examined."
	  <<" The city you were looking for was: "<<cityInput<<endl;
	 }
}



// Prints the link-list.
void displayList(PtrType head)
{
bool finished = false;

	while (!finished)
	{
		if (head->isCapital == true) // Is a capital.
		{
		cout<< head->name<<", "<< head->state <<" "<<" population "<< head->pop <<" (capital) "<< endl;
		head = head->next;
	 	}
		else if (head->isCapital == false) // Not a capital.
		{	
		cout<< head->name<<", "<< head->state <<" population "<< head->pop <<endl;
		head = head->next;
		}		

		if(head->next == NULL) finished = true;
	
	}
}

// Initializes list containing database and returns pointer to
// the start of the list.  Input stream is specified by input
// and will already be defined.

void displayMenu()
{
  cout<<"** U.S City Information Program **"<<endl;
  cout<<"(Enter number of choice and RETURN)"<<endl<<endl;
  cout<<"1) Delete a city."<<endl;
  cout<<"2) Give the capital of a specified state."<<endl;
  cout<<"3) List all cities from a specified state."<<endl;
  cout<<"4) List all the cities in the database."<<endl;
  cout<<"5) Quit the program"<<endl;
}

PtrType initialize(ifstream & input)
{
   char buf[BUFFERSIZE];
   char *bufptr = buf;

// Set first to point to the dummy node at the front of the list.
// Values set by default constructor includes NULL pointer.

   PtrType first; // Creates a pointer to a node.
	PtrType current; // Used for filling the list.

   CityNode* newNode = new CityNode; // Creates an empty node.
	first = newNode; // Makes first point to the empty node.

	current = first; // Both point at front of the list.

   while (input.getline(bufptr,BUFFERSIZE)) // read first line for city
   {
	  current->name = strdup(bufptr); 	
	  //cout<<"Debug: current->name "<<current->name<<endl;	

     input.getline(bufptr,BUFFERSIZE);  // read second line for state

	  current->state = strdup(bufptr); // Pulls data from buffer to state.
	  //cout<<"Debug: current->state "<<current->state<<endl;

     input.getline(bufptr,BUFFERSIZE); // read third line for capital

		  int capitalTest = atoi(bufptr);

		  if(capitalTest == 1 ) // Is a capital.
			{
			current->isCapital = true;
			}
			else                 // Not a capital.
			{
			current->isCapital = false;
			}
		
		//cout<<"Debug: current->isCapital "<<current->isCapital<<endl;
		
	   input.getline(bufptr,BUFFERSIZE); // read fourth line for population

     	current->pop = atoi(strdup(bufptr));
		//cout<<"Debug: current->pop "<<current->pop<<endl;
		
   	newNode = new CityNode;  // Insert new node into list 
		current->next = newNode; // Set a pointer to the newly created node.
		
		current = newNode; // Newly created node is now current.
	}
 

// Sample use of debug switch and debug code

#ifdef DEBUG
  if (debugON)
  {
	 cout<<endl; // Spacing for viewability.
    cout << "list after reading the input file\n";
    displayList(first);
	 cout<<endl; // Spacing for viewability.
  }
#endif
 
  // return pointer to start of list  
 	return first;
}
     
int main(int argc, char *argv[])
{
  ifstream city_input;
  int choice;
  string cityInput;

  PtrType head;
  char buffer[BUFFERSIZE];

  if(argc > 1) // open file and initialize database
  {
    (city_input.open(argv[1]));
    head = initialize(city_input);
  }
  else 
    head = NULL; // initialize to empty

  // specify code for menu display and processing of choice

  bool finished = false;
  while (!finished)
  {
    displayMenu(); // interactive menu display
	 cin>>choice;	
	 
	 cin.getline(buffer,BUFFERSIZE);
   // int choice = atoi(buffer);

	 switch (choice)
	 {
		case 1: // Delete a city.
		cout<<"Enter the city you wish to delete."<<endl;
		//cin>>cityInput;
		//deleteNode(head, cityInput);
		break;
		
		case 2: // Give a capital of a specified state.
		cout<<"Debug: You selected choice 2."<<endl<<endl;
		break;

		case 3:// List all cities from a specified state.
		cout<<"Debug: You selected choice 3."<<endl<<endl;
		break;

		case 4:// List all the cities in the database.
		cout<<"Debug: You selected choice 4."<<endl<<endl;
		break;

		case 5:// Quit the program.
		finished = true;
	
		case 6: // Debug output.
		displayList(head);
	 }

  }

  return 0;
}




