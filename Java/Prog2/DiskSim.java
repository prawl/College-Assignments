/*
	Patrick Rawlings
	CSCI 3310 Section 1
	Fall 2011
	Program 2
	10/5/11

	Description: The program is to simulate managing files on a disk. The disk 
	consists of sectors, each of which is capable of storing the same number of 
	characters. When a request is made by the operating system to store a file on 
	the disk, the disk controller program must determine if enough free sectors 
	are available on the disk for storing the file. It must also keep track of 
	which sectors contain the information for a given file, as well as keep track 
	of the sectors still available.

	I/O format: The input for the program is a text file that contains three
	items per line.  These items are opCode, file_id, and size. (ie. c 1 0)
	The command for input is simply < test.txt which will be in the same 
	directory.  The program will then take the file and format the data as 
	if it were a disk.

	Error Handling:
	1) Attempting to create a file that already exist is an error.  
	This should be handled by printing a suitable error message to the screen.
	
	2) Attempting to create a file for which there is a not enough available 
	space is an error.
	
	3) Attempting to delete a non-existing file is na error, print a message 
	and ignore the command.
	
	4) Attempting to print the information for a non-existant file is an error.
	Print a message and ignore the command.	

	ASSUMPTIONS: We are assuming the only commands are print, create, delete are 
	the only commands we can use and that I am an awesome person.
*/
//*****************************************************************************	

import java.io.*;
import java.util.*;

public class DiskSim
{

private static final int NUM_SECTORS = DiskParam.NUM_SECTORS;
//NUM_SECTORS holds the max number of sectors. 30													
private static final int NUM_FILES = DiskParam.NUM_FILES;
//NUM_FILES sets upper bound to how many files can be created. 20		 
private static final int MAX_SIZE = DiskParam.MAX_SIZE;
//MAX_SIZE sets upper bound to how many characters can be contained in a file.25
private static final int SECTOR_SIZE = DiskParam.SECTOR_SIZE;
//Sets upper bound to how many characters each sector can hold. 3

private static List <SectorUsage>[] file_array = new List [NUM_FILES];
//Array 2 in the file list.  This organizes the sectors list.

private static  List <SectorUsage> openSectors = new List <SectorUsage> ();
//Creates a list.This spot is used to hold how many sectors are...

private static int [] numchars = new int [NUM_FILES]; 
//Array 1 in the file list. Used to store info about the file. 
//Specifically how many chars in in the file which is used to calculate the size

public static void main (String[] args){

SectorUsage initial = new SectorUsage(0, NUM_SECTORS - 1);// initializes free space.
openSectors.add(1, initial);
Scanner kbd = new Scanner(System.in);


//Prefill numchars to all -1 to tell if full or not.
for(int i = 0; i < NUM_FILES; i++) {
numchars[i] = -1;
file_array[i] = new List <SectorUsage> ();

} 

char opCode; // single character. ('c'opy, 'p'rint, 'd'elete, x - exit)
int file_id; // an int between 0 and NUM-FILES - 1.
int size;    // Size of the file. Cannot exceed MAX_SIZE.
int outputSize = 0; // Captures the size for printing purposes.


//System.out.println("Debug: NUM_SECTORS = " + NUM_SECTORS);
//System.out.println("Debug: NUM_FILES = " + NUM_FILES);
//System.out.println("Debug: MAX_SIZE = " + MAX_SIZE);
//System.out.println("Debug: SECTOR_SIZE = " + SECTOR_SIZE);


	while (kbd.hasNext())
	{	
	opCode = kbd.next().charAt(0);	
	file_id = kbd.nextInt();
	size = kbd.nextInt();

	//System.out.println("Debug: opCode = " + opCode);
	//System.out.println("Debug: file_id = " + file_id);
	//System.out.println("Debug: size = " + size);

	if(size > 0){
	outputSize = size;
	}

		switch (opCode) 
		{
		case 'c'://Create entry.
		create(file_id, size, outputSize);
		break; 

		case 'p'://Print entry.
		print(file_id, outputSize);
		break;		
	
		case 'd'://Delete entry.
		delete(file_id, size);
		break;
		
		case 'x'://Exit the program.
		exit(size);
		return;
		}// end switch
	}//end while
}//end main
//******************************************************************************
//public static int sectorCounter() calculates how many free sectors are left.
// Like fileCounter this is effective at the end of the program.  It does not
// take in any input but simply calculates how many sectors that have not been
// used and returns this number.
public static int sectorCounter()
{
	int totalSectors = 0;

	for(int i = 1; i <= openSectors.size(); i++)
	{
	totalSectors = (openSectors.get(i).getEnd() - openSectors.get(i).
	getStart() + 1);
	}
	totalSectors = NUM_SECTORS - totalSectors;
	//System.out.println("Debug: totalSectors = " + totalSectors);
return totalSectors;
}
//******************************************************************************
// public static int fileCounter(int size) calculates how many files have been
// created.  This is particularly effective at the end of the program becauase it
// isn't possible to keep a running total so simply tallying all the available
// files at the end works well.  It takes in size to determine how many files
// have been create.
public static int fileCounter(int size)
{
	int numFiles = 0;
	for(int i = 0; i < NUM_FILES; i++)
	{
		if (numchars[i] > 0)
		{
		numFiles++;
		}//end if
	}//end for
	//System.out.println("Debug: numFiles = " + numFiles);
return numFiles;
}
//*****************************************************************************
//public static void delete(int file_id, int size) deletes a record from the 
//disk.  It takes in file_id to determine where the sector to be deleted is and
// size to know how much to delete.  
public static void delete(int file_id, int size)
{
	//System.out.println("Debug: file_id = " + file_id);
	int freeSectors = 0; //Temporarily holds how many sectors are free for 
								//deleting purposes.

	if (numchars[file_id] > -1)//There is a file to delete.
	{
	//System.out.println("Debug: File does exist, time to delete it.");

		for (int i = 1; i <= file_array[file_id].size(); i++)
		{
		freeSectors += file_array[file_id].get(i).getEnd() - 
		file_array[file_id].get(i).getStart() +1;
		}//end for
	numchars[file_id] = -1; //time to update the list to reflect that a file no 
									//longer exist.
	//System.out.println("Debug: numchars[file_id] should now be -1 to reflect a 
	//sucessful delete. = " + numchars[file_id] );

	//I need to update the how many sectors there currently are by 
	//subtracting the ones I deleted.
	System.out.println("\nFile " + file_id + " deleted, " + freeSectors +
	 " sectors freed.");

	//Now I actually need to remove the sectors.
	//System.out.println("Debug: Now deleting sectors.");
		for(int i = 1; i <= file_array[file_id].size(); i++)
		{	
		SectorUsage g = file_array[file_id].get(i);
		openSectors.add(1,g ); // What's the purpose of this line?
		file_array[file_id].removeAll();//Remove the data from the sectors in the
												  // specified spot.
		}//end for

	}//end if
	else
	{// File does not exist, cannot delete
	System.out.println("Error!  File does not exist, cannot delete!");
	}//end else
}//end delete
//*****************************************************************************
//public static void create(int file_id, int size) creates a new file by 
//	determining if there is enough space to create then stores the file into
// the available sector(s).  Create take in file_id to determine the location
// of the new file and size to determine how many sectors the new file will 
// occupy.  
public static void create(int file_id, int size, int outputSize)
{
if(numchars[file_id] > -1)//file already exist, skip it.
{
 System.out.println("Error! File already exist. Ignoring file.");
}
else //file has not been created yet.  Let's make it! yeah!
{
	System.out.println("File " + file_id + " created, size = " + outputSize);
	List <SectorUsage> usage = new List <SectorUsage>(); //creates a new list 
																		  //called usage.
  	int spaceRequired = 0;
	if(size % SECTOR_SIZE == 0)// has a remainder.  Need to add 1. 
	{
	//System.out.println("Debug: I HAVE ENTERTED THE IF ");
	spaceRequired = (size / SECTOR_SIZE);
	}// end if
	else
	{
	//System.out.println("Debug: I HAVE ENTERTED THE ELSE");
	spaceRequired = (size / SECTOR_SIZE) +1;
	}//end else
	//System.out.println("\nDebug: Initial Stage of Sectors list : " + 
	//openSectors.get(1).getStart() + "  " + openSectors.get(1).getEnd());
	//System.out.println("Debug: Calculating how many sectors needed for a file.  
	//Sectors needed = " + spaceRequired);
	int sectorsize = 0;  	

	for(int i = 1; i <= openSectors.size(); i++) 
	{
   SectorUsage curSector = openSectors.get(i); //points s to position k of the 
													//created sectors
   sectorsize += curSector.getEnd() - curSector.getStart() +1;//How many open sectors are 
																 //currently available.
		
	//System.out.println("Debug: Comparing sectorsize with spaceRequired.");
    	if(sectorsize > spaceRequired) // There is space to save 
		{
		//System.out.println("Debug: Have space to save.  Saving now.");
      usage.add(1, new SectorUsage(curSector.getStart(), curSector.getStart() +
		spaceRequired -1));
      curSector.setStart(spaceRequired + curSector.getStart()); // Adjust for saved space. Start 
															  // is now after the saved data.
		//System.out.println(usage.get(1).getStart());   
		spaceRequired = 0;
      }
      else//if sectorsize < spaceRequired.  Not enough space to save
		{
      usage.add(1,curSector);
      openSectors.remove(i--);
      spaceRequired -= sectorsize;
      }//end else
      if(spaceRequired == 0) break;
  	}//end for
   if(spaceRequired > 0)
	{
   	for(int i = 0; i <= usage.size();i++)
		{
  		openSectors.add(1, usage.get(i));
   	return;   
		}//end for  
  	}//end if
   file_array[file_id] = usage;
   numchars[file_id] = size;
}//end else


}//end create
//*****************************************************************************
//	public static print (int file_id, int outputSize) prints off all the 
// available sectors or the sectors filled.  It takes in file_id which 
// determines the location of the sectors and outputSize which is just size
// but only data that is relavent.  
public static void print(int file_id, int outputSize)
{ 	
	if(file_id != -1)//Print the contents of the unused sector list.
	{
		if(numchars[file_id] == -1) //Files does not exist!
		{
		System.out.println("File " + file_id + 
		" non-existent, print command ignored.\n");
		return;
		}//end if	 
	// Print the sectors that I just filled up with my create cmd.;
	System.out.println("Sector usage for file " + file_id + " --- size = " + 
	outputSize + " characters.");
	System.out.println("Start Sector End Sector");
		for(int i = file_array[file_id].size(); i >= 1; i--)
		{		
		System.out.println("" + file_array[file_id].get(i).getStart() +
		 "\t      " +  file_array[file_id].get(i).getEnd() );
		}//end for	
	}///end if
   else 
	{
	//System.out.println("I see a -1 in file_id time to print all available
	// sectors!");
	System.out.println("\nContents of Sectors List");
	System.out.println("Start Sector  End Sector");
		for(int i=1; i <= openSectors.size(); i++)
		{
		System.out.println(openSectors.get(i).getStart() + "\t      " + 
		openSectors.get(i).getEnd()  );
		}// end for
	}//end else
}//end print
//******************************************************************************
// public static void exit (int size) prints out all the remaing files and 
// unused sectors.  This is especially effective at the time of exit because
// it's not possible to keep a running total so this works.  
public static void exit(int size)
{
int fileCount = 0;//Used for printing purposes only.
int printFreeSectors;//Used for printing purposes only.
fileCount = fileCounter(size);
printFreeSectors = sectorCounter();
System.out.println("SIMULATOR EXIT: File " + fileCount + " files exist," +
" occupying " + printFreeSectors + " sectors.");
}
//******************************************************************************
}//end DiskSim
