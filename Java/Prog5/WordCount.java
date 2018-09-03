/*
	Patrick Rawlings
	CSCI 3310 Section 1
	Fall 2011
	Program 5
	12/6/11

	Description: 
	1) This program is to read an input file whose name will be specified
	as command line argument, breaking the lines of the file into words.  
	
	2) Store the words in a hash table along with a count of how many times the word
	appears in the text.
	
	3) Produce the following as output to standard output.  
	The n most frequently occurring words where the value for n is specified on
	the command line.  Output one line per word, giving the word and how many times
	it occurs.
	The total number of unique words found in the file.
	
	I/O format: The program will read in a text file followed by a number that
	specifies the top n words in the file. (ie. java WordCount textfile.txt 4).
	The program will throw an exception if the input is not of the above 
	specifications.

	Error Handling:  None required.

	ASSUMPTIONS: We are assuming the text file does not contain more than
	11003 unique words and the number of words "n" you are report is not above 
	the number of words in the file. (ie. Suppose you wanted the top 5 most
	used words in the text file but there are only 4 words in it, an error 
	will occur).  

*/

import java.io.*;
import java.util.*;
import java.lang.*;
import java.util.Enumeration;

public class WordCount{

	// Declarations and initialization for hash table.  Using Java API.
	public static final int TABLESIZE = 11003;
	public static Hashtable<String,WordItem> hashTable = new Hashtable<String, WordItem>(TABLESIZE);

//******************************************************************************
	/* wordCopy returns a word whose position is located in the input string
		line from position firstPos through lastPos, mapping all letters to
		lower case
		Method: is to copy the characters into a changeable StringBuffer, then
		convert to lower case; then return as a String.
	*/
	public static String wordCopy(String line, int firstPos, int lastPos){

		StringBuffer word = new StringBuffer();
		word.append( line.substring(firstPos,lastPos+1));
		for (int i = 0; i < word.length(); i++){
			word.setCharAt(i,Character.toLowerCase(word.charAt(i)));
		}//end for
		return word.toString();

	}//end wordCopy
//******************************************************************************
	/*	printHashTable is a function that will print out the contents of a filled
		hash table.  This is used for debugging purposes.  
	*/
	public static void printHashTable (){
		
		System.out.println("--------------------------------------");
		System.out.println("Retrieving all keys from the Hashtable");
		Enumeration e = hashTable.keys();

      while( e. hasMoreElements() ){      
       	System.out.println("{" + e.nextElement() + "}");
		}//end while

		System.out.println("---------------------------------------");
	}//end printHashTable
//******************************************************************************
	/*
		wordCount is a function that reports how many of each top words are in
		the text file.  This function requires you to have a hash table that
		is a global variable and is of the naming scheme "hashTable". The function
		takes the input "numWords" which is input variable from the user.
		(ie. java WordCount text.txt 4) where 4 will be number of words.  
	*/
	public static void wordCount (int numWords){
	
		Vector<WordItem> mrVec = new Vector<WordItem>(hashTable.size());	//Vector named mrVec
		mrVec.addAll(hashTable.values());											//Put all values from hashTable to vector.
		Collections.sort(mrVec);														//Sort the vector, ascending order.
		System.out.println("The " + numWords + " most frequently occurring words were: ");
	
		for(int i = 1; i <= numWords; i++){
			System.out.println(i + ". " + mrVec.get(mrVec.size()-i).getWord() + " occurred " + mrVec.get(mrVec.size()-i).getCount() + " times."  ); 
		}//end for	
 
		System.out.println(); 
		System.out.println("There were a total of " + hashTable.size() + " unique words." );

	}//end wordCount
//******************************************************************************

	public static void storeHash(String word){

		//printHashTable();
		WordItem  hashWord = new WordItem(word);		
		WordItem  dupHashWord =(WordItem) hashTable.get(word);

		if(word.length() == 0) return;

		if(hashTable.containsKey(word)){				// Word is already in the table, increment count for that word.
			//WordItem  temp =(WordItem) hashTable.get(word);
			dupHashWord.setCount(dupHashWord.getCount()+1);
			//System.out.println("Debug: WordItem hashWord contains : " + temp.getWord() + " and " + temp.getCount() );
		}//end if

		else{													// Add word to hash table.
			//WordItem  hashWord = new WordItem(word);	
			hashTable.put(word, hashWord); 		
			//System.out.println("Debug: WordItem hashWord contains : " + hashWord.getWord() + " and " + hashWord.getCount() );
		}//end elses

	}//end storeHash
//******************************************************************************
	/* bufToHash filled s hash table from the given input buffer 
		(ie. a line of text). The function's input is a String line which
		holds literally a line of text from the text file.  
	*/
	public static void bufToHash (String line){
		int tracker = 0;										//Holds a count as you go through each char.
		int wordEnd = 0;										//Holds the end char position for each word in a line.
		int wordStart = 0;									//Hold the beginning char for position for each word in a line.
		char curChar = ' ';									//Current char as you go through the entire line.
		char prevChar = ' ';									//Previous char to curChar current location.
		char nextChar = ' ';									//Next char to curChar current location.
		String word = "";										//Holds each individual word from the line.

		for(int i = 0; i < line.length(); i++){
		
			//System.out.println("Debug: Starting the for loop now.");
			//System.out.println("Debug: Tracker is located at position " + tracker + " at char " + curChar);
			//System.out.println("Debug: wordStart is currently loacted at " + wordStart);
			//System.out.println("Debug: wordEnd is currently loacted at " + wordEnd);
			//System.out.println("Debug: Current line length is " + line.length());
			curChar = line.charAt(i);
			//System.out.println("Debug: Current char is : " + curChar );
			
			if(i >= 1){											//If I can get access to a valid char before cur grab it.
				prevChar = line.charAt(i-1);
				//System.out.println("Debug: prev char is : " + prevChar );
			}//end if

			if(i != line.length()-1){						//If I can get access to a valid char after cur grab it.
				nextChar = line.charAt(i+1);
				//System.out.println("Debug: next char is : " + nextChar );
			}//end if

			//System.out.println("Debug: Current position of wordEnd is: " + wordEnd);	
		
			if(tracker == line.length() -1  && Character.isLetter(curChar) == true ){ 	//At the end of the line.  	
				word = wordCopy(line, wordStart, tracker);
				//wordStart = tracker;
				//wordEnd = tracker;
				//System.out.println("Debug: wordStart is currently loacted at " + wordStart);
				//System.out.println("Debug: Current word is 1: " + word);
				storeHash(word);
			}//end if

			if(Character.isLetter(curChar) == false ){											//Current char is not a valid letter.
				//System.out.println("Debug: " + curChar + " invalid char detected!");
				//System.out.println("Debug: Current position of wordEnd is: " + wordEnd);
				//System.out.println("Debug: Word length is " + wordEnd);	
				
				if((nextChar == ' ' && Character.isLetter(prevChar) == true)  && curChar == '\'' 
																	){ // This is case see a invlid ' at the end of the word. 
					wordEnd = tracker - 1;			
					//System.out.println("Debug: wordEnd is currently located at " + wordEnd + ".  Tacker is located at " + tracker);
					word = wordCopy(line, wordStart, wordEnd);
					wordStart = tracker;
					wordEnd = tracker;
					//System.out.println("Debug: wordStart is currently loacted at " + wordStart);
					//System.out.println("Debug: Current word is 2: " + word);	
					storeHash(word);				
				}//end if

				if ((Character.isLetter(prevChar) == true && Character.isLetter(nextChar) == true) && curChar == '\'' 
					&& (prevChar != ' ' && nextChar != ' ') 										){//This is case see a ' in an valid spot.
					wordEnd+=1;
				}//end if
				else if((prevChar == ' ' && Character.isLetter(nextChar) == true) && curChar == '\'' 
												){ 															  // his is case see a ' in an invalid spot.				
					wordStart+=1;
				}//end else if
				else{																							  //Cur char is invalid but not a '
					
					if(wordStart == wordEnd && wordStart != 0){ 									  //Skips an invlid char.
						//System.out.println("Debug I AM HERE!");
						wordStart = wordEnd+1;
					}//end if
					else{																						  //If the char makes it here
																												  //it's safe to store it into the hash table.
						wordEnd = tracker - 1;			
						//System.out.println("Debug: wordEnd is currently located at " + wordEnd + ".  Tacker is located at " + 	tracker);
						word = wordCopy(line, wordStart, wordEnd);
						wordStart = tracker+1;
						wordEnd = tracker;
						//	System.out.println("Debug: wordStart is currently loacted at " + wordStart);
						//System.out.println("Debug: Current word is 3: " + word);
						storeHash(word);	
					}//end else
				}//end else
			}//end if
			tracker++;
			wordEnd++;									
		}//end for
	}//end bufToHash
//******************************************************************************
	
	public static void main(String[] args){

		 if (args.length < 2){
		    System.out.print("ERROR: insufficient number of command line ");
		    System.out.println("arguments. Program aborted.");
		    return;
		 }//end if

		 File inFile = new File(args[0]);
		 int numWords = Integer.parseInt(args[1]);

		 try {
		 Scanner keyboard = new Scanner(inFile); // text info from stdin
		 String line;                      		  // holds input lines
		 //System.out.println("Debug: File successfully found!");			
		
			 while (keyboard.hasNext()){
				line = keyboard.nextLine();
				bufToHash(line);	
			 }//end while
		 }//end try
		 catch(FileNotFoundException e){System.out.println(e); return;}

		wordCount(numWords);	

	}//end main
//*****************************************************************************
}//end WordCount
