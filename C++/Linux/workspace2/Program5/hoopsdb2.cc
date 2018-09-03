 /*
Name: Christopher M West, Patrick Rawlings
  Class at ECU:3300-001
  Assignment Due Date: Wednesday December 8, 5:00 P.M.
  Assignment Number: Program 5 (p5)
  Professor: Dr. Ronnie Smith
 
  Description:
*/

#include <iostream>
#include <iomanip>
#include <fstream>
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

/*****************************************************************************/

/*
	this is a funtion that take in a Treeitem to print a single instance of the two fields inside the
	TreeItem. also another variable uses a boolean value to determine if we want to output 
	the information as formated or not. We used the <iomanip> library to preform the formatting. 
*/
void printItem(TreeItem item, bool formatOn)
{
    if (formatOn == true)
    {
    cout << setiosflags(ios::right);
    cout<<setw(20)<<item.school<<":\t"<<item.gamesWon<<" wins"<<endl;
    }
    else 	
    {
    cout<<item.school<<":\t"<<item.gamesWon<<" wins"<<endl;
    }
}
/* 
	this nice little function is to seperate the menu and the last responce to the choice 
	that was made. it is the result of the iomanip library we needed to format the printItem to
	right justify the school name. so we decided to use it again to help cleanup presentation of 
	the screen output.
*/
void printSpacer()
{
    cout<<endl<<setw(79)<<setfill('*')<<" "<<endl;
    cout<<setw(79)<<setfill(' ')<<" "<<endl;
}

int treeHeight(TreePtr root) {
  if (root==NULL) {
    return(0);
  }
  else {
    // compute the depth of each subtree
    int lBranch = treeHeight(root->left);
    int rBranch = treeHeight(root->right);
    // use the larger one
    if (lBranch > rBranch) return(lBranch+1);
    else return(rBranch+1);
  }
}

bool gamesWon(TreePtr root, string input)
{
	if(root==NULL)
	{
	cout<<endl<<"Did not find '"<< input <<"' in the database."<<endl;
	return false;
	}

	else if(input==root->item.school)
	{	
	printItem(root->item,false);
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

void postOrdTraverse( TreePtr root)
    {
        if (root!=NULL)
            {
           postOrdTraverse( root->left );    	// Print items in left subtree.
           postOrdTraverse( root->right );   // Print items in right subtree.
           printItem(root->item, true);     	 // Print the root item.
            }
    }

void preOrdTraverse( TreePtr root)
    {
        if (root!=NULL)
            {
           printItem(root->item, true);      	// Print the root item.
           preOrdTraverse( root->left );    	// Print items in left subtree.
           preOrdTraverse( root->right );   	// Print items in right subtree.
            }
    }

void inOrdTraverse( TreePtr root)
    {
        if (root!=NULL)
            {
           inOrdTraverse( root->left );   		 // Print items in left subtree.
           printItem(root->item, true);      	// Print the root item.
           inOrdTraverse( root->right );   		// Print items in right subtree.
            }
    }
 
bool gamesWon(TreePtr root, int input)
{
	if(root==NULL)
	{
	cout<<endl<<"Did not find '"<< input <<"' in the database."<<endl;
	return false;
	}
	
	else if(input<root->item.gamesWon)
	{
	return gamesWon(root->left,input);
	}
	
	else if(input==root->item.gamesWon)
	{	
	printItem(root->item,true);
	}

	else
	{
	return gamesWon(root->right,input);
	}
}

void inOrdFindWins( TreePtr root, int wins)
    {
        if (root!=NULL)
            {
           inOrdFindWins( root->left,wins );    		// Print items in left subtree.
			if(wins==root->item.gamesWon)
					{
					
				 	printItem(root->item, true);      			// Print the root item.
					}
           inOrdFindWins( root->right,wins );   		// Print items in right subtree.
            }
    }

string getInput(string someOutput)
{
	cout<<someOutput<<endl<<endl;
	string userInput;
	getline(cin,userInput,'\n');		//this will get the whole line instead 
	cout<<endl;
	return userInput;
}

int getInputNum(string someOutput)
{
	cout<<someOutput<<endl<<endl;
	int userNumInput;
	cin>>userNumInput; 
	cout<<endl;
	return userNumInput;
}

void insertItem (TreePtr &root, TreePtr &newNode)
{
    if(root==NULL)
    {
        root = new TreeNode(newNode->item,NULL,NULL);
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
/* 
	Top level function for option 1 for building the database
   db_input is connected to the external file to be read using the getline
   command. returns pointer to constructed binary search tree.
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
   
           /*this is to get the data for the first node then determine where 
				the next node should be placed*/
            db_input.getline(bufptr,BUFFERSIZE);
            
            name = strdup(bufptr);								// grab buffer as char array
            current->item.school=name;					// fill this node's school with it's 
																						// name
            db_input.getline(bufptr,BUFFERSIZE);
            tmpNum=atoi(bufptr);								// grab buffer as integer
            current->item.gamesWon=tmpNum;	// fill this node's number of games 
																						// won with the total for that school
   while (db_input.getline(bufptr,BUFFERSIZE)) // capture data to fill this 
																							// node until end of file
        {
            #ifdef DEBUG
              if (debugON)
                  {
                    printItem(current->item, true);		// this was for debug
                }
            #endif
            nextNode = new TreeNode; 					// only creat a node it needed i.e. 
																						// somthing in buffer
            current=nextNode;
            name = strdup(bufptr);								// grab buffer as char array
            current->item.school=name; 					// fill this node's school with it's 
																						// name
            db_input.getline(bufptr,BUFFERSIZE);
            tmpNum=atoi(bufptr);								// grab buffer as integer
            current->item.gamesWon=tmpNum;	// fill this node's number of games 
																						// won with the total for that school
            insertItem(root,current);							// function call
            
        }
        return root;
}

/* 
	Top level function for option 2 for building the database 
	db_input is connected to the external file to be read using the getline
	command returns pointer to constructed binary search tree.
*/
void selectionSort(TreeItem item[], int arrayPopulatedSize) {

      int outerIndex; 
		int innerIndex;
		int refIndex; 
		TreeItem tmpItem;    

      for (outerIndex = 0; outerIndex < arrayPopulatedSize - 1; outerIndex++) 
			{
            refIndex =outerIndex;
            for (innerIndex = outerIndex + 1; innerIndex < arrayPopulatedSize;innerIndex++)
					{
						 if (item[innerIndex].school < item[refIndex].school)
							{
                     	refIndex = innerIndex;
							}
					}
            if (refIndex != outerIndex)
				 	{
                  tmpItem = item[outerIndex];
                  item[outerIndex] = item[refIndex];
                  item[refIndex] = tmpItem;
            	}
      }
}

TreePtr makeTree(TreeItem data[],int first,int last)
{
//cout<<"DEBUG: I AM HERE."<<endl;
cout<<"DEBUG: First = "<<first<<endl;
cout<<"Debug: Last = "<<last<<endl;
	 int middle;

TreePtr root=NULL;
	if (first<=last) 
	{
	middle= (first+last)/2;
		
	
	root->item=data[middle];
	root=makeTree(data,first,middle-1 );
	root=makeTree(data,middle+1,last);
	}
	return root;
}

TreePtr sortInit(ifstream & db_input)
{
 char buf[BUFFERSIZE];
   char *bufptr = buf;

	TreeItem current [65];
	TreeItem tmpTreeItm;
	//TreeItem TreeItm
   char* name;
   int tmpNum=0;
	int index=0;

	//load the array
   while (db_input.getline(bufptr,BUFFERSIZE)) // capture data to fill this 
																							// node until end of file
        {
				//TreeItm=new TreeItem;
				//TreeItem tmpTreeItm=TreeItm;            
				name = strdup(bufptr);								// grab buffer as char array
            tmpTreeItm.school=name; 				// fill this node's school with it's 
																						// name
            db_input.getline(bufptr,BUFFERSIZE);
            tmpNum=atoi(bufptr);								// grab buffer as integer
            tmpTreeItm.gamesWon=tmpNum;	// fill this node's number of games 
																						// won with the total for that school
				current[index]=tmpTreeItm;
				index++;
        }
			selectionSort(current,index);

			//cout<<"DEBUG: current ="<< current << "index = " << index<<endl;
        return makeTree(current,0,index);

}

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
   string outPut2User;

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
    root = sortInit(db_input);
   }

// Code for interactive processing goes here.
 bool finished = false;
  while (!(finished))  			// display entire menu until program is killed.
  {
    displayMenu();				// interactive menu display.

   cin.getline(buffer,BUFFERSIZE);
   int choice = atoi(buffer);
   
   // code for choosing correct functionality based on menu choice goes here.
    switch(choice)
    {

    case 1:{ // Option 1: 
	    outPut2User="Enter a team to see it's wins.";
	    gamesWon(root,getInput(outPut2User));
            printSpacer();
              break;
        }
                      
    case 2:{ // Option 2:
				 outPut2User="Enter a score to see which team(s) have this score.";
	   		 inOrdFindWins(root,getInputNum(outPut2User));
             printSpacer();
				 break;
        }
                      
    case 3:{ // Option 3:
            postOrdTraverse(root);
            printSpacer();
            break;
        }
                      
    case 4:{ // Option 4:
            preOrdTraverse(root);
            printSpacer();
            break;
            }
                      
    case 5:{ // Option 5:     
              inOrdTraverse(root);
              printSpacer();
              break;
        }
    case 6:{ // Option 6:
          cout<<"Tree Depth of the tree is: "<<treeHeight(root)<<endl;
          printSpacer();
          break;
        }
    case 7:{ // Option 7: Quit the program.
          finished=true;
          printSpacer();
          break;
        }
    }
}
   return 0;
}
