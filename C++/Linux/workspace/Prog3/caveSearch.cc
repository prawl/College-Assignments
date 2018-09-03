/*
  Name: Patrick Rawlings
  Class at ECU: CSCI 3300
  Assignment Due Date: 3/28/11
  Assignment Number: p3
  Professor: Dr. Ronnie Smith
  
  Description: The purpose of this program is to take user input in the 
  format of size of the multidimensional array and the letters 
  'T' - traversable and 'X' - not traversable and determine if it is possible
  to navigate through every 'T' starting at position (1,1) and ending back at
  position (1,1).  See examples in the comments at the end of the program for
  a sample input.    
*/ 

using namespace std;
#include <iostream>

char caveInfo [50][50]; // Only global variable allowed.  Specified by 
								// instructions.
int main (){

int maxX;
int maxY;
int rowNum = 1;
int curX = 1;
int curY = 1;

cout<<"Start input here."<<endl;
cin>>maxX>>maxY;

for(int index = 0; index < maxX; index++)
{
	for(int index2 = 0; index2 < maxY; index2++)
	{
	caveInfo[index][index2] = 'B';
	}
}
cout<<"Debug: I am here"<<endl;


/*
rowNum = maxY;

	while(!cin.eof())
		{
			cin.getline(&caveInfo[rowNum][1],(maxX+1));
			rowNum--;		
		}
cout<<"DEBUG: I am here!"<<endl;
*/
}













/**************************************************************************/
/*  PROGRAM ASSIGNMENT

*/

