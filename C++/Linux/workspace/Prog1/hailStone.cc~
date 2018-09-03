/*
  Name: Patrick Rawlings
  Class: CSCI 3300
  Assignment Due Date: 2/7/11 at 5:00
  Assignment Number: Program 1
  Professor: Dr. Ronnie Smith
  Grade: 
  
  Description: The purpose of this program is to take two user inputted numbers
	(a min and a max) and run them through the HailStone sequence returning which
	number between the min and max produces the longest hailstone sequence. 
	The HailStone sequence determines inclusively which whole interger in that range
	of numbers has the longest amount of hailstone iterations. 

	Test Cases:

	1) 97 produces the longest hailstone sequence between 1 and 100 inclusive.  
	Its length is 119. 

	2) 871 produces the longest hailstone sequence between 666 and 999 inclusive. 
	Its length is 179. 

	3) 6171 produces the longest hailstone sequence between 1000 and 10000 
	inclusive. Its length is 262. 
*/

#include <iostream>
using namespace std;

// What does this do? (NOT HOW) 
// This is the function that produces the HailStone sequence.  The sequence 
// takes the inputted number and inserted in a loop will always return 1 after
// the sequence is finished.  No one has been able to prove this sequence however
// it was verified by computers for a large range of numbers.
int hailStone (int value){

	if (value % 2 == 0) // is even.
	{
		value = (value / 2); 
		//cout<<"DEBUG: " << value << endl;
	}
	else 					  // is odd.
	{
		value = (3 * value + 1);
		//cout<<"DEBUG: " << value << endl;
	}

return value;
}

// What does this do? (NOT HOW) 
// This is the function that calculates the length of each hailstone sequence.
// The function will recursively call itself until the hailstone sequence is 
// complete thus returning the length of the sequence.
int lengthHail(int num){

int count = 1; 

	while (num != 1)
	{
		num = hailStone(num); // recursive call until num reaches 1.
		count++;
	} 

return count;
}

// What does this do? (NOT HOW)
// This is the main, it's purpose to take users input and run the calculations
// thus returning the what number produces the longest HailStone sequence between
//  the two user inputted numers.
int main (){

int lowerLimit; // Hold the users minimum number. 
int upperLimit; // Holds the users maximum number.
int lowerLimitTemp; // Holds the users minumum number for final ouput purposes. 
int longestHail=0; // Holds the longest hailstone sequence length.
int hailStoneLength; // Holds the most current hailstone sequence length.
int hailStoneNum; // Holds the num in which produces the longest hailstone length.

cout<<"Please enter a lower limit. " << endl;
cin>>lowerLimit;
cout<<"Please enter an upper limit. " << endl;
cin>>upperLimit;

lowerLimitTemp = lowerLimit;

while (lowerLimit <= upperLimit) // Checks each number from min to max.
{

	hailStoneLength = lengthHail(lowerLimit); // Stores current length.

	if (longestHail < hailStoneLength) // Compares current length with longest.
	{
		longestHail = hailStoneLength; // Saves the length that reigns champion of being greatest.
		hailStoneNum = lowerLimit; // Saves the number that reigns champion of being the longest.
	}

lowerLimit++; 
}

cout<<hailStoneNum<< " produces the longest hailstone sequence between "
<< lowerLimitTemp << " and " << upperLimit << " inclusive.  Its length is "
<< longestHail<<"."<<endl;

//cout<<"DEBUG: Longest hailstone sequence is " << longestHail <<endl;
//cout<<"DEBUG: The number that produces the  Longest hailstone sequence is " << hailStoneNum <<endl;

} 

