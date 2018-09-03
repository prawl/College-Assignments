/*
	Patrick Rawlings
	CSCI 3310 Section 1
	Fall 2011
	Program 4
	10/27/11

	Description: The program is to evaulate algebraic expressions through the
	following steps:
	
	1) Read in the infix expression as a string.
	2) Convert the infix expression to a postfix expression.
	3) Evalutes the postfix expression.

	I/O format: The first portion of the input (one or more lines) consists of 
	assignments of integer values to upper case letters.  The letters are in no
	particular order, but no letter will be assigned two values.  An example 
	assignment line is D = -45.  The integer values assinged to letters will be
	in the reange of a 32 bit integer.  The assignment lines always being with 
	the letter in column 1 of the input line.  You may assume that there will
	be one or more spaces between each token (ie. <letter>, <asst_op>, and 
	<number>).  A sectinel line of the form $PART2 indicates the end of the 
	assignment lines,  The second portion of the input (one or more lines) 
	consists of infix expressions.  An example is C-(B+(C+(A-E)))-X  .
	Each of the input expressions will consist of only upper case letters and the
	four operators.  The expression lines begin in column 1 and contain no 
	embedded spaces.  You may also assume that the values of any calculations 
	involved in evaluating an expression will all be in the range of a 32 bit
	integer. The input is terminated by the end-of-file (EOF) character. 
	Control-D.

	Error Handling: No error handling required.  

	ASSUMPTIONS: You may assume all input is 
	correctly formatted and there will be no attemps to divide by zero.

*/
//*****************************************************************************	

import java.io.*;
import java.util.*;
import java.lang.*;

public class InfToPost{

Deque<Integer> stack = new ArrayDeque<Integer>();// Initializes the stack.

public static void main (String[] args){

Scanner kbd = new Scanner(System.in);

Stack <Integer> intStack = new Stack <Integer>();//Initalizes the int stack.
Stack <Character> charStack = new Stack <Character>();//Initalizes the char stack.
char letter;//Holds the upper case letter in which will represent a int value.
char [] charArray = new char[25];//Holds chars from first while input
int [] numArray = new int [25];//Holds ints from first while in input.
int number;//Holds the integer value you wish to assign to the letter.
int result;//Holds the result of the postfix calculations
int index = 0;// Incremenenter for first while input loop.
String infix, postfix;//Holds infix & postfix expressions. 
String asst_op;//Holds the operand for the letter value expression. (ie: =)

	while (kbd.hasNext()){//Read in input until the string "$PART2" appears.
	
		letter = kbd.next().charAt(0);
		if (letter == '$') break;//Stop reading input if $ is found.
		charArray[index] = letter;
		asst_op = kbd.next();
		number = kbd.nextInt();
		numArray[index] = number;
		//System.out.println("Debug: " + letter + " " + asst_op + " " + number);
		index++;

	}//end while	

	while (kbd.hasNext()){ 
	
		infix = kbd.next();		
		postfix = infixToPostfix(infix, charStack);
		result = postfixCalc(postfix, numArray, charArray, index, intStack);
		printResult(infix, postfix, result);	
	
	}//end while

}//end main

//******************************************************************************
//public static int postfixCal takes it the postfix expression and calculates
//the mathmatical answer per set values.  The function takes in the String
//postfix, numArray, charArray, index, and the intStack.
public static int postfixCalc(String postfix, int [] numArray, char [] charArray, int index, Stack <Integer> intStack) {

int size = postfix.length();// holds size of current postfix string.
char charPostfix;//Holds current char in the string postfix.
int result = 0;
int curInt; //Holds the int version of what I need to calc.

//System.out.println("Debug: postfix " + postfix);

for(int i = 0; i < size; i++){//Find the current int in the expression.
charPostfix = postfix.charAt(i);//Puts each char from postfix into charPostfix.
curInt = convertToInt(postfix, numArray, charArray, charPostfix); 
//System.out.println("Debug: Current Int is " + curInt);

	if(charPostfix != '+' && charPostfix != '-' && charPostfix != '*' && charPostfix != '/' && charPostfix != '(' && charPostfix != 		')'){
	//System.out.println("Debug: Pushing " + curInt + " into the stack! ");
	intStack.push(curInt);
	}//end if
	else{

			if(charPostfix == '*'){//Multiply Case
				//System.out.println("Debug: Found a *, time to multiply!");
				int num2 = intStack.pop();
				int num1 = intStack.pop();
				result =  num1 * num2;
				intStack.push(result);
				//System.out.println("Debug: answer " + result);
			
			}//end if

			if(charPostfix == '+'){//Add Case
				//System.out.println("Debug: Found a +, time to add!");
				int num2 = intStack.pop();
				int num1 = intStack.pop();
				result = num1 + num2;
				intStack.push(result);
				//System.out.println("Debug: answer " + result);
			
			}//end if
		
			if(charPostfix == '/'){//Divide Case
				//System.out.println("Debug: Found a /, time to divide!");
				int num2 = intStack.pop();
				int num1 = intStack.pop();
				result =  num1 / num2;
				intStack.push(result);
				//System.out.println("Debug: answer " + result);
		
			}//end if

			if(charPostfix == '-'){//Subtract Case
				//System.out.println("Debug: Found a -, time to subtract!");	
				int num2 = intStack.pop();
				int num1 = intStack.pop();
				result = num1 - num2;
				intStack.push(result);
			//	System.out.println("Debug: answer " + result);
			
			}//end if	

	}//end else

}//end for

return result;
}//end evalPostfix
//******************************************************************************
//public static int convertToInt takes in the postfix expression, a char array,
//a int array and the current char in the postfix expression.  This function
//will return int value for the current char being looked at. (ie. A = 1)
//(ie. If A = 20, in the text file, A will hold the value 20).
public static int convertToInt (String postfix, int [] numArray, char [] charArray, char charPostfix){

int size = postfix.length();//Holds size of current postfix string.
int result = 0;//Holds the int result of current char.

for(int i = 0; i < size; i++){ 

		//System.out.println("Debug: Comparing " + charPostfix + " with " + charArray[i]);
		if(charPostfix == charArray [i]){// Found a match, replace match with int value in the string.
		//System.out.println("Debug: Found a match!");
		result = numArray [i];
		return result;//Return value if in preset text file.
		//System.out.println("Debug: Current Int is " + result);
		}//end if
}//end for

int curCharVal;// 
curCharVal = addr(charPostfix);//Give value of current char

if(curCharVal >= 0 && curCharVal <= 25){//Char is A - Z & not assigned a value.
	return curCharVal + 1;//Return value if not in text file using
}//end if

return -99;//Return value if not used data. (ie. +,-,/,*)
}//end convertToInt
//******************************************************************************
//public static String infixToPostfix takes in a string which is
//infix expression (ie. A+B-C) and turn's it into a postfix expression. (ie AB+C-).
//The function also takes in a character stack in order to complete this operation. 
public static String infixToPostfix (String infix, Stack <Character> charStack){

String postfix = "";//Will hold the postfix expression.
int size = infix.length();// Holds size of current infix string.
char charInfix;//Holds each char of infix, since infix is a string.
int curCharVal;//Holds the numerical value for each char in charInfix.

for(int i = 0; i < size; i++){

	charInfix = infix.charAt(i);//Put each char from infix into charInfix.
	curCharVal = addr(charInfix);//Gives the current numerical value of the char. 

	if(curCharVal >= 0 && curCharVal <= 25){//current char is a letter. (ie. A, B, C)
	//System.out.println("Debug: " + charInfix + " is being added to postfix.");
	postfix +=  Character.toString(charInfix);//Stores the contents of temp into a string.
	}//end if

	if(charInfix == '('){
	//System.out.println("Debug: " + charInfix + " is being pushed to the stack.");
	charStack.push(charInfix);
	}//end if	
	
	if(charInfix == ')'){
		while(!charStack.isEmpty()){
			char prevChar = (Character) charStack.pop();
			if(prevChar == '(')break;
			else{
			//System.out.println("Debug: " + prevChar + " is being pushed to the stack.");
			postfix += prevChar;
			}//end else	
		}//end while
	}//end if	

	if(charInfix == '+' || charInfix == '-' || charInfix == '*' || charInfix == '/'){
		while(!charStack.isEmpty()){
		char prevChar2 = (Character) charStack.pop();
			if(prevChar2 == '('){
			charStack.push(prevChar2);
			break;
			}//end if
			if(precEval(charInfix) <= precEval(prevChar2)){
			//System.out.println("Debug: " + prevChar2 + " is being pushed to the stack.");
			postfix+= prevChar2;
			}//end if
		}//end while
		charStack.push(charInfix);	
	}//end if

}//end for

	
if(!charStack.isEmpty()){ //This will empty the stack at the end if there is
									//any operators left in the stack.
//System.out.println("Debug: Reached the end! Time to pop what's remaining in the stack.");
	while(!charStack.isEmpty()){
   postfix+= charStack.pop();
	}//end while
}//end if

return postfix;
}//end infixToPostfix
//******************************************************************************
//public static int precEval take in the current char of the infix expression
//and returns either a 2 or a 1.  These numbers are to represent a precedence
//value of the current character in infix.  If there are other symbols the
//function will return -1.
public static int precEval (char charInfix){

if (charInfix == '*' || charInfix == '/') return 2;

if (charInfix == '+' || charInfix == '-') return 1;

return -1; // Not a valid operator.
}//end precEval
//******************************************************************************
//public static int addr returns the equivalent integer address
//for the letter given in ch, 'A' returns 0, 'Z' return 25 and all other
//letters return their corresponding position as well.
public static int addr (char ch){
return (int) ch - (int) 'A';
}//end addr
//******************************************************************************
//public static void printResult is a simply a function that will print the
//answer.
public static void printResult (String infix, String postfix, int result){

	System.out.println("Infix: " + infix);
	System.out.println("Postfix: " + postfix);
	System.out.println("Result: " + result);

}//end printResult
//******************************************************************************

}//end InfToPost
