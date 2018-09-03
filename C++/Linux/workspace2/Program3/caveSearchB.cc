/*
  Name: Christopher M West, Patrick Rawlings
  Class at ECU:3300-001
  Assignment Due Date: Thursday November, 5:00 P.M.
  Assignment Number: Program 3
  Professor: Dr. Ronnie Smith
  
  Description: The purpose of this program is to take user input in the 
  format of size of the multidimensional array and the letters 
  'T' - traversable and 'X' - not traversable and determine if it is possible
  to navigate through every 'T' starting at position (1,1) and ending back at
  position (1,1).  See examples in the comments at the end of the program for
  a sample input.
           
*/

#include <iostream>
//#include "string.h"
using namespace std;
char caveInfo[50][50]; // Only global variable allowed.  Is used to set max
                       // size of the muli-array.
struct MyPnt{
	int xAxis;
	int yAxis;

	MyPnt(){
		xAxis=yAxis=1;
	}
};

bool solves(int curX, int curY,int maxMoves, int curMoveCnt, int myDir [],int finalCoords[2][2401])
{
	bool finished = false;
	bool lastMove = false;
	bool mveNorth = true;
	bool mveSouth = true;
	bool mveEast = true;
	bool mveWest = true;
	
	//int count=0;
	int newX=curX;
	int newY=curY;
	
	
		
	if(caveInfo[curY][curX+1]=='T' && mveEast == true) //checks for east move
	{	
		
		//TorF=true;
		curMoveCnt++;
		newX++;
		myDir[curMoveCnt]=69;
		//myDir2[curMoveCnt]=69;
		finalCoords[0][curMoveCnt]=curX;
		finalCoords[1][curMoveCnt]=curY;
		caveInfo[curY][curX] = 'V';
		mveNorth = true;
		mveSouth = true;
	 	mveEast = true;
		mveWest = true;
		//cout<< "Moving East!" << endl;
		solves(newX, newY,maxMoves,curMoveCnt,myDir,finalCoords);
		
	}
	else if (caveInfo[curY+1][curX]=='T'&& mveNorth == true) //checks for north move
	{
		//TorF=true;
		curMoveCnt++;;
		newY++;
		myDir[curMoveCnt]=78;
		//myDir2[curMoveCnt]=78;
		finalCoords[0][curMoveCnt]=curX;
		finalCoords[1][curMoveCnt]=curY;
		caveInfo[curY][curX] = 'V';
		mveNorth = true;
		mveSouth = true;
	 	mveEast = true;
		mveWest = true;
		//cout<< "Moving North!" << endl;
		solves(newX, newY,maxMoves,curMoveCnt,myDir,finalCoords);
	}	
	else if (caveInfo[curY][curX-1]=='T' && mveWest == true) //checks for west move
	{
		//TorF=true;
		curMoveCnt++;
		newX--;
		myDir[curMoveCnt]=87;
		//myDir2[curMoveCnt]=87;
		finalCoords[0][curMoveCnt]=curX;
		finalCoords[1][curMoveCnt]=curY;
		caveInfo[curY][curX] = 'V';	
		mveNorth = true;
		mveSouth = true;
	 	mveEast = true;
		mveWest = true;
		//cout<< "Moving West!" << endl;		
		solves(newX, newY,maxMoves,curMoveCnt,myDir,finalCoords);
			
	}	
	else if (caveInfo[curY-1][curX]=='T' && mveSouth == true) //checks for south move
	{
		//TorF=true;
		curMoveCnt++;
		newY--;
		myDir[curMoveCnt]=83;
		//myDir2[curMoveCnt]=83;
		finalCoords[0][curMoveCnt]=curX;
		finalCoords[1][curMoveCnt]=curY;
		caveInfo[curY][curX] = 'V';
		mveNorth = true;
		mveSouth = true;
	 	mveEast = true;
		mveWest = true;
		//cout<< "Moving South!" << endl;		
		solves(newX, newY,maxMoves,curMoveCnt,myDir,finalCoords);	
	}
	
	cout<<"Debug: I hit a dead end in the search. Here is where I am located:" << curX<<","<<curY << endl;
	cout<<"curMoveCnt is =" << curMoveCnt << endl;
	
	if (caveInfo[curY-1][curX]!='T' && caveInfo[curY][curX-1]!='T' && caveInfo[curY+1][curX]!='T' && caveInfo[curY][curX+1]!='T')
	{
	finished = true;
	}
	else
	{
	cout<<"I SEE A DIFFERENT PATH I HAVEN'T TRIED YET!!!!"<< endl;
		curMoveCnt++;
		
		solves(newX, newY,maxMoves,curMoveCnt,myDir,finalCoords);
		
	
	}



	 if(curMoveCnt==maxMoves && finished == true) // Found the correct path!
	{
		cout << "YOU ARE MOTHERFUCKING DONE!!!!" << endl;		
		lastMove=true;	
	}

		while(curMoveCnt != maxMoves && finished == true ) // Start back tracking here.
		{
			cout<< "DEBUG: myDir[curMoveCnt] =" << myDir[curMoveCnt]<< endl;
			cout<< "DEBUG:START BACKTRACKING." << endl;
			
		
		
			if(myDir[curMoveCnt] == 69) // Came from East.  Move back West
			{ 
			caveInfo[curY][curX] = 'A';
			//caveInfo[curY][curX-1];	
			//curMoveCnt--;
			//newX--;
			mveEast = false;
			finished = false;
			cout<< "Moved back west"<<endl;
			cout<< "DEBUG:END BACKTRACKING"<<endl<< endl;
			}

			else if (myDir[curMoveCnt] == 78) // Came from North.  Move back South.
			{ 
			caveInfo[curY][curX] = 'A';	
			//caveInfo[curY-1][curX];
			//curMoveCnt--;
			//newY--;
			
			mveNorth = false;
			finished = false;
			cout<< "Moved back south"<<endl;
			cout<< "DEBUG:END BACKTRACKING"<<endl << endl;
			}	
			else if (myDir[curMoveCnt] == 87) // Came from West.  Move back East.
			{ 
			caveInfo[curY][curX] = 'A';
			//caveInfo[curY][curX+1];
			//curMoveCnt--;
			//newX++;
			
			mveWest = false;
			finished = false;
			cout<< "Moved back east"<<endl;
			cout<< "DEBUG:END BACKTRACKING"<<endl;
			}
			else if (myDir[curMoveCnt] == 83) // Came from South.  Move back North.
			{ 
			caveInfo[curY][curX] = 'A';	
			//caveInfo[curY+1][curX];
			//curMoveCnt--;
			//newY++;
			
			mveSouth = false;
			finished = false;
			cout<< "Moved back north"<<endl;
			cout<< "DEBUG:END BACKTRACKING"<<endl << endl;
			} 
		}
	


	
	return lastMove;
}


// This function is used to count the number of T's in the inputted cave.
int numCntTChar(int Xcnt,int Ycnt)
{
	int TcharCnt=0;
	for(int xIndex=1;xIndex<=Xcnt+1;xIndex++) // runs through the rows.
	{
		for(int yIndex=1;yIndex<=Ycnt;yIndex++) // run through the columns.
		{
			if(caveInfo[xIndex][yIndex]=='T') 

				TcharCnt++; 
		}
	}
	
	return TcharCnt;
}	


int main (){
    // Variables for main starts here.
	int finalCoords[2][2401];
	int moves[2401];
	//char crap[11];
	int rowNum=1; // Instructions specify to start at 1.
	int maxX=0; // Size of the rows.
	int maxY=0; // Size of the columns
	const int STARTPOINT=1; 
	//const int SIZE=50; // Max size of the muli-dem array.
	int tmpNum=0; 
	int tmpNum2=0;
	int startCnt=0;
	int numOfMoves;
	
	
	
	MyPnt start;
	
	// Variables for main ends here
	moves[0]='E';
	cin >> maxX>>maxY;	
	cout <<maxX<<" "<<maxY<<endl; 
	
	// prefill array with char 'B'
	for(int i=0;i<maxY+2;i++)
		{
			for(int index=0;index<maxX+3;index++)
			{
				caveInfo[i][index]='B';
			}
		}
	
	rowNum=maxY+1;
 		
	//get data from user or cin stream
	while(!cin.eof())
		{
	

			cin.getline(&caveInfo[rowNum][STARTPOINT],(maxX+1));
			rowNum--;
			
		}
	
	tmpNum=maxY+1;//it was just need this way


	// Used to display the rows and columns in the required format.
	for (int i=0; i<=maxY+1; i++,cout<<endl,tmpNum2++)
		{ 
			cout<<"row "<<tmpNum-tmpNum2<< ":"; 
			for(int index=0;index<=maxX+3;index++)
				{
					cout<<caveInfo[tmpNum-tmpNum2][index];
				}
		}


	// If the number of T's in the cave are odd, the cave is automatically
	// untraversable.
	numOfMoves=numCntTChar(maxX,maxY);
	if(numOfMoves%2!=0) // checks for odd number of T's.
	{
		cout<<"Cave untraversable"<<endl;
		return 0;
	}
	
	cout<<numOfMoves<<endl;

	if (!(caveInfo[start.xAxis][start.yAxis]=='T')|| !(caveInfo[start.xAxis][start.yAxis+1]=='T'))
	{
		cout<<"Cave untraversable"<<endl;
		return 0;
	}
	
	
	else solves(start.xAxis+1,start.yAxis ,numOfMoves, startCnt, moves, finalCoords);
    //printout grid 0,0 to 10,10
    //~ for(int i=0;i<=10;i++){for(int ii=0;ii<=10;ii++){cout<<caveInfo[i][ii];}cout<<endl;}
    cout<<"Start (1,1)"<<endl;
    for(int index2=1;index2<numOfMoves;index2++,cout<<")"<<endl)
    {
		
		switch(moves[index2]){
			case 'E':
				cout<<"East (";break;
			case 'N':
				cout<<"North (";break;
			case 'W':
				cout<<"West (";break;
			case 'S':
				cout<<"South (";break;
			}
		for(int index=0;index<2;index++)
		{
			cout<<finalCoords[index][index2];
			if(index==0)cout<<",";
			
		}
			
}
     cout<<"South (1,1)"<< endl;
 //~ cin.get();
 //~ return 0;
  
}


/*
                                  Computer Science 3300
                                            Program 3
DUE: Thursday November 4, 5:00 P.M.
Problem Description
You are still the programmer at the Extremely Creative Undertakings (ECU) travel agency.
Your manager has learned about a set of interesting caves that are represented by two
dimensional grids and wants you to write a computer program to analyze the caves and see if
there is a route through the cave that satisfies the manager‟s rules. Consider the following grid
representation of a 4 x 4 cave.
        4    T    T    T    T
        3    T    X    X    T
        2    T    T    T    T
        1    T    T    T    T
             1    2    3    4
Using a traditional (x,y) coordinate system, the entrance is always at the lower left square (1,1).
Squares labeled with the letter „T‟ represent traversable squares in the cave. Squares labeled
with „X‟ represent untraversable squares. The manager‟s rules for traversing a cave are as
follows.
    1.  Always begin in square (1,1).
    2.  Always move from square to square either horizontally or vertically, never diagonally.
    3.  Never visit a square more than once, except the square (1,1) when exiting the cave.
    4.  Squares marked X cannot be visited.
For the sample cave, a valid route through the cave would consist of the following moves
(reading left to right, top to bottom).
Start (1,1)     East (2,1)       North (2,2)    East (3,2)    South (3,1)     East (4,1)
North (4,2)     North (4,3)      North (4,4)    West (3,4)    West (2,4)      West (1,4)
South (1,3)     South (1,2)      South (1,1)
Your job is to write a program that can read in the specification of a cave, and output a sequence
of moves that takes someone through every traversable square of the cave while obeying the
stated rules. If a cave is not traversable, you must output the message “Cave untraversable.” An
example of an untraversable cave is the following.
        4    T    T    T    T
        3    X    X    X    T
        2    T    T    T    T
        1    T    T    T    T
             1    2    3    4
Input/Output Requirements
   1. Input is read from standard input. The first line of the input are two numbers maxX and
      maxY that represent the maximum X and Y coordinates in the cave. The remaining input
      lines, maxY lines altogether, each consist of maxX characters that specify whether or not
      each square in that row is traversable, with the letter „T‟ denoting traversable, and the
      letter „X‟ denoting untraversable. A sample cave and its input format are shown below.
      5    T     T    T    T
      4    T     X    X    T
      3    T     X    T    T
      2    T     T    T    T
      1    T     T    T    T
           1     2    3    4
      45
      TTTT
      TXXT
      TXTT
      TTTT
      TTTT
   2. You should store the information about the cave in a two-dimensional array. Suppose we
      call this array caveInfo. Then caveInfo[i][j] should represent the traversability
      information for coordinate position (j,i). That is, the row index corresponds to the y-
      coordinate in the grid, and the column index corresponds to the x-coordinate in the grid.
      Thus, for the sample cave, caveInfo[2][3], caveInfo[2][4], and caveInfo[3,4] should
      have the value „X‟, and all other values for caveInfo[i][j], with 1 ≤ i ≤ 5 and 1 ≤ j ≤ 4
      should have the value „T‟.
   3. A technical issue with input of characters is how to read in an entire line at once and skip
      to the next line. For reading each row of cave information, use the following statement
      (note the similarity to Java syntax for invoking a method of an object---cin is actually an
      object used for input).
      cin.getline(&caveInfo[rowNum][1],maxX+1);
      where caveInfo is the two dimensional array, and rowNum represents the current row
      being input. Note that the current row number will decrease as you read the input. The
      two arguments of the getline function are (1) a pointer to the base address where the input
      line is stored (note that we want to begin storing the information in column 1 rather than
      column 0 of the row); and (2) the maximum number of characters to be stored.
   4. Another technical issue with the input of characters and the use of getline() is that after
      reading the first two numbers in your input, a call to getline() is needed to skip over the
      rest of the first input line (probably just the newline character). Thus, before you start
      your loop that reads in the actual cave information, you will need a statement of the form.
         cin.getline(caveInfo[0],1);
         to throw away the rest of the first line. The 0th row of caveInfo can be used as a
         “dummy” buffer that is not needed otherwise at this point.
Algorithmic Requirements
This problem requires an algorithm known as backtracking search. The idea is that we
systematically explore the possible solution space (in this case a sequence of moves), but when
during this systematic process we reach a dead end, we must backtrack and try another
alternative. For example, in this program, you should systematically search for moves in the
following order: East, North, West, and South. Consider again our first sample cave.
         4    T    T    T    T
         3    T    X    X    T
         2    T    T    T    T
         1    T    T    T    T
              1    2    3    4
If you apply this systematic method of search in looking for a route through the cave, you will
move through the cave in the following sequence.
(1,1), (2,1), (3,1), (4,1), (4,2), (4,3), (4,4), (3,4), (2,4), (1,4), (1,3), (1,2), (2,2), (3,2)
but when you reach (3,2), you will have no legal moves as East, West, and South would take you
to squares already visited, and North is an untraversable square. So in a backtracking search,
you would have to reset your current position to be the previous position (2,2), and then try
moves from that point other than the one already tried (the East move to (3,2)). Unfortunately,
the other choices: North, West, and South, again lead you to dead ends and so you backtrack
once again to (1,2), where again you encounter dead ends (the South move to the Entrace/Exit
(1,1) would not be allowed at this point as you would not have yet visited (2,2) and (2,3), since
after backtracking, you no longer have visited those squares). In fact, backtracking search will
have to back up all the way to (2,1) and try the alternative North move, before eventually finding
a solution! So while backtracking search isn‟t very smart, it is systematic, and when properly
implemented, will find a solution as long as it has enough computing time to do so!
In order to properly implement a backtracking search, you must maintain an accurate state of the
computation as you try each move. Details about this set of information are described next.
Maintaining the state of the computation
At any given moment, the following represents the state of the computation that must be
maintained and used to solve this problem.
         The current position.
         The set of squares already visited.
         The sequence of moves already made.
         The sequence of moves already tried at the current position.
        The traversability information about the cave squares.
Every time the computation selects a new move to try, this state information must be updated
correctly. Every time the computation backtracks to a previous state, the state information must
be reverted back to its previous values. We will discuss how to do this in discussing the
backtracking search algorithm.
Backtracking search algorithm
The heart of the algorithm is based on the following idea. Given the current state of the
computation, is there a sequence of moves starting from the current position that enables a
complete legal traversal of the cave? The necessary algorithmic steps to carry out this idea are
the following.
    1. Does the current move cause a complete, legal traversal of the cave? If so, return
        success.
    2. Otherwise, is the current move legal (but does not complete the traversal)? If so, add to
        the sequence of moves made, and mark the current position as “visited”. Then
        systematically check to see if there is a sequence of moves starting from the new current
        position that enables a complete legal traversal of the cave. Try the moves in the order
        East, North, West, and South, and return success if any of these moves lead to a complete
        legal traversal. You do not have to try all the moves if an earlier one leads to success.
    3. If the current move is not legal, or if the move was legal, but no successful complete legal
        traversal was found by trying subsequent moves, then backtrack and return failure.
    4. Backtracking is achieved by restoring the state of the computation to its values prior to
        beginning the execution of step 1.
You must implement this algorithm using a function
solves(curX,curY,moveDir,moves,moveNum,totMoves)
where curX is the current x-coordinate for the proposed next move, curY is the current y-
coordinate for the proposed next move, moveDir is a character that denotes the current move
direction (from the set {„E‟,‟N‟,‟W‟,‟S‟} for East, North, West, and South), moves is an array
specifying the sequence of moves already made, moveNum is the number of the current move,
and totMoves is the total number of moves that will be necessary to make a complete legal
traversal of the cave. The final element of the computational state, the two-dimensional array
caveInfo that maintains information on the traversability of the cave squares, will be
implemented as a global variable. How to do that will be discussed in the Technical Issues
section. As an example of what this state information might look like, consider again the
original cave, and the state of the computation after moving into (3,1), and solves is being called
with the proposed move into (4,1). Here should be the values of the parameters:
curX = 4, curY = 1, moveDir = „E‟, moves[1] = moves[2] = ‘E’ (representing the moves from
(1,1) to (2,1), and (2,1) to (3,1)); moveNum = 3 (we are now considering making the third move),
and totMoves = 14 (in the case of this cave, the total number of moves required for a complete
legal traversal will be 14). While the initial values of caveInfo are set by the input, some of the
values may be modified as the computation proceeds. This will also be discussed below.
Technical Issues
       To declare caveInfo as a global variable, place the following declaration at the top of your
       program, outside of any function, and just after the using namespace std; statement.
       char caveInfo[50][50];
       You may assume this is big enough to handle any cave. As a global variable, it can be
       referenced in any function you may write without passing it as a parameter. This is the
       only global variable allowed.
       The simplest way to keep track of which squares have already been visited as solves is
       trying to find a solution is to reset the value for the corresponding caveInfo square to a
       different letter. Use „V‟ to represent the concept that a square has been visited. Be sure
       to reset it to „T‟ if you backtrack!
       The formula for determining the total number of necessary moves is simply the number
       of traversable squares in the cave. Thus, after reading in the cave information, a function
       will need to be written that counts the number of traversable squares. A slightly more
       efficient solution would be to count the number of non-traversable squares and use
       arithmetic to compute the number of traversable squares. This second solution, done
       correctly, will earn more credit.
       A sticky technical issue is checking when moves are disallowed because it takes you
       outside the boundaries of the cave. For our sample cave, when the current position is the
       upper right corner, square (4,4), moving East or North is disallowed because it‟s out of
       bounds. Having to check for “out-of-bounds” math can be done, but is tedious and
       sometimes error prone. A more elegant solution, which I call the Gordon maneuver, after
       my former ECU colleague, Steve Gordon, who introduced me to the idea, is to initialize
       rows 0 and MaxY+1, and columns 0 and MaxX+1 to a “non-T” value so that all that is
       necessary to determine if a square is a legal place to move to is to see whether it‟s value
       is a „T‟. Use the letter „B‟ for this initialization (to denote the border of the cave). This
       initialization can be done while reading the cave information or afterwards.
       The function solves is a self-referential or recursive function (i.e. a function whose
       definition refers to itself). A careful review of the backtracking search algorithm shows
       that in step 2, the process of systematically checking the possible moves from the current
       position is where you need to specify the recursive calls.
       The function main() should ensure that the following steps are carried out either through
       direct instructions or function calls as appropriate.
            1. Initialize maxX, maxY, and caveInfo to the input values
            2. Set the caveInfo border.
            3. Determine the total number of required moves.
            4. Initialize the current state of the computation to reflect the start conditions of the
                problem: starting in (1,1) which should be marked as visited, with no moves yet
                made.
            5. Invoke the solves function to see if either an East move or North move from the
                start position will lead to a solution (obviously, we already know West and South
                are impossible from the lower left corner).
                     if (solves(using East move) || solves(using North move)) then output moves
                     else output “Cave untraversable”
            6. Produce the correct output depending on the outcome of step 5.
      Besides main(), your program must contain the following functions as a minimum.
          1. The solves(...) function. What type of value should it return to represent success
              or failure?
          2. A function that counts traversable or untraversable squares as appropriate.
          3. A function that outputs the sequence of moves of a complete, legal traversal. the
              format of the output should be one move per line. For example, the first few lines
              of output for our sample cave would be:
              Start (1,1)
              East (2,1)
              North (2,2)
              The final line should be
              South (1,1)
      You may define additional helper functions as desired. A particularly useful helper
      function might be a debugging function that displays the state of the cave at a given point
      during the computation. That way you can see if you are properly marking squares as
      visited and have set the border correctly.
      This program requires no prompts for input. As with program 2, you can use I/O
      redirection to avoid excessive typing.
      While this program manipulates sequences of characters, it is not processing strings in the
      sense we have discussed in class. That is, there will be no need to maintain a null
      character („\0‟) as part of the representation of the traversability information.
Program Deadlines and Submission Information
      The deadline for final submission of the completed assignment is 5:00 P.M. on Thursday
      November 4.
      Use the <assignment_number> p3 for the submission.
      Use the name caveSearch.cc for your program file.
      Follow the submission guidelines in the Programming Standards handout.

 */
