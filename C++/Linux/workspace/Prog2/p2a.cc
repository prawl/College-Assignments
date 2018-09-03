/*
  Name:Patrick Rawlings
  Class at ECU:3300-001
  Assignment Due Date: 3/1/11
  Assignment Number: Program 2
  Professor: Dr. Ronnie Smith
  
  Description: The longest up sequence takes two user inputted numbers (one 
  to fill array 1, and the other fill array 2) and uses a third array 
  (reference array) to sort and find the upsequence of the data.  To achieve
  the longest up sequence the program will look through the given array and 
  pull out the numbers in sequential order, skipping the numbers who are not
  included in the up sequence and then starting a new up sequence with those
  skipped numbers.  The program then uses the longest up sequence in 
  reference to the (reference array) to display the relation to second 
  original array.  See end of program for examples.         
*/

#include <iostream>
using namespace std;

int main (){

 int const SIZE=101;// This is the max size of the input arrays.  
 int cost[SIZE]={0};/* Array used to hold the data for seqFinals.  
							It Is prefilled with zeros to ensure there is not
							some left over data in the memory location that 
							this program is allocated and only test value 
							we want to test and not some leftover data*/

 int distance[SIZE]={0};/* Array used to hold the data for seqFinals.  
							It Is prefilled with zeros to ensure there is not
							some left over data in the memory location that 
							this program is allocated and only test value 
							we want to test and not some leftover data*/

 int reference[SIZE]={0};/* Array used to hold the data for seqFinals.  
							It Is prefilled with zeros to ensure there is not
							some left over data in the memory location that 
							this program is allocated and only test value 
							we want to test and not some leftover data*/

 int seqFinals[SIZE]={0};/* Array used to hold the data for seqFinals.  
							It Is prefilled with zeros to ensure there is not
							some left over data in the memory location that 
							this program is allocated and only test value 
							we want to test and not some leftover data*/

 int tmpNum=1;/* Users temp array size using the EOF command.  Starts at 1 
					because we do not use position 0.also becuase we were 
					instructed to only start the use of the arrays a position 
					1 of the array and not position 0. that is what the boss 
					wanted*/
 int fusCnt=1;
 int myArraySize=0;/* The actual size of the array dictated by the user or 
						file input return line entries capped by EoF or 
						Ctrl-D keystroke.*/ 
   
    // Variables for main ends here

	// This loop is needed to make sure the reference array is filled with 
	// integers so they can be sorted. i.e 0 thru 100
	for(int i=0; i<SIZE;i++)
		{		
		reference[i]=i;
		}
    
    //begin user input

    /*  This is the end of file command.  It is needed so that if the users 
		wants to end input before the max size of the arrays the command 
		"ctrl + d" will use the inputted size.
		As long as there is not a EOF signal or Ctrl-D keystroke file the 
		two arrays with data being input by cin stream. the iterations 
		count is stored in tmpNum.
	*/
    while(!cin.eof()){
        cin>>cost[tmpNum]; // fill array number 1.
        cin>>distance[tmpNum]; // fill array number 2.
        tmpNum++;
        }


}























/**************************************************************************/
/*  PROGRAM ASSIGNMENT

*/

