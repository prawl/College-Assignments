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
#include <stdlib.h>
using namespace std;
char caveInfo[50][50]; // Only global variable allowed.  Is used to set max size of the muli-array.

struct MyPnt
{
	int xAxis;
	int yAxis;
	
	MyPnt()
		{
			xAxis=yAxis=1;
		}
};

bool solves(int curY, int curX, int moveDir, int moves[], int moveNum, int totMoves)
{
	cout<<"Debug: (x,y)"<<"("<<curX<<","<<curY<<")"<<" moveNum: " << moveNum << " totMoves: " << totMoves<< endl;

	if((curY==2&&curX==1)&&(moveNum==totMoves))// Completely finished.
	{ 		
	cout<<"Debug: You have found the correct path!"<<endl;	
	return true;
	}
		else if(caveInfo[curY][curX]=='T') // Make sure current space is a T.
		{
		caveInfo[curY][curX]='V';
			cout<<"Debug: You are currently on a 'T'."<<endl;
			 // If current space is a T, replace it with a V.  This give the okay to move!
			moves[moveNum]=moveDir; 
			moveNum++;
		
			cout<<"Debug: Check for a valid move."<<endl;
				if(solves(curY, curX+1, 'E', moves, moveNum, totMoves)); //East Move
				//cout<<"Debug: Making East move!"<<endl; 
				else if(solves(curY+1, curX, 'N', moves, moveNum, totMoves)); //North Move
				//cout<<"Debug: Making North move!"<<endl;
				else if(solves(curY, curX-1, 'W', moves, moveNum, totMoves)); //West Move
				//cout<<"Debug: Making West move!"<<endl;
				else if (solves(curY-1, curX, 'S', moves, moveNum, totMoves)); //South Move
				//cout<<"Debug: Making South move!"<<endl;
					
		}	
	else if((moveNum != totMoves)/*&&(curY != 2 && curX != 1)*/){ 
	cout<<"Debug: OOPS! You ran into a dead end.  Must back up one space."<<endl;
	cout<<"Debug: (x,y)"<<"("<<curX<<","<<curY<<")"<<" moveNum: " << moveNum << " totMoves: " << totMoves<< endl;
	caveInfo[curY][curX]='T';
	moves[moveNum]=moveDir;
	moveNum--;
	return false;
	}
	
	


		
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

int main ()
{
	
// Variables for main starts here.
    	const int STARTPOINT=1;
	char moveDir;
	int totMoves;
	int moves[totMoves];
	int rowNum=1; // Instructions specify to start at 1.
	int maxX=0; // Size of the rows.
	int maxY=0; // Size of the columns
	int moveNum=1;
	int tmpNum=0;
	MyPnt start;  
	//int direction=69;
	//int startCnt=1;
// Variables for main ends here
	
	
	cin >> maxX>>maxY;	
	cout <<"Debug: (maxX,maxY) " <<"("<<maxX<<","<<maxY<<")"<<endl;
	// prefill array with char 'B'
	for(int i=0;i<maxY+2;i++)
		{
			for(int index=0;index<maxX;index++)
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
	totMoves=numCntTChar(maxX,maxY);
	cout<<endl<<"Debug: Max Number of Moves:"<<totMoves<<endl<<endl;
	 
	cout<<"Debug: First Call of the solves function."<<endl<<endl;
	if(solves(start.yAxis,start.xAxis,'E',moves, moveNum, totMoves) == false){
	cout<<"Failure"<<endl;
	}
	else
	{
	cout<<"Success"<<endl;
	}
	
	
/************************************************************************************************************************************* */
						// Final output statement
			
		//cout<<"Debug: (x,y) "<<"("<<start.xAxis<<","<<start.yAxis <<")"<< endl<<endl; 

		


/********************************************************************************************************************************** */		
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
