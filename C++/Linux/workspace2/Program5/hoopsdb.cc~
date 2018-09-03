/*
Name: Christopher M West, Patrick Rawlings
  Class at ECU:3300-001
  Assignment Due Date: Wednesday December 8, 5:00 P.M.
  Assignment Number: Program 5 (p5)
  Professor: Dr. Ronnie Smith
  
  Description: 
  
  
  
  
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

const int BUFFERSIZE = 512;  // use for buffer size

typedef char * KeyType;

// You are responsible for details of a TreeItem

struct TreeItem {
	string school;
	int  gamesWon;
	
	TreeItem()
	{
		school="";
		gamesWon=0;
	}
	
};

struct TreeNode {
  TreeItem item;
  TreeNode * left;
  TreeNode * right;

  TreeNode(TreeItem value, TreeNode * lval, TreeNode * rval) 
  {
		item = value;
		left = lval;
		right = rval;
  }
  
   TreeNode()
   {
		item.school="";
		item.gamesWon=0;
		left=NULL;
		right=NULL;
	}
};

typedef TreeNode * TreePtr;

// You are responsbile for details of printItem

void printItem(TreeItem item)
{
	cout<<item.school<<":\t"<<item.gamesWon<<" wins"<<endl;
}
  
/* Top level function for option 1 for building the database
// db_input is connected to the external file to be read using the getline
// command.
// returns pointer to constructed binary search tree.
*/

bool gamesWon(TreePtr root, string input)
{
	if(root==NULL)
	{
	return false;
	}

	else if(input==root->item.school)
	{
	printItem(root->item);
	}
	
	else if(input<root->item.school)
	{
	return gamesWon(root->left,input);
	}
	
	else
	{
	return gamesWon(root->right,input);
	}
}


void insertItem (TreePtr &root, TreePtr & newNode)
{
	if(root==NULL)
	{
		root = new TreeNode(newNode->item,NULL,NULL);
		//printItem(root->item);// this was for debug
	}	
	
	else if(newNode->item.school.compare(root->item.school)<0)
	{
		insertItem(root->left, newNode);
	}

	else if(newNode->item.school.compare(root->item.school)>0)
	{
		insertItem(root->right, newNode);
	}
}

TreePtr fileInit(ifstream & db_input)
{
	char buf[BUFFERSIZE];
   char *bufptr = buf;
   

  TreePtr current = new TreeNode;
	TreePtr root = NULL; 
   TreePtr nextNode = NULL;
   
   root =current; 
   char* name;
   int tmpNum=0;
   
   		//this is to get the data for the first node then determine where the next node should be placed
			db_input.getline(bufptr,BUFFERSIZE);
			
			name = strdup(bufptr);// grab buffer as char array
			current->item.school=name; //fill this node's school with it's name
			db_input.getline(bufptr,BUFFERSIZE);
			tmpNum=atoi(bufptr);// grab buffer as integer
			current->item.gamesWon=tmpNum;//fill this node's number of games won with the total for that school
			//printItem(root->item);// this was for debug
      
   while (db_input.getline(bufptr,BUFFERSIZE)) // capture data to fill this node until end of file
		{
			printItem(current->item);// this was for debug
			nextNode = new TreeNode; //only creat a node it needed i.e. somthing in buffer
			current=nextNode;
			name = strdup(bufptr);// grab buffer as char array
			current->item.school=name; //fill this node's school with it's name
			db_input.getline(bufptr,BUFFERSIZE);
			tmpNum=atoi(bufptr);// grab buffer as integer
			current->item.gamesWon=tmpNum;//fill this node's number of games won with the total for that school
			insertItem(root,current);//function call
			//printItem(current->item);// this was for debug
		}
		return root;
}

/* Top level function for option 2 for building the database
// db_input is connected to the external file to be read using the getline
// command
// returns pointer to constructed binary search tree.*/
/*
TreePtr sortInit(ifstream & db_input) 
{
}*/

 //Menu for user interaction. 
void displayMenu()
{
   cout<<"** NCAA Tourney Information Program **";
	cout<<endl<<"(Enter number of choice and RETURN)";
	cout<<endl;
	cout<<endl<<"1)  Tell how many game a team won";
	cout<<endl<<"2)  Tell which teams won \"n\" games";
	cout<<endl<<"3)  Print all information via postorder traversal";
	cout<<endl<<"4)  Print all information via preorder traversal";
	cout<<endl<<"5)  Print all information via inorder traversal";
	cout<<endl<<"6)  Print depth of the tree";
	cout<<endl<<"7)  Quit the program"<<endl;
}

int main(int argc, char *argv[])
{
   TreePtr root;
   ifstream db_input;
   string input;


// Additional declarations needed for main should be put here
char buffer[BUFFERSIZE];
// Open input file based on second command line argument
   db_input.open(argv[2]);

// Invoke proper DB initialization based on first command line argument

   if (atoi(argv[1]) == 1)
   {
     root = fileInit(db_input);
   }
   else
   {
    // root = sortInit(db_input);
   }

// Code for interactive processing goes here.
 bool finished = false;
  while (!(finished))  // display entire menu until program is killed.
  {
	displayMenu();// interactive menu display.

	#ifdef DEBUG2
	  if (debugON2)
	  {
	    cout << endl<<"Current list size"<<curCnt<<endl;
		
	  }
	#endif
   cin.getline(buffer,BUFFERSIZE);
   int choice = atoi(buffer);
   
   // code for choosing correct functionality based on menu choice goes here.
	switch(choice)
	{

	case 1:{ 
		cout<<"Enter a team to see it's wins."<<endl;
		cin>>input;
		gamesWon(root,input);
		  break;
		}
					  
	case 2:{ 
		  break;
		}
					  
	case 3:{ 
		  break;
		}
					  
	case 4:{ 
		break;
		}
					  
	case 5:{ 
		 
		  break;
		}
	case 6:{ 
		 
		  break;
		}
	case 7:{ 
		  finished=true;
		  break;
		}
	}
  }

   return 0;
}
