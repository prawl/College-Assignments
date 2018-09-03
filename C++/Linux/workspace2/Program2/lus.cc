/*
  Name: Christopher M West, Patrick Rawlings
  Class at ECU:3300-001
  Assignment Due Date: Thursday October 14, 5:00 P.M.
  Assignment Number: Program 2a
  Professor: Dr. Ronnie Smith
  
  Description: The longest up sequence takes two user inputted numbers (one to fill array 1, and the other
   fill array 2) and uses a third array (reference array) to sort and find the upsequence of the data.  To 
   achieve the longest up sequence the program will look through the given array and pull out the numbers in 
   sequential order, skipping the numbers who are not included in the up sequence and then starting a new up 
   sequence with those skipped numbers.  The program then uses the longest up sequence in reference to the 
   (reference array) to display the relation to second original array.  See end of program for examples.           
*/

#include <iostream>
using namespace std;

/* 
   This is a function that literally swaps the two inputted data.  This is necessary because we will be
   sorting sets of data and this function helps us achieve this goal.  
*/

void swap (int& x,int& y)
		{
		int temp =x;
			
		x=y;
		y=temp;
		}

/*
   This is a function that sorts the users inputted data array into a seperate reference array.  This is necessary 
   because we want to preserve the users original input while at the same time sort the data.
*/

void seqSort(int tmpArray[], int tmpArrayRef[],int tmpNum)
	{
		// Loop deincrements everytime to prevent searching already sorted data.
		for(int x=1;x<tmpNum;tmpNum--){
			
			// The most efficient way to impliment loop for the swap function
  			// using the size of the array.
			for (int i=1;i<tmpNum;i++) 
			{
				// Necessary to compare the ith position and ith +1 position in order to call the
				// swap function.
				if (tmpArray[tmpArrayRef[i]]<tmpArray[tmpArrayRef[i+1]]) 
				{
					swap(tmpArrayRef[i],tmpArrayRef[i+1]);
				}
			}
		}
	}
/*
   This is a function that finds the next value in the up sequence recursively until the call returns true.  Based
   off this can can calculate the length of the longest up sequence.
*/


bool findNext(int tmpArray[], int tmpArrayRef[], int finals[], int arraySize, int index, int count, int &maxSize){
	int myValue = tmpArray[tmpArrayRef[index]];

	//cout << "I am index:"<<index << " value="<<myValue<<endl;
	
	bool foundChild = false;
	bool madeMax = false;
	int currentMax = maxSize;
	
	// Compares the numbers in an array sequentally until it finds a number that does not match the upsequence.
	for (int i=index + 1; i <= arraySize; i++){
		if (tmpArray[tmpArrayRef[i]] > myValue){
			foundChild = true;
			madeMax = findNext(tmpArray, tmpArrayRef, finals, arraySize, i, count + 1, maxSize);
			if (madeMax){
				finals[count] = tmpArrayRef[index];
			}
		}
	}

	// Compares the sizes of the largest up sequence to know which one will be the longest.
	if (!foundChild){
		if (count >= maxSize){
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
   This is a function that finds the up sequence and stores the longest up sequence into an array.
*/ 

void UpSeqFinder(int tmpArray[], int tmpArrayRef[], int uSFinals[], int tmpNum){
	int maxSize = 0;
	int currentMax = -1;
	for (int i=1; i<=tmpNum; i++){
		findNext(tmpArray, tmpArrayRef, uSFinals, tmpNum, i, 1, maxSize);
		if (maxSize > currentMax){
			uSFinals[1] = tmpArrayRef[i];
			currentMax = maxSize;
		}
	}
}

/* This is where the program starts and ultimately ends; making function calls 
 	as needed.*/
int main (){
    // Variables for main starts here
   	
 int const SIZE=101;// This is the max size of the input arrays.  
 int cost[SIZE]={0};// Array used to hold the data for cost.  Needs to start at 0 to compensate for the EOF cmd.
 int distance[SIZE]={0};// Array used to hold the data for distance.  Needs to start at 0 to compensate for the EOF cmd.
 int reference[SIZE]={0};// Array used to hold the data for reference.  Needs to start at 0 to compensate for the EOF cmd.
 int seqFinals[SIZE]={0};// Array used to hold the data for seqFinals.  Needs to start at 0 to compensate for the EOF cmd.
 int tmpNum=1;// Users temp array size using the EOF command.  Starts at 1 because we do not use position 0.
 int fusCnt=1;
 int myArraySize=0;// The actual size of the array stored from tmpNum. 
   
    // Variables for main ends here

	// This loop is needed to make sure the reference array is filled with integers so they can be sorted.
	for(int i=0; i<SIZE;i++)
		{		
		reference[i]=i;
		}
    
    //begin user input

    //  This is the end of file command.  It is needed so that if the users wants to end input before the max size of the      	   //  arrays the command "ctrl + d" will use the inputted size.
    while(!cin.eof()){
        cin>>cost[tmpNum]; // fill array number 1.
        cin>>distance[tmpNum]; // fill array number 2.
        tmpNum++;
        }
	
	//end user input

	//begin calculations with user provided input
    myArraySize=tmpNum-1;
	seqSort(distance,reference,myArraySize);
	UpSeqFinder(cost,reference,seqFinals,myArraySize);

	//end calculations with user provided input
/******************************************************************************/
	//begin output to screen
	
		
	tmpNum=1; // "tmpNum" needs to be set to 1 because the array starts at 1 and it needs to run to given size.
	
	cout<<"\nUnsort data as inputed with reference(ref) indicating the "<<
		"\nsorted order\n\n";
	while(tmpNum < myArraySize){
		cout<<"cost="<<cost[tmpNum]<<"  distance="<<distance[tmpNum]<<"  ref="<<
			reference[tmpNum]<<"\n";
		tmpNum++;
		}
	
	tmpNum=1; // "tmpNum" needs to be reset to 1 because we reuse it and the array starts at 1 and it needs to run to 			  //  given size.
	
	cout<<"\n\nHere is the list sorted by distance from longest distance to"<<
		"\nshortest distance in decsending order\n\n";
	while(tmpNum < myArraySize)
		{
		cout<<"cost="<<cost[reference[tmpNum]]<<"  distance="<<
				distance[reference[tmpNum]]<<"\n";
		tmpNum++;
		}

	tmpNum=1;// "tmpNum" needs to be reset to 1 because we reuse it and the array starts at 1 and it needs to run to
		 // given size.
	
	// This loop purpose is to end the display whe the integer equals zero.  Is is to prevent the output from diplaying
	// the unused positions everytime.
	while(seqFinals[fusCnt]!=0)
	{fusCnt++;}
	fusCnt--;
	cout<<"\n"<<"the max upSequence count is: "<<fusCnt<<endl;
	cout<<"\n\nHere is the list sorted by distance of longest upSequence of cost" <<endl;
	while(tmpNum <= fusCnt)
		{
		cout<<"cost="<<cost[seqFinals[tmpNum]]<<"  distance="<<
				distance[seqFinals[tmpNum]]<<" reference(ref)"<<seqFinals[tmpNum]<<"\n";
		tmpNum++;
		}
	//end output to screen
    
    return 0;
}
/******************************************************************************/
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

TEST CASE 2:

Unsort data as inputed with reference(ref) indicating the 
sorted order

cost=44  distance=35  ref=17
cost=673  distance=856  ref=2
cost=235  distance=856  ref=3
cost=27  distance=243  ref=16
cost=854  distance=346  ref=14
cost=887  distance=542  ref=12
cost=236  distance=75  ref=6
cost=86  distance=3  ref=5
cost=865  distance=42  ref=4
cost=90  distance=6  ref=18
cost=8  distance=112  ref=11
cost=235  distance=653  ref=13
cost=905  distance=95  ref=15
cost=186  distance=674  ref=7
cost=234  distance=87  ref=19
cost=543  distance=787  ref=9
cost=4  distance=863  ref=1
cost=23  distance=134  ref=20
cost=666  distance=54  ref=10
cost=32  distance=7  ref=8


Here is the list sorted by distance from longest distance to
shortest distance in decsending order

cost=4  distance=863
cost=673  distance=856
cost=235  distance=856
cost=543  distance=787
cost=186  distance=674
cost=235  distance=653
cost=887  distance=542
cost=854  distance=346
cost=27  distance=243
cost=23  distance=134
cost=8  distance=112
cost=905  distance=95
cost=234  distance=87
cost=236  distance=75
cost=666  distance=54
cost=865  distance=42
cost=44  distance=35
cost=32  distance=7
cost=90  distance=6
cost=86  distance=3

the max upSequence count is: 6


Here is the list sorted by distance of longest upSequence of cost
cost=4  distance=863 reference(ref)17
cost=673  distance=856 reference(ref)2
cost=235  distance=653 reference(ref)12
cost=236  distance=75 reference(ref)7
cost=666  distance=54 reference(ref)19
cost=865  distance=42 reference(ref)9


Computer Science 3300 
Program 2 
DUE: Thursday October 14, 5:00 P.M. 
Problem Description 
You are the programmer at the Extremely Creative Undertakings (ECU) travel agency. 
You frequently have to develop customized software to assist with travel planning 
based on the latest unusual idea from your manager. The latest idea is the "Drive 
early/pay late" travel package. 
A customer specifies a set of (cost,distance) pairs that represent various travel 
destinations (the names are irrelevant). The units are dollars for cost and miles 
for distance. An example set would be the following: 
608 130 
900 210 
50 200 
100 400 
110 300 
605 205 
800 140 
600 120 
200 190 
The "Drive early/pay late" package is a sequence of travel destinations where each 
subsequent destination is closer, but the cost increases. For example, the 9th item 
in the set (200,190) and the 7th item in the set (800,140) would represent a valid 
travel itinerary because the distance decreases (from 190 to 140), while the cost 
increases (from 200 to 800). Another valid itinerary would be the 5th item (110,300), 
followed by the 2nd item (900,210). 
Your manager has asked you to write a program that takes a set of these pairs and 
produces a maximal length itinerary for the "Drive early/pay late" package since 
the amount of money ECU makes is a function of the number of travel destinations a 
customer visits. For the dataset listed, the maximal length itinerary is four 
destinations (items 4, 5, 9, and 7, in that order). Alternative length four 
itineraries include items 4, 5, 9, 1, and 4, 5, 9, and 8. There are at least two others. 
Input/Output Requirements 
1. Input is read from standard input, one pair of numbers describing a travel 
destination in the order (cost,distance) per line as shown above. We will denote 
the numbers on the ith input data line as C[i] and D[i]. Each cost and distance value 
will be unique. That is, if i ? j, then C[i] ? C[j] and D[i] ? D[j]. End-of-file 
terminates the input. 
2. The first output line should contain an integer n, the length of the maximal 
length itinerary. The remaining n lines should each contain a single positive integer 

representing a travel destination. If the chosen sequence of travel destinations 
is a[1], a[2],  , a[m], m ? n, then it must be the case that C[a[1]] < C[a[2]] 
<  < C[a[m]] and D[a[1]] > D[a[2]] >  > D[a[m]]. 

Thus, for the first specified maximal itinerary given above (where a[1] = 4, 
a[2] = 5, a[3] = 9, and a[4] = 7), the output would be 
4 
4 
5 
9 
7 
Any of the correct answers for the sample input case would have been acceptable. 
In general, any correct answer may be produced as your output. 
Algorithmic Requirements 
This problem is a variation of the longest upsequence problem. The standard form of 
this problem is that we have an ordered sequence of numbers S[1], S[2],  , S[k] for 
some integer k > 0, and what we are trying to find is a subsequence of the S[i], 
where S[x[1]] < S[x[2]] <  < S[x[m]], for some integer m ? k, and x[1] < x[2] 
<  < x[k] . As an example, suppose our sequence S is the following: 
100 110 900 605 50 200 800 608 600 
Then a valid upsequence would be S[5] (50) and S[8] (608), but the following would 
not be a valid upsequence: S[2], S[4], and S[9], because the condition S[4] < S[9] 
is false (i.e. S[4] > S[9]). The longest upsequence is of length 4. One such upsequence 
is S[1], S[2], S[6] and S[7]. Substituting S[8] or S[9] for S[7] also yields an 
upsequence of length 4. 
The complication for our problem is that we have pairs of values rather than just a 
single sequence of numbers. Since in our problem, the cost value is the one that is 
increasing for each travel choice in the itinerary, we can apply the longest upsequence 
algorithm to the cost numbers, but for which ordering of those numbers? The answer is 
to sort the pairs based on decreasing distance, and then apply the longest upsequence 
algorithm. For the original given input, if we sort by decreasing distance, we get the 
following set of pairs. The number in parentheses denotes its original ordering in the 
initial input. 
100 400 (4) 
110 300 (5) 
900 210 (2) 
605 205 (6) 
50 200 (3) 
200 190 (9) 
800 140 (7) 
608 130 (1) 
600 120 (8) 
If you carefully inspect this reordered input set, you will see that the choices for 
the itinerary correspond to a longest upsequence for the values in the first column. 
Details for the longest upsequence algorithm will be described later in this document. 
How to sort without moving data 
At this point, you may have realized a technical complication with the approach described 
above. If we sort our data by decreasing distance, how do we retain the information about 
the original location of the data in the input so that we can properly specify the required 
output? The answer is that we maintain a separate array of references to the original data. 
We call this array index. Initially index[i] = i, for 1?i?n where n is the total number of 
(cost,distance) pairs in the input. After we execute the sort algorithm, index[i] should be 
the subscript reference to the ith item in the sorted form of the array. Since we are sorting 
based on D[i] in our sample problem, this means that after sorting (into descending order), that 
D[index[1]] ? D[index[2]] ?  ? D[index[n]] 
Based on this sorted order, the cost element corresponding to D[index[i]] will be C[index[i]]. 
For sorting, a simple but inefficient algorithm that you may use is Selection sort. This algorithm 
is described on pages 285-286 of your text. Note that the algorithm in the text is for sorting 
into ascending order. Pseudocode for the selection sort into descending order is given below. 
Acronyms are FUS for FirstUnSorted and IOL for index of largest. 
sort(data[],n) // sorts data[i], 1 ? i ? n into descending order 
{ 
for (FUS = 1; FUS <= n-1; FUS++) 
set IOL = index of largest element in data[k], FUS ? k ? n 
"swap" data[IOL] and [data[FUS]] 
} 
Remember that in our case, we don't swap the actual data, but instead swap the values 
in index[FUS] and index[IOL], so you will need to add index[] to your parameter list 
(discussed more in the technical requirements). Any references to the actual data in the 
sort will be of the form data[index[??]] rather than data[??] where ?? simply refers to 
whatever the appropriate subscript value should be at that point. 
Longest upsequence algorithm 
This discussion assumes that our data is stored in an array data[i], 1 ? i ? n, and 
that we are directly indexing into this array. In determining the longest upsequence, 
it is not sufficient to keep track of the current longest upsequence and keep trying 
to add to that. For the sample sequence <17, 28, 21, 25, 18, 19, 11, 20, 26, 27>, if 
we start out just adding to the sequence beginning with the first number, we will add 
the second number, 28, and never get an upsequence of length > 2 even though there is a 
length 6 upsequence (17, 18, 19, 20, 26, 27,  corresponding to indices 1, 5, 6, 8, 9, 10 
in the data array). Solving this problem requires a famous technique called dynamic 
programming invented by Richard Bellman. This term refers to a general set of techniques 
for preserving solutions to subproblems that point the way, through appropriate combination, 
to the solution to the main problem. In this case, the subproblem is, "what is the optimal 
longest upsequence of length k", for 1 ? k ? m, where m represents the length of the longest 
upsequence found so far in examining the data. "Optimal" means that the largest value in the 
upsequence is as small as possible. For example, in the data set from above 
17, 28, 21, 25, 18, 19, 11, 20, 26, 27 
After looking at the first 5 numbers, the optimal length 1 upsequence is the number <17>; 
the optimal length 2 upsequence is <17,18>; and the optimal length 3 upsequence is <17,21,25>. 
If there was no more input at this point, the answer would be 3. But as it turns out, as more input 
is processed, we discover a better length 3 upsequence, <17,18,19> by extending the optimal 
length 2 upsequence at that point (<17,18>) and continue with discovering a length 4, 5, and 6 upsequence. 
Computing the longest upsequence requires a separate array seq where seq[i] denotes the 
index in our data array of the final value in the optimal longest upsequence of length 
i (again optimal means that the largest value in the upsequence is as small as possible). 
When we finish processing this input sequence, the values of seq would be the following. 
The number in parenthesis corresponds to the actual data value. 
seq[1] = 7 (11) seq[2] = 5 (18) seq[3] = 6 (19) 
seq[4] = 8 (20) seq[5] = 9 (26) seq[6] = 10 (27) 
and the length of the longest upsequence is 6. 
The algorithm for calculating longest upsequence requires inspecting each item data[i] 
in turn, from 1 ? i ? n, and determine which of the following two cases applies and carry 
out the required step. 
Case 1: Longest current upsequence is length k, and data[i] > kth item in the current 
upsequence of length k (i.e. data[seq[k]]). In this case, create an upsequence of length 
k+1. The last value in this sequence is data[i]. 
Case 2: For some upsequence of length m, m < k, data[i] is larger than data[seq[m]] 
(largest item in current optimal upsequence of length m), but smaller than data[seq[m+1]] 
(largest item in current optimal upsequence of length m+1). This means data[i] represents a 
new optimal largest value for upsequence of length m+1). Adjust seq[m+1] accordingly 
(i.e., i now represents the location of the largest value in the current optimal 
 upsequence of length m+1). 
If the problem that requires the longest upsequence algorithm requires not only the 
length of the longest upsequence, but also the values, then we need an addition array 
previous[]. The value previous[i], 1 ? i ? n, is an index into the data array for the 
previous value in a longest upsequence that includes data[i]. In case 1, previous[i] 
would be seq[k], where k had been the previous value for the length of the longest 
upsequence (which is now being changed to k+1). In case 2, previous[i] would be 
seq[m] as data[i] is now the optimal largest value for the m+1 length upsequence. 
In the case that m is 0 (i.e. data[i] is the smallest value seen so far in the dataset 
and is consequently the optimal largest value for the length 1 upsequence, set 
previous[i] to -1). When finished, if L is the length of the longest upsequence, then 
following the previous references starting at previous[seq[L]] specifies the longest 
upsequence items in reverse order. 
Again, remember that for this problem, you cannot directly reference the data array in 
executing this algorithm. The index array discussed under "How to sort without moving 
data" section must be used. 
Technical Issues 
You may assume there are no more than 100 (cost,distance) input values. 
The mathematical descriptions for this problem and the solution algorithm(s) all assume 
that the initial subscript of the data is 1. While C++ starts array indices with 0, I encourage you to develop your code relative to the mathematical specification, and skip using index 0 for your arrays. Be sure to declare your arrays large enough to do this correctly. 
Your program must be written by correctly specifying the following three functions. 
1. A function that implements the necessary sort of the distance array, specifying the sorted order through the index[] references. 
2. A function that implements the longest upsequence algorithm. It will use the cost array in conjunction with the index[] references. 
3. Your main() function that should read in the input data and initialize the necessary auxiliary arrays, then call the other two functions to do the necessary calculations and print the result. 
You may define additional helper functions as desired. 
This program requires no prompts for input. The cin statement discussed in class is actually a function that returns true when it's able to properly execute and false when it cannot. Thus, a statement of the form cin >> num1 >> num2 will try to read two numbers, storing the first in num1 and the second in num2, and if it is unable to do so because end-of-file has been reached, returns false. 
You can simulate end-of-file at the keyboard by hitting Ctrl-D (hold down Ctrl while hitting D). 
Alternatively, you can use I/O redirection if you get tired of typing in keyboard input. If your executable file is a.out, then the command a.out < input.dat will take its input from the file input.dat rather than the keyboard. You can create such files with an editor such as gedit. This can save you lots of typing as you test your program. 
Because of the complexity of this program and the novelty of the algorithms and array references, I strongly encourage you to develop the program as a sequence of smaller programs. Here are some suggested intermediate programs to write. 

1. A program that can read in a single sequence of numbers, terminated by EOF, sort the numbers, and print them out in their sorted order 
2. A program that can read in a single sequence of numbers, terminated by EOF, and determine the length of the longest upsequence and print out that number. 

3. Enhance the program in item 1 to sort based on references, preserving the original order of the data, and using an auxiliary index array to show what the sorted order would be. Output both the original data, and the sorted data (e.g. data[index[i]]). 
4. Enhance the program of item 2 to print not only the length of the longest upsequence, but also what items constitute that sequence, as well as their indices in the data array. 

Once you've completed those four intermediate programs, you should be able to combine what you know into a program to solve the entire problem. 

Program Deadlines and Submission Information 
For this program, 20% of your grade will be based on successful and on-time submission of the intermediate program #4 described above (the one that calculates and produces the length of a longest upsequence of numbers as well as their locations in the input). The deadline for this submission is the start of class Thursday October 7. 
The deadline for final submission of the completed assignment is 5:00 P.M. on Thursday October 14. 
Use the <assignment_number> p2a for the intermediate submission and the <assignment_number> p2b for the final submission. 
Follow the submission guidelines in the Programming Standards handout. 
Use the name lus.cc for the initial submission and travel.cc for the final submission. 

*/

