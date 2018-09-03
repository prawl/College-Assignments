/*
  Name:Patrick Rawlings
  Class:3300
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

/* 
   This is a function that literally swaps the two inputted data.  This is 
   necessary because we will be sorting sets of data and this function helps
   us achieve this goal. The variables used are Reference variable os that 
   manipulates the contents of the array positions passed to this function. 
*/

void swap (int& x,int& y)
	{
		int temp =x;
		
		x=y;
		y=temp;
	}

/*
   This is a function that sorts the users inputted data array into a 
   seperate reference array.  This is necessary because we want to preserve 
   the users original input while at the same time sort the data.
*/

void seqSort(int tmpArray[], int tmpArrayRef[],int tmpNum)
	{
		// Loop deincrements everytime to prevent searching already sorted 
		// data. The data is sorted in order of largest to smallest starting
		// . It subtracts the bottom item of each iteration from the next 
		// loop until the array is sorted.
		for(int x=1;x<tmpNum;tmpNum--)
		{
			
			//The most efficient way to impliment loop for the swap function
  			// using the size of the array.
			for (int i=1;i<tmpNum;i++) 
			{
				// Necessary to compare the ith position and ith +1 position 
				// in order to call the swap function.
				if (tmpArray[tmpArrayRef[i]]<tmpArray[tmpArrayRef[i+1]]) 
				{
					swap(tmpArrayRef[i],tmpArrayRef[i+1]);
				}
			}
		}
	}
/*
   This is a function that finds the next value in the up sequence 
   recursively until the call returns true.  Based off this can can 
   calculate the length of the longest up sequence.
*/


bool findNext(int tmpArray[], int tmpArrayRef[], int finals[], 
	int arraySize, int index, int count, int &maxSize)
	{
	
	int myValue = tmpArray[tmpArrayRef[index]];

	//cout << "I am index:"<<index << " value="<<myValue<<endl;
	
	bool foundChild = false;
	bool madeMax = false;
	int currentMax = maxSize;
	
	// Compares the numbers in an array sequentally until it finds a number 
	// that does not match the upsequence.
	for (int i=index + 1; i <= arraySize; i++)
		{
		if (tmpArray[tmpArrayRef[i]] > myValue)
			{
			foundChild = true;
			madeMax = findNext(tmpArray, tmpArrayRef, finals, arraySize, i, 
			count + 1, maxSize);
			if (madeMax)
				{
				finals[count] = tmpArrayRef[index];
				}
			}
		}

	// Compares the sizes of the largest up sequence to know which one will 
	// be the longest.
	if (!foundChild)
		{
		if (count >= maxSize)
			{
			maxSize = count;
			finals[count] = tmpArrayRef[index];
			//cout << "I set the max size of "<<maxSize<<" so far"<<endl;
			return true;
			}
		}

	//cout << "I am returning "<< (madeMax?"true":"false") << endl;
	return madeMax;
	}

/* 
   This is a function that finds the up sequence and stores the longest up 
   sequence into an array.
*/ 

void UpSeqFinder(int tmpArray[], int tmpArrayRef[], int uSFinals[], int 
	tmpNum)
	{
	int maxSize = 0;
	int currentMax = -1;
	for (int i=1; i<=tmpNum; i++)
		{
		findNext(tmpArray, tmpArrayRef, uSFinals, tmpNum, i, 1, maxSize);
		if (maxSize > currentMax)
			{
			uSFinals[1] = tmpArrayRef[i];
			currentMax = maxSize;
			}
		}
	}

/* 	This is where the program starts and ultimately ends; making function 
	calls as needed.
*/
int main (){
    // Variables for main starts here
   	
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
	
	//end user input

	//begin calculations with user provided input
    myArraySize=tmpNum-1;/*since the while increments one more time after 
							the EOF we must remove that count before we 
							can assign the value to our user input count 
							holder becuase we reuse tmpNum later in the 
							program.
						*/
	// all of the calculation and data manipulation is done by these 2 
	// function calls.
	seqSort(distance,reference,myArraySize);// this satisfies #1 & #3
	UpSeqFinder(cost,reference,seqFinals,myArraySize);// this satisfies 
													  // #2 & #4

	//end calculations with user provided input
/**************************************************************************/
	//begin output to screen
	
	//this output satisfies #1 with the third column	
	tmpNum=1; // "tmpNum" needs to be set to 1 because the array starts at 1 
			  // nd it needs to run to given size.
	
	
	/* This loop purpose is to end the display whe the integer equals zero. 
		Is is to prevent the output from diplaying the unused positions 
		everytime. 
	*/
	// this output satisfies #3 & #4(refer to output above to verify 
	// correctness)
	while(seqFinals[fusCnt]!=0)
	{fusCnt++;}
	fusCnt--;
	cout<<"\n"<<"the max upSequence count is: "<<fusCnt<<endl;
	cout<<
	"\n\nHere is the list sorted by distance of longest upSequence of cost" 
	<<endl;
	while(tmpNum <= fusCnt)
		{
		cout<<"cost="<<cost[seqFinals[tmpNum]]<<"  distance="<<
				distance[seqFinals[tmpNum]]<<" reference(ref)"
				<<seqFinals[tmpNum]<<"\n";
		tmpNum++;
		}
	//end output to screen
    
    return 0;
}
/**************************************************************************/
/* 
TEST CASE 1:

10 15
12 100
40 22
142 5
123 321

Unsort data as inputed with reference(ref) indicating the 
sorted order

cost=10  distance=15  ref=5
cost=12  distance=100  ref=2
cost=40  distance=22  ref=3
cost=142  distance=5  ref=1
cost=123  distance=321  ref=4


Here is the list sorted by distance from longest distance to
shortest distance in decsending order

cost=123  distance=321
cost=12  distance=100
cost=40  distance=22
cost=10  distance=15
cost=142  distance=5

the max upSequence count is: 3


Here is the list sorted by distance of longest upSequence of cost
cost=12  distance=100 reference(ref)2
cost=40  distance=22 reference(ref)3
cost=142  distance=5 reference(ref)4

Test Case 2:

608 130
900 210
50 200
100 400
110 300
605 205
800 140
600 120
200 190
1000 95

Unsort data as inputed with reference(ref) indicating the 
sorted order

cost=608  distance=130  ref=4
cost=900  distance=210  ref=5
cost=50  distance=200  ref=2
cost=100  distance=400  ref=6
cost=110  distance=300  ref=3
cost=605  distance=205  ref=9
cost=800  distance=140  ref=7
cost=600  distance=120  ref=1
cost=200  distance=190  ref=8


Here is the list sorted by distance from longest distance to
shortest distance in decsending order

cost=100  distance=400
cost=110  distance=300
cost=900  distance=210
cost=605  distance=205
cost=50  distance=200
cost=200  distance=190
cost=800  distance=140
cost=608  distance=130
cost=600  distance=120

the max upSequence count is: 5


Here is the list sorted by distance of longest upSequence of cost
cost=100  distance=400 reference(ref)4
cost=110  distance=300 reference(ref)5
cost=200  distance=190 reference(ref)9
cost=600  distance=120 reference(ref)8
cost=1000  distance=95 reference(ref)10

***************************************************************************
*/

