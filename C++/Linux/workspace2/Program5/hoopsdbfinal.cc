 /*
Name: Christopher M West, Patrick Rawlings
  Class at ECU:3300-001
  Assignment Due Date: Wednesday December 8, 5:00 P.M.
  Assignment Number: Program 5 (p5)
  Professor: Dr. Ronnie Smith
 
  Description:
  This program takes in data from a file (south.txt) that is formatted with data
  like below:

	this program can either bring the data into a binary search tree like it is
	are the file is laid out or can bring in the data sort it alphabetically and
	then create a balanced binary search tree with the shortest depth.
	
	this program presents a menu of 7 question to interact with the data just 
	brought into the tree structure. It use nodes for the tree an encapsulates
	the inputted data pairs into a struct inside each node.
	
	the tree can be outputted to the screen either as inorder(alpha-order),
	preorder, or postorder traversal of the tree.
	
	the tree can be searched to determine if data entered by the user at the 
	prompt matches what is in the tree structure.
	
	the output is either outputted as formated or unformated based on the need
	to do so.
:)
*/
#include <iostream>
#include <iomanip>//not in base template added for our needs
#include <fstream>
#include <limits>//not in base template added for our needs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*****************************************************************************/
using namespace std;
const int BUFFERSIZE = 512;  // use for buffer size
typedef char * KeyType;
//#define DEBUG
bool debugON = true;// global debugging flag.
/*****************************************************************************/
/* 
	This Struct is use as a part of the TreeNode Struct below. We are creating a
	definition of an complex-dataType which consist of two different primative 
	data types. This is the foundation of objects in object-oriented 
	programming languages. A struct with functions is-a class (object)
*/
struct TreeItem
{
	string school;
	int  gamesWon;
    
	TreeItem()//base case empty item: set everything to empty , Zero or NULL
	{
		school="";
	gamesWon=0;
	} 
};
/*****************************************************************************/
/* 
	another struct. This Struct was defined pre-created in the project template.
 	it is the building blocks of a binary search tree with default constructors
*/
struct TreeNode 
{
	TreeItem item;
	TreeNode * left;
	TreeNode * right;

	TreeNode(TreeItem value, TreeNode * lval, TreeNode * rval)
	{
		item = value;//fill the node with an item
		left = lval;//set this pointer
		right = rval;//set this pointer
	}

	TreeNode()//base case empty node: set everything to empty , Zero or NULL
	{
		item.school="";
		item.gamesWon=0;
		left=NULL;
		right=NULL;
	}
};
typedef TreeNode * TreePtr;
/*****************************************************************************/
/*
	this is a funtion that take in a Treeitem to print a single instance of the 
 	two fields inside the TreeItem. also another variable uses a boolean value 
 	to determine if we want to output the information as formated or not. We 
 	used the <iomanip> library to preform the formatting. 
*/
void printItem(TreeItem item, bool formatOn)
{
	if (formatOn == true)//formated output
	{
		cout << setiosflags(ios::right);// set right alignment of text
		cout<<setw(20)<<item.school<<":\t"<<item.gamesWon<<" wins"<<endl;
	}
	else //unformated output	
	{
		cout<<item.school<<":\t"<<item.gamesWon<<" wins"<<endl;
	}
}
/*****************************************************************************/
/* 
	this nice little function is to seperate the menu and the last responce to 
 	the choice that was made. it is the result of the iomanip library we needed 
 	to format the printItem to right justify the school name. so we decided to 
 	use it again to help cleanup the presentation of the screen output and make 
 	it easier to read instead of jumbled looking.
*/
void printSpacer()
{
	cout<<endl<<setw(79)<<setfill('*')<<" "<<endl;//create a line of'*'
	cout<<setw(79)<<setfill(' ')<<" "<<endl; //reset the setfill to empty space
}
/*****************************************************************************/
/* 
	Measure the depth of the binary search tree or any binary tree and return 
	the result of the depth as a whole number
*/
int treeHeight(TreePtr root) 
{
	if (root==NULL) 
	{
		return(0); //have found end of tree on this branch (NULL Leaf)
	}
	else 
	{
		// compute the depth of each subtree
		int lBranch = treeHeight(root->left);//call self left
		int rBranch = treeHeight(root->right);//call self right
		// use the larger total and return it
		if (lBranch > rBranch) return(lBranch+1);
		else return(rBranch+1);
	}
}
/*****************************************************************************/
/*
	after receiving the answer to the question of what school to find the score 
	of do a traversal of the tree to find the school. if found during the 
	recursion call printItem w/o formating or an empty leaf is empty leaf 
	is encountered then exit the funtion and printout a not found message
*/
bool gamesWon(TreePtr root, string input)
{
	if(root==NULL)//did not find a school with that name
	{
	cout<<endl<<"Did not find '"<< input <<"' in the database."<<endl;
	return false;
	}

	else if(input==root->item.school)
	{	
	printItem(root->item,false);// found the school print it out to user
	}
	
	else if(input<root->item.school)
	{
	return gamesWon(root->left,input);//not found yet look somemore to the left
	}
	
	else
	{
	return gamesWon(root->right,input);//not found yet look somemore to theright
	}
}
/*****************************************************************************/
/*
	Traverse the entire tree and on the recusive collapse call printItem 
	formatted until the entire tree is traversed
*/
void postOrdTraverse( TreePtr root)
{
	if (root!=NULL)
	{
		postOrdTraverse( root->left );	// Print items in left subtree.
		postOrdTraverse( root->right );	// Print items in right subtree.
		printItem(root->item, true);		// Print the root item.
	}
}
/*****************************************************************************/
/*
	call printItem formatted then traverse the entire tree recusivively on each 
	recursive iteration call printItem formatted and recurse again until the 
	entire tree is traversed
	
*/
void preOrdTraverse( TreePtr root)
{
	if (root!=NULL)
	{
		printItem(root->item, true); 		// Print the root item.
		preOrdTraverse( root->left );  	// Print items in left subtree.
		preOrdTraverse( root->right );  	// Print items in right subtree.
	}
}
/*****************************************************************************/
/*
	Traverse the entire left tree then recurse and on the recusive collapse of 
	the left subtree call printItem formatted until the entire tree is traversed
*/
void inOrdTraverse( TreePtr root)
{
	if (root!=NULL)
	{
		inOrdTraverse( root->left );		// Print items in left subtree.
		printItem(root->item, true);		// Print the root item.
		inOrdTraverse( root->right );		// Print items in right subtree.
	}
}
/*****************************************************************************/ 
/*
	Take in user inputted number and compare it to every node in the tree to see 
	if it matches. number is compare to the root->item.gamesWon of each node.
	if a match call printItem formatted (because there maybe more than one).
	exit if you find an emtpy leaf. 
	if no match is found do nothing and exit function.
	this is implemented in the same manner as the In Order Traversal above.
	(alpha-order printout)	 
*/
void inOrdFindWins( TreePtr root, int wins)
{
	if (root!=NULL)
	{
		inOrdFindWins( root->left,wins );	// Print items in left subtree.
		if(wins==root->item.gamesWon)
		{
			printItem(root->item, true);		// Print the root item.
		}
		inOrdFindWins( root->right,wins );	// Print items in right subtree.
	}
}

/*****************************************************************************/
/*
	This funtion receive a string to ask the user for input. Then returns that 
	input as a string object. this one funtion is used for two menu choices
	in this program
*/
string getInput(string someOutput)
{
	cout<<someOutput<<endl<<endl;	//output to user...ask a question
	string userInput;
	cout<<"Debug: You found me!"<<endl;
	getline(cin,userInput,'\n');	//this will get the whole line instead 1 word 
	cout<<endl;							//space formating
	return userInput;					// is that your final answer?
}
/*****************************************************************************/
/* 
	like getInput above the purpose of the function is to get something from 
	the user to be used in another function call by this funtions caller
	the difference is this returns an int and makes sure the user is only 
	inputting a numeric value. It will question to re-enter a number until the 
	user does enter a number.
	if you do not check for this then you send the menu into a continuios loop
	of outputing the menu.
*/
int getInputNum(string someOutput)
{
	cout<<someOutput<<endl<<endl;	//output to user...ask a question
	int userNumInput;	
	// we need this to make sure that only a number was input by the user 
	// using the <limits> library to test for this.
	while (!(cin>>userNumInput))
	{
			cout<<"you did not enter a number, please try again."<<endl;
			cout<<someOutput<<endl<<endl;//output to user...ask a question
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
	} 
	cout<<endl;					//space formating
	return userNumInput; 	// is that your final answer?
}

/*****************************************************************************/
/* 
	this is a way to insert into the tree alpha order of nodes where anything
	that is before the root of the tree alphabeticlly is sent to the left subtree
	for entry and those after root are sent to the right subtree for entry.
	this desicion making is done on every new recursive call down in the tree 
	until the node is placed into the tree.
	this is used for startup option 1.
*/
void insertItem (TreePtr &root, TreePtr &newNode)
{
	if(root==NULL)								// found a place to insert node
	{
		root = new TreeNode(newNode->item,NULL,NULL);
	}    
	else if(newNode->item.school.compare(root->item.school)<0)
	{
		insertItem(root->left, newNode);//have not found home 4 this node go left
	}
	else if(newNode->item.school.compare(root->item.school)>0)
	{
		insertItem(root->right, newNode);//have not found home 4 this node goright
	}
}
/*****************************************************************************/
/* 
	Top level function for option 1 for building the database 
   db_input is connected to the external file to be read using the getline
   command. returns pointer to constructed binary search tree.
*/
/*
	this can result in an unbalanced tree and ultimately defeat the purpose of
	creating a binary search tree.
*/
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
   /*	this is to get the data for the first node then determine where 
		the next node should be placed*/
	db_input.getline(bufptr,BUFFERSIZE);
	name = strdup(bufptr);		// grab buffer as char array
	current->item.school=name;	// fill this node's school with it's 
										// name
	db_input.getline(bufptr,BUFFERSIZE);
	tmpNum=atoi(bufptr);				// grab buffer as integer
	current->item.gamesWon=tmpNum;// fill this node's number of games 
											// won with the total for that school
	while (db_input.getline(bufptr,BUFFERSIZE))// capture data to fill this 
																// node until end of file
	{
	#ifdef DEBUG
		if (debugON)
		{
			printItem(current->item, true);	// this was for debug
		}
	#endif
		nextNode = new TreeNode;		// only creat a node it needed i.e. 
												// somthing in buffer
		current=nextNode;
		name = strdup(bufptr);			// grab buffer as char array
		current->item.school=name;		// fill this node's school with it's 
												// name
		db_input.getline(bufptr,BUFFERSIZE);
		tmpNum=atoi(bufptr);				// grab buffer as integer
		current->item.gamesWon=tmpNum;// fill this node's number of games 
												// won with the total for that school
		insertItem(root,current);		// function call      
	}
	return root;
}
/*****************************************************************************/
/*
	simple but effective sorting algorithm to sort string variables int a struct
	datatype. the items being compared are item[int].school. This sort is being 
	implemented on an array of type TreeItem.
*/
void selectionSort(TreeItem item[], int arrayPopulatedSize) 
{
	int outerIndex; 
	int innerIndex;
	int refIndex; 
	TreeItem tmpItem; //used for the swaping around in the array
	// sort array eliminating the top(0) index after each iteration    
	for (outerIndex = 0; outerIndex < arrayPopulatedSize ; outerIndex++) 
	{
		refIndex =outerIndex;
		for (innerIndex = outerIndex + 1; innerIndex < arrayPopulatedSize;
				innerIndex++)
		{
			if (item[innerIndex].school < item[refIndex].school)
			{
				refIndex = innerIndex;	// mark as best to move to top of current 
												// indexed list
			}
		}
		/* 
			at the end of one complete iteration through the array move 
			the smaller item to the begining of the array segment that is 
			being compared only if it needs to be moved.
		*/
		if (refIndex != outerIndex)
		{
			tmpItem = item[outerIndex];
			item[outerIndex] = item[refIndex];
			item[refIndex] = tmpItem;
		}
	}
}
/*****************************************************************************/
/*
	this is a balanced insertNode by using a sorted TreeItem array an grabs the 
	middle position to insert at the root of the tree to create a balance binary 
	search tree irregardless of how the data was brought into the program.
	this will create the shallowest tree of the two types created in this program
	and shallow means faster search capable than an unbalanced tree.
	this matters on very large trees.
*/
TreePtr makeTree(TreeItem data[],int first,int last)
{
	int middle=0;
	TreePtr root=NULL;// create first node but empty	
	if (first<=last) 
	{
		middle= (first+last)/2;/* determine where in the array needs to be added 
											to the tree at this point in the build*/
		root=new TreeNode(data[middle],NULL,NULL);//insert data in a new spot
		root->left=makeTree(data,first,middle-1);//fill the left subtree
		root->right=makeTree(data,middle+1,last);//fill the right subtree
	}
	return root;//return the completed binary tree root pointer
}
/*****************************************************************************/
/* 
	Top level function for option 2 for building the database 
	db_input is connected to the external file to be read using the getline
	command returns pointer to constructed binary search tree.
*/
TreePtr sortInit(ifstream & db_input)
{
	char buf[BUFFERSIZE];// create a character buffer for data input
	char *bufptr = buf;
	TreeItem current [65];
	TreeItem tmpTreeItm;
	char* name;	// used to temporary hold the school's name b4 adding 
					// to a new TreeItem
	int tmpNum=0;
	int index=0;
	//load the array from the file(south.txt) at program start
	while (db_input.getline(bufptr,BUFFERSIZE)) // capture data to fill this 
																// node until end of file
	{     
		name = strdup(bufptr);					// grab buffer as char array
		tmpTreeItm.school=name; 				// fill this node's school with it's 
														// name
		db_input.getline(bufptr,BUFFERSIZE);
		tmpNum=atoi(bufptr);						// grab buffer as integer
		tmpTreeItm.gamesWon=tmpNum;			// fill this node's number of games 
														// won with the total for that school
		current[index]=tmpTreeItm;
		index++;
	}
	// sort the tree alphabetically in order a to z
	selectionSort(current,index);
	// inject the sorted array into a balance binary search tree and return the
	//pointer to the root of the tree to the caller of this funtion
	return  makeTree(current,0,index-1);
}
/*****************************************************************************/
//Menu for user interaction.
void displayMenu()
{
	cout<<"** NCAA Tourney Information Program **";
	cout<<endl<<"(Enter number of choice and RETURN)";
	cout<<endl;
	cout<<endl<<"1)  ***Print information on a given team";
	cout<<endl<<"2)  ***Tell how many games every team in a given division has won";
	cout<<endl<<"3)  ***Tell which teams won > n games";
	cout<<endl<<"4)  Print all information via postorder traversal";
	cout<<endl<<"5)  Print all information via preorder traversal";
	cout<<endl<<"6)  Print depth of the tree";
	cout<<endl<<"7)  Quit the program"<<endl;
}
/*****************************************************************************/
int main(int argc, char *argv[])
{
	TreePtr root; 			//establishing the base of the tree
	ifstream db_input;	//input file stream
	string outPut2User;	// used to send a prompt question to the user
	char buffer[BUFFERSIZE];
	// Open input file based on second command line argument
	db_input.open(argv[2]);
	// Invoke proper DB initialization based on first command line argument
	if (atoi(argv[1]) == 1)
	{	// can create an unbalanced tree depending on input order
		root = fileInit(db_input);
	}
	else
	{	// creates a balanced tree for optimal search speed
		root = sortInit(db_input);
	}
	// user interaction section
	bool finished = false;
	printSpacer();// for formating and improved presentation & readablity
	while (!(finished))	// display entire menu until program is killed.
	{
		displayMenu();		// interactive menu display.
		cin.getline(buffer,BUFFERSIZE);
		/*assume an integer will be input and will 
		do nothing if nothing otherwise, it will just redisplay the menu
		****************************************************************
		the ASCII for 1 thru 7 are not on the keyboard though 
		8 is the backspace key
		****************************************************************
		*/
		int choice = atoi(buffer);
		
		/***********************************************************************/
		/*
			this is the switch/case block used to complete the requested action 
			of the user
		*/
		switch(choice)
		{
			case 1:
			{ // Option 1: Print information on a given team
				cout<<"Debug: you have selected choice 1."<<endl;				
				//outPut2User="Enter a team to see it's wins.";					
				//gamesWon(root,getInput(outPut2User));
				printSpacer();
				break;
			}
			case 2:
			{ // Option 2: Tell how many games every team in a given division has won
				cout<<"Debug: You have selected choice 2."<<endl;				
				//outPut2User="Enter a score to see which team(s) have this score.";				
				//inOrdFindWins(root,getInputNum(outPut2User));
				printSpacer();
				break;
			}
			case 3:
			{ // Option 3: Tell which teams won > n games
				cout<<"Debug: You have selected choice 3."<<endl;
				//postOrdTraverse(root);
				printSpacer();
				break;
					}
			case 4:
			{ // Option 4: Print all information via postorder traversal
				postOrdTraverse(root);
				printSpacer();
				break;
			}
			case 5:
			{ // Option 5: Print all information via preorder traversal     
				preOrdTraverse(root);
				printSpacer();
				break;
			}
			case 6:
			{ // Option 6: Print depth of the tree
				cout<<"Tree Depth of the tree is: "<<treeHeight(root)<<endl;
				printSpacer();
				break;
			}
			case 7:
			{ // Option 7: Quit the program.
				finished=true;
				printSpacer();
				break;
			}
		}
	}
   return 0;
}
