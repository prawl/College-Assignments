/* 
//--------------------------------------
//Patrick Rawlings
//CSCI 3300 
//Program 1 
//Fall 2010
//
//Purpose of Program: The purpose of the program is to take two inputs from the user "Lower" and "Upper"
//and run them through the hailstone sequence until it finds the number between "Lower" and "Upper" with 
// the largest hailstone sequence.
//
// Test Case 1:
//
// Lower Limit: 5
// Upper Limit: 10
// 18 produces the longest hailstone sequence between 7 and 20 inclusive.
// It's length is 21.
//
//Test Case 2:
//
// Lower Limit: 21
// Upper Limit: 23
// 22 produces the longest hailstone sequence between 21 and 23 inclusive.
// It's length is 16
//
//Test Case 3:
//
// Lower Limit: 15
// Upper Limit: 100
// 97 produces the longest hailstone sequence between 15 and 100 inclusive.
// It's length is 119. 
//---------------------------------------
*/

#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

// Determines the next number in the hailstone sequence. It takes in only 1 parameter to calculate the next 
// number in the hailstone sequence.
int hailstone (int n)
{

// Checks for an even number.
if(n % 2 == 0) 
{
n = (n/2);
}
// Checks for an odd number.	
else		
{
n = (3 * n +1);    
}

return n;
}
		

// Determines the length of the hailstone sequence.  This also takes in only 1 parameter but it returns the
// length of the current hailstone sequence.
int lengthhail (int n)
{
int count = 1;
int f;

// A loop to calculate the hailstone length for each number.
while (n != 1)
{
f = hailstone(n);
n = f;
count++;
}
return count;
}


// Main funtion of the program is used to take the users input "Upper" and "Lower" and run them through the
// funtions "lengthhail" and "hailstone" to produce the longest hailstone sequence between the two input integers.
int main ()
{

// Listed all the variables out vertically because it is easier to read.
int lowerLimit = 0;
int upperLimit = 0;
int hailStoneLength;
int largestHailStone;
int largestHailStoneNum;
int lowerLimitTemp, lowerLimitTemp2;
int finalLowerLimit;

// Get input from user.
cout << "Enter lower limit:";
cin >> lowerLimit;

cout << "Enter upper limit:";
cin >> upperLimit;

// "finalLowerLimit" was created to display the original value of "lowerlimit" in the final print statement
// because "lowerLimit" has it's value changed.
finalLowerLimit = lowerLimit;

// Loop is used to calculate the hailstone sequence for each digit between "lowerLimit" and "upperLimit" 
while (lowerLimit <= upperLimit)
{

// Temp variables needed to complete the second while loop.
lowerLimitTemp = lowerLimit;
lowerLimitTemp2 = lowerLimit;

hailStoneLength = lengthhail(lowerLimit);


	// If statement used to store the number with the largest hailstone sequence to the variable 	
	// "largestHailStoneNum."
	if(hailStoneLength > largestHailStone)
	{
	largestHailStone = hailStoneLength;
	largestHailStoneNum = lowerLimit;
	}

		// Loop is used to take the current number and calculate the next hailstone sequence digit.
		while (lowerLimitTemp != 1)
		{

		lowerLimitTemp = hailstone(lowerLimitTemp2);

		lowerLimitTemp2 = lowerLimitTemp;

		}
		lowerLimit++;
		}

cout << largestHailStoneNum << " produces the longest hailstone sequence between " << finalLowerLimit << " and " << upperLimit << " inclusive. \n"  << " It's length is " << largestHailStone << ".\n";

}








