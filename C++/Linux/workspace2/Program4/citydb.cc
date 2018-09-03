/*
  Name: Patrick Rawlings
  Class at ECU:3300
  Assignment Due Date: 4/12/11
  Assignment Number: Program 4
  Professor: Dr. Ronnie Smith
  
  Description: The purpose of the program is to allow the user to edit/delete
  information in a database from a preset list of choices.  The program reads
  a list of data from a text file and stores it into the buffer which then is 
  organized into link list.  Once the data is in the link-list the user can
  alter and display the data.  To achieve this, a function is set to perform
  each option.
  1) "delete a city", 2) "give the capital", 3) "list cities of a state",
  4) "list all cities in the database" and 5) "quit the program."        
*/


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

const int BUFFERSIZE = 512; // Global variable.

struct CityNode {
  char *name;    // Holds name of city.
  char *state;   // Holds State.
  bool isCapital;// Reports if city is captial of state.
  int pop;       // Holds the population of a city.
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

//#define DEBUG
bool debugON = false;// global debugging flag

// Prints all the data of one node.  This is necessary to print each node in 
// sucession.
void displayNode(PtrType& head) 
{	  
	if(head->next!=NULL){ // checks for empty list.
	 if (head->isCapital==true){ // Prints capital
		cout<<head->name<<", "<<head->state<<" population "
		  <<head->pop<<" (capital)"<<endl;}
	else {cout<<head->name<<", "<<head->state<<" population "<<head->pop<<endl;} 
	}
}

// Function for implementing option 4, list all cities on the list.
void displayList(PtrType& prev)
{
	bool finished=false;
	cout<<endl;
	PtrType head= prev->next;
			
	while (!finished) // Displays the list until NULL is reached.
	{	
	displayNode(head);
	head = head->next; 

		if (head==NULL||head->next == NULL) 
		{
		finished=true;
		}
	}
	cout<<endl;	
}
// Menu for user interaction. 
void displayMenu()
{
   	cout<<"** U.S. City Information Program **";
	cout<<endl<<"(Enter number of choice and RETURN)";
	cout<<endl;
	cout<<endl<<"1)  Delete a city";
	cout<<endl<<"2)  Give the capital of a specified state";
	cout<<endl<<"3)  List all cities from a specified state";
	cout<<endl<<"4)  List all cities in the database";
	cout<<endl<<"5)  Quit the program"<<endl;
}

// Initializes list containing database and returns pointer to
// the start of the list.  Input stream is specified by input
// and will already be defined.
PtrType initialize(ifstream & input)
{
   char buf[BUFFERSIZE];
   char *bufptr = buf;

// Set first to point to the dummy node at the front of the list.
// Values set by default constructor includes NULL pointer.

   PtrType current = new CityNode;// Current is need to traverse the list.
   //cout<<"Debug: Displaying the origin Pointer Value here "<<current->next<<endl;
   PtrType head = NULL; // Needed to access the list.
   PtrType nextNode = NULL; 
   head=current; 
   int capitalTest;

   while (input.getline(bufptr,BUFFERSIZE)) // read first line for city
   {
	
	nextNode = new CityNode; // Creates a new node while.
	//cout<<"Debug: Displaying the Pointer Value here "<<nextNode->next<<endl;
	current->name = strdup(bufptr); /* stores the name of the city 
		  												from buffer to node. */

	input.getline(bufptr,BUFFERSIZE);  // read second line for state
   current->state = strdup(bufptr); /* stores the state from the 
		  														buffer to node.*/

	  input.getline(bufptr,BUFFERSIZE); // read third line for capital
	  capitalTest=atoi(bufptr);	//change name at some future point
	     if(capitalTest == 1) /* if the buffer holds a 1 it means you state 
												node is a capital*/
	     {
	     current->isCapital = true;
	     }
	     else  /* if the buffer holds a 0 it means you state node is 
						NOT a capital*/
	     {
	     current->isCapital = false;
	     }

	  input.getline(bufptr,BUFFERSIZE); // read fourth line for population	
     current->pop = atoi(bufptr); /* stores the population of a city from the 
		  										buffer to node.*/
	//cout<<"Debug: Displaying the origin Pointer Value here "<<current->next<<endl;
	current->next=nextNode;//  assign new node to tail of current node
	current=nextNode; /*reassign the varilable to the new empty nod to 
		  								be filled*/
		//cout<<"Debug: Displaying the Pointer Value here "<<nextNode->next<<endl;
    }
	//cout<<"Debug: Displaying the origin Pointer Value here "<<current->next<<endl;
	current->next=NULL;/* once finished with list creation seal the end 
	  									pointer with a NULL*/
	//printf("Pointer to next Node After: %p \n ",current->next);

#ifdef DEBUG
  if (debugON)
  {
    cout << "list after reading the input file\n";
	 curCnt=length(head);
    displayList(head,curCnt); 
  }
#endif
	PtrType mtyNode = new CityNode; 
	mtyNode->next=head; // resets head to point at the front of the list. 
	head=mtyNode; // and skip the empty node.
 
  return head;
}

// Function for implementing option 2.  It searches through the linked-list for 
// the inputted state and if the state has the capital with it, it will report 
// that capital. 
void findCapital(PtrType head,string input)
{

	if(head->next!=NULL) // Not done.
	{
		
		if (!(input == head->state)) // Not done
		{				
		//cout<<"Debug: Did not find match, start searching recursively."<<endl;
		findCapital(head->next,input); // Recursively search
		}
			else if(head->isCapital!=true) // Not a capital.
			{
			//cout<<"Debug: Did not find match, start searching recursively."<<endl;
			findCapital(head->next,input); // Recursively search.
			}	 
		
		 else if(head->isCapital==true)  // Is a capital.
		{
		//cout<<"Debug: Found a capital!"<<endl;
		displayNode(head);		
		}
	}
	if(head->next==NULL)// Did not find.
	{
		 //cout<<"Debug: Did not find a match in the list"<<endl;
		 cout<<endl<<"Did not find a Capital for the state of "
			  <<input<<" in this database."<<endl;
	}
}

// Function for implementing option 3.  It finds the state specified in the list 
// recursively while reporting the cities with the respective state.
void find_state(PtrType head,string input, bool finished)
{
	if(head->next!=NULL) // Not done.
	{
		
		if (!(input == head->state)) // Did not find.
		{				
			//cout<<"Debug: Did not find match, start searching recursively."<<endl;	
			find_state(head->next,input,finished); // Recursively search.
		}
		else if(input ==head->state) // Found a match.
		{
			//cout<<"Debug: Found a match!"<<endl;
			displayNode(head);	
			
			if(head->next!=NULL)
			{
				finished=true;
				find_state(head->next,input,finished);
			}	 
		}
	}
	else if(finished==false||head->next!=NULL) // Finished.
	{
		
	}
}

// Function for implementing option 1.  It find the node specified and deletes 
// the entire node with all of its contents while linking the previous node to 
// the next node.
void delete_node(PtrType& prev, string inputCity, string inputState)
{
	//cout<<"Debug: Head is currently holding "<<prev->next->name<<endl;
	//cout<<"Debug: User inputCity is holding "<<inputCity<<endl;

	 if(prev!=NULL && prev->next->next!=NULL) // Not done.
	 {
		PtrType head=prev->next;
			
			// Not a match.
			if (!(inputCity == prev->next->name)||!(inputState == prev->next->state)) 
			{
			//cout<<"Debug: Did not find a match searching recursively."<<endl;	
			delete_node(prev->next,inputCity, inputState); // Search recurisvely.
			}
				else
				{
				//cout<<"Debug: Found city/state name!"<<endl;
				PtrType tmpNode = prev;
				tmpNode->next=head->next;
			 	if(head->next==NULL) tmpNode->next=NULL;
				delete head->name;
				delete head->state;
				delete head;
				cout<<"The city was successfully deleted."<<endl<<endl;				
				}
	 }
	 else 
	 {
	  //cout<<"Debug: Did not find city name"<<endl;
	  cout<<"The city/state combination you entered is not in the list" 
	  <<" being examined."
	  <<" The city you were looking for was "<<inputCity
	  <<" and the state you were looking for was "<<inputState<<"."<<endl;
	 }
}

string getInput(string someOutput)
{
	string userInput;
	cout<<someOutput<<endl;
	getline(cin,userInput,'\n');/*this will get the whole line instead 
	  									of one word delimited by a space*/
	cout<<endl;
	return userInput;
}

int main(int argc, char *argv[])
{
	 ifstream city_input;
	  PtrType head; 
	 char buffer[BUFFERSIZE];
	 string outPut2User;
	 string outPut2User2;
	 bool isFound=false;
	 string inputState;

  if(argc > 1) // open file and initialize database
  {
   (city_input.open(argv[1]));
   head = initialize(city_input);
  }
  else 
   head = NULL; // initialize to empty

  // specify code for menu display and processing of choice

  bool finished = false;
  while (!(finished))
  {
	displayMenu();// interactive menu display

	#ifdef DEBUG2
	  if (debugON2)
	  {
		 cout << endl<<"Current list size"<<curCnt<<endl;
		
	  }
	#endif
   cin.getline(buffer,BUFFERSIZE);
   int choice = atoi(buffer);

	switch(choice)
	{

	case 1:{ // Option 1: Delete Node.
				 
		  outPut2User="Enter the city you wish to delete.";
		  outPut2User2="Enter the state of the city to delete.";
		  delete_node(head,getInput(outPut2User),getInput(outPut2User2));
		  break;
		}
					  
	case 2:{ // Option 2: Find Capital with a nested menu.
		  
		  const int size = 52;  
		  string cityArray [size]; // Array to hold all possible choices.
		  bool done = false; // Outer loop check.
		  bool finished = false; // Inner loop check.
		  int userInput; // Holds, you guessed it, users input.
		  int count = 1;// Used to output list for nested menu.
		  int index = 2; // CityArray's index. 
		  PtrType temp; // Temp pointer to reset head after loop.
		  temp = head;	// Set temp to point at head.
			 
			  while (!done) // Still in nested menu.
			  {
				cout<<endl;
				cout<<"State capital information"<<endl;
				cout<<"(Enter number of choice and RETURN)"<<endl;
			
					while(!finished) // output all nodes that are capitals.
					{
						if (count == 1) // Always set 1 choice to "ignore request."
						{						
						cout<<count<<". "<<"Ignore request"<<endl;
						count++;
						}					   
						if (head->isCapital == true) // Is capital
						{ 
						cout<<count<<". "<<head->state<<endl;
						cityArray[index] = head->state;
						index++;
						count++;
						}
					   head = head->next;
						if(head->next == NULL) finished = true; // finished.	
						
					}
					
					count = 1; // Reset count to 1 to enable user to revisit menu.
					finished = false;
					head = temp; // Reset pointer to enable user to revisit menu.
					
					//cout<<"Debug: I am here"<<endl;
					//cout<<"Array is holding: "<<cityArray[counter]<<endl;
					
					cin>>userInput;			
					if(userInput == 1) break; // Done.
					else findCapital(head->next, cityArray[userInput]); //Finds Cap.
					
				}	
			}
		  
					  
	case 3:{ // Option 3: List all cities from specified state.
		  outPut2User="Enter a state to find it's cities: ";
		  find_state(head->next,getInput(outPut2User),isFound);
		  cout<<endl;
		  break;
		}
					  
	case 4:{ // Option 4: List all information in database.
		if(head==NULL&&head->next==NULL)break;
		    else{
			  displayList(head);
			  break;
			   	     }
			}
					  
	case 5:{ // Option 5: Quit the program.
		  finished=true;
		  //break;
		
		}
	}
 }	
return 0;
}
