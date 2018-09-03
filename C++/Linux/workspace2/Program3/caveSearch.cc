/*
  Name: Patrick Rawlings
  Class at ECU:3300
  Assignment Due Date: 3/29/11
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
//#include <stdlib.h>
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
bool solves2(int curX, int curY,int myDir [],int direction, int before, int after,int newMveCnt, int curMoveCnt, int maxMoves,int finalCoords[2][2401]);
int backTrack(int curY, int curX,int curMoveCnt,int myDir [],int direction, int before, int after,int newMveCnt,int maxMoves,int finalCoords[2][2401])
{	//cout<<"Debug: BackTrack outside"<<endl<<endl;	

	if(curMoveCnt>1)
	{
		int tmpNum=0;	

		if (caveInfo[curY][curX+1]=='T') // east
		{
		//cout<<"OH MY GAWD I FOUND A NEW PATH!"<< endl;
		//set before and after point
		before = curMoveCnt+1;
		after = curMoveCnt-1;
		
		solves2(curX+1, curY, myDir, direction, before, after, newMveCnt++, curMoveCnt, maxMoves, finalCoords);
		}	
		 else if (caveInfo[curY+1][curX]=='T') // north
		{
		//cout<<"OH MY GAWD I FOUND A NEW PATH!"<< endl;
		before = curMoveCnt+1;
		after = curMoveCnt-1;
		solves2(curX, curY+1, myDir,direction,before, after, newMveCnt++, curMoveCnt, maxMoves, finalCoords);
		}
		 else if (caveInfo[curY][curX-1]=='T') // west
		{
		//cout<<"OH MY GAWD I FOUND A NEW PATH!"<< endl; 
		before = curMoveCnt+1;
		after = curMoveCnt-1;
		solves2(curX-1, curY, myDir,direction,before, after, newMveCnt++, curMoveCnt, maxMoves, finalCoords);
		}
		 else if (caveInfo[curY-1][curX]=='T') // south
		{
	   //	cout<<"OH MY GAWD I FOUND A NEW PATH!"<< endl;
		before = curMoveCnt+1;
		after = curMoveCnt-1;
		solves2(curX, curY-1, myDir,direction, before, after, newMveCnt++, curMoveCnt, maxMoves, finalCoords);
		}

		//,direction, before, after, newMveCnt++, maxMoves, finalCoords
		tmpNum=curMoveCnt-1;
		//cout<<"Debug:x,y "<<curX<<","<<curY<<" curMoveCnt: "<<curMoveCnt<<endl<<endl;
		//curY, curX,myDir,direction,before,after,newMveCnt,curMoveCnt,maxMoves,finalCoords	
		if(myDir[curMoveCnt] == 69)
		{
		backTrack(curY,--curX,--curMoveCnt,myDir,direction, before, after, newMveCnt++, maxMoves, finalCoords);//MOVE BACK WEST
		caveInfo[curY][curX] = 'A';	
		}		
		else if(myDir[curMoveCnt] == 78)
		{
			
		backTrack(--curY,curX,--curMoveCnt,myDir,direction, before, after, newMveCnt++, maxMoves, finalCoords);//MOVE BACK SOUTH
		caveInfo[curY][curX] = 'A';
		}
		else if(myDir[curMoveCnt] == 87)
		{		
		backTrack(curY,++curX,--curMoveCnt,myDir,direction, before, after, newMveCnt++, maxMoves, finalCoords);//MOVE BACK EAST
		caveInfo[curY][curX] = 'A';

		}
		else if(myDir[curMoveCnt] == 83)
		{
		backTrack(++curY,curX,--curMoveCnt,myDir,direction, before, after, newMveCnt++, maxMoves, finalCoords);//MOVE BACK NORTH
		caveInfo[curY][curX] = 'A';
		}		

	}return curMoveCnt;
}


bool solves2(int curX, int curY,int myDir[], int direction, int before, int after, int newMveCnt, int curMoveCnt, int maxMoves,int finalCoords[2][2401])
{
bool TorFe = false;
	bool TorFn = false;
	bool TorFw = false;
	bool TorFs = false;
	bool lastMove = false;
	int newX=curX;
	int newY=curY;

		if((curY==1&&curX==1)&&(curMoveCnt==maxMoves)) // Am I finished? YES! You are completely finished.
		{
		//cout<<"Debug: YOU FOUND THE CORRECT PATH!"<<endl<<endl;
		lastMove=true; 
		return lastMove;
		}  
		
		else if((curMoveCnt<maxMoves))// Am I finished? NO! You are not in position 1,1 and not finished.
		{
		//cout<<"Debug: I AM SOLVING THE MAZE!"<<endl;
		TorFe=(caveInfo[curY][curX+1]=='T');
		TorFn=(caveInfo[curY+1][curX]=='T');
		TorFw=(caveInfo[curY][curX-1]=='T');
		TorFs=(caveInfo[curY-1][curX]=='T');
		
			if(TorFe||TorFn||TorFw||TorFs) //checks for possible moves
			{	
				myDir[curMoveCnt]=direction;
				finalCoords[0][curMoveCnt]=curX;
				finalCoords[1][curMoveCnt]=curY;
				caveInfo[curY][curX] = 'V';
				//cout<<"Debug:x,y "<<curX<<","<<curY<<" curMoveCnt: "<<curMoveCnt<< " maxMoveCnt = "<< maxMoves <<endl<<endl;
				//curX, curY, myDir, direction, before, after, newMveCnt, curMoveCnt, maxMoves, finalCoords
				if(TorFe==true)
				{
				solves2(++newX, newY,myDir,direction=69,before, after,newMveCnt,++curMoveCnt,maxMoves,finalCoords);//move east
				}				
				else if(TorFn==true)
				{
				solves2(newX, ++newY,myDir,direction=78,before, after,newMveCnt,++curMoveCnt,maxMoves,finalCoords);//move north
				}
				else if(TorFw==true)
				{
				solves2(--newX, newY,myDir,direction=87,before, after,newMveCnt,++curMoveCnt,maxMoves,finalCoords);//move west
				}				
				else if(TorFs==true)
				{
				solves2(newX, --newY,myDir,direction=83,before, after,newMveCnt,++curMoveCnt,maxMoves,finalCoords);//move south
				}			
			}
		}	//cout<<"Debug:START BACKTRACKING"<<endl;//++curY,curX,--curMoveCnt,myDir,direction, before, after, newMveCnt++, maxMoves, finalCoords
			curMoveCnt=backTrack(curX, curY,curMoveCnt,myDir ,direction, before, after, newMveCnt, maxMoves,finalCoords);
		if(curY==1 && curX==1)// this backtrack to the start of this look.
		{		
		backTrack(curY, curX,curMoveCnt,myDir,direction, before, after, newMveCnt, maxMoves,finalCoords);
		}
		return lastMove;
}
// before, after, newMveCnt++
// ,int before, int after, int newMveCnt
bool solves(int curX, int curY,int maxMoves, int curMoveCnt,int myDir [],int direction,int finalCoords[2][2401],int before, int after, int newMveCnt)
{
	bool TorFe = false;
	bool TorFn = false;
	bool TorFw = false;
	bool TorFs = false;
	bool lastMove = false;
	int newX=curX;
	int newY=curY;

		if((curY==1&&curX==1)&&(curMoveCnt==maxMoves)) // Am I finished? YES! You are completely finished.
		{
		//cout<<"Debug: YOU FOUND THE CORRECT PATH!"<<endl<<endl;
		lastMove=true; 
		return lastMove;
		}  
		
		else if((curMoveCnt<maxMoves))// Am I finished? NO! You are not in position 1,1 and not finished.
		{
		//cout<<"Debug: I AM SOLVING THE MAZE!"<<endl;
		TorFe=(caveInfo[curY][curX+1]=='T');
		TorFn=(caveInfo[curY+1][curX]=='T');
		TorFw=(caveInfo[curY][curX-1]=='T');
		TorFs=(caveInfo[curY-1][curX]=='T');
		
			if(TorFe||TorFn||TorFw||TorFs) //checks for possible moves
			{	
				myDir[curMoveCnt]=direction;
				finalCoords[0][curMoveCnt]=curX;
				finalCoords[1][curMoveCnt]=curY;
				caveInfo[curY][curX] = 'V';
				//cout<<"Debug:x,y "<<curX<<","<<curY<<" curMoveCnt: "<<curMoveCnt<< " maxMoveCnt = "<< maxMoves <<endl<<endl;
				//,before,after,newMveCnt
				if(TorFe==true)
				{
				solves(++newX, newY,maxMoves,++curMoveCnt,myDir,direction=69,finalCoords,before, after, newMveCnt++);//move east
				}				
				else if(TorFn==true)
				{
				solves(newX, ++newY,maxMoves,++curMoveCnt,myDir,direction=78,finalCoords,before, after, newMveCnt++);//move north
				}
				else if(TorFw==true)
				{
				solves(--newX, newY,maxMoves,++curMoveCnt,myDir,direction=87,finalCoords,before, after, newMveCnt++);//move west
				}				
				else if(TorFs==true)
				{
				solves(newX, --newY,maxMoves,++curMoveCnt,myDir,direction=83,finalCoords,before, after, newMveCnt++);//move south
				}			
			}
		}	//cout<<"Debug:START BACKTRACKING"<<endl;//++curY,curX,--curMoveCnt,myDir,direction, before, after, newMveCnt++, maxMoves, finalCoords
			curMoveCnt=backTrack(curY, curX, curMoveCnt,myDir ,direction, before, after, newMveCnt, maxMoves,finalCoords);
		if(curY==1 && curX==1)// this backtrack to the start of this look.
		{		
		backTrack(curY, curX,curMoveCnt,myDir,direction, before, after, newMveCnt, maxMoves,finalCoords);
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
    const int MAXMOVES=2401;
	int finalCoords[2][MAXMOVES];
	int moves[MAXMOVES];
	int rowNum=1; // Instructions specify to start at 1.
	int maxX=0; // Size of the rows.
	int maxY=0; // Size of the columns
	const int STARTPOINT=1; 
	int tmpNum=0; 
	int direction=69;
	int startCnt=1;
	int numOfMoves;
	//bool finished=false;
	int index=1;
	int index2=1;
	MyPnt start;
	int before=0;
	int after=0;
	int newMveCnt=0;

	// Variables for main ends here
	
	cin >> maxX>>maxY;	
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
	numOfMoves=numCntTChar(maxX,maxY);
	//cout<<endl<<"Number of Moves:"<<numOfMoves<<endl<<endl;
	if (!(caveInfo[start.xAxis][start.yAxis]=='T')) // Checks (1,2) and (2,1) and (1,1) for T's.  If not found cave is automatically untraversable. 
	{
		cout<<"Cave untraversable"<<endl;
		return 0;
	}
	//else
	{ 

	//cout<<"I'm here"<<endl;//++newX, newY,maxMoves,++curMoveCnt,myDir,direction=69,finalCoords,before, after, newMveCnt++
	solves(start.xAxis+1,start.yAxis,numOfMoves,startCnt,moves,direction,finalCoords,before, after, newMveCnt); 
	}
	

		cout<<"Start ("<<finalCoords[index][index2]<<","<< finalCoords[index][index2]<<")" << endl; 
		for(int index2=1;index2<numOfMoves;index2++,cout<<")"<<endl)
		{		
			switch(moves[index2])
				{
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
				if(index==0)
				{				
				cout<<",";
				}
			}			
		}
		 		
	 return 0;
}

