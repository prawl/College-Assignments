/*
	Patrick Rawlings
	CSCI 4630
	Spring 2012
	Assignment 2
	2/27/12

	Description:  This program converts decimal to hexidecimal.

	ASSUMPTIONS:  This program is controlled by dectobin.cc.  See that program
	for the description.

	IMPORTANT: Do not use cin or cout as it interferes with reading from sandard in/out.
*/

#include <string.h>		//strdup calls.
#include <stdlib.h>		//exit calls
#include <stdio.h>		//standard input/output.

/*
	decToHex is a function that takes int a integer(deciaml) and returns
	an array of hexidecimal.  There are many function out that will do this
	process for you however the assignment instruction said we have to create
	our own method.
*/

void decToHex(int input){

	int SIZE = 8; 				//Max size of my char array.
	int flag = 0;				//Flags if zero is found.

	char hexArray[SIZE];		//Array to hold hex
	char *hex;					//Pointer to all possible choices.
	
	hex = strdup("0123456789ABCDEF");
	int inc = 0;
	
	while(inc < SIZE){		//Initialize array with 0's
		hexArray[inc] = '0';
		inc++;
	}//end while

	for(int dec = SIZE - 1; dec >= 0; dec--){	
		hexArray[dec] = hex[input % 16];		//Store the value into hex
		input = input / 16;
    	}//end for
      
	for(int inc = 0; inc < SIZE; inc++){
		if(flag == 0){
			if(hexArray[inc] != '0'){
				printf("%c", hexArray[inc]);
				flag = 1;
			}//end if
		}//end if
		else{
		printf("%c", hexArray[inc]);
		}//end else
	}//end for

}//end dectoHex

/*
	sizeOf is a simple function that returns the size of a given array.
*/
int sizeOf(char size[]){

	int inc = 0;
	bool Done; 

	while(!Done){					//Run until a break occurs
		if(size[inc] == '\n') {
			break;  		
		}//end if
		inc++;
	}//end while
	return inc + 1;

}//end sizeOf

/*
	skipEmpty is a function that reads from the buffer and if a blank spot
	is encountered it will simply skip that spot and resume adding the
	data to the array.
*/
void skipEmpty(char buf2[], int SIZE){	
	if(buf2[0] != ' '){					
		decToHex(atoi(&buf2[0]));     		//Put buffer into decToHex
	}//end if

	for(int inc = 0; inc < SIZE; inc++){
		if(buf2[inc] == ' '){					//Print space as appears.
			printf(" ");				
			decToHex(atoi(&buf2[inc + 1]));  //Continure printing     
		}//end if
    }//end for
	printf("\n"); 									//Print space for asthetics purposes.
}//end skipEmpty


int main(){

	int size;	
	int inc1 = 0;								//Incrementor 1
	int inc2 = 0;								//Incrementor 2

	char inputBuf[200];						//Buffer to grab from std in.
	char *buf[200];							//Buffer to hold data, will be pass
	bool done;									//from inputBuf.
	
	while(!done){
		fgets(inputBuf, 100, stdin);		//Read from stdin which is piped in.
			if((feof(stdin)) != 0){			//Break when you hit end of the values.
				break;
			}//end if
		buf[inc1] = strdup(inputBuf);		//Put the input data into a separete buffer.
		inc1++;
  	}//end while

	while(inc2 < inc1){
		size = sizeOf(buf[inc2]);			//Grab size of the duped buffer.
		skipEmpty(buf[inc2], size);		//Skip invlid spots.
		inc2++;
   }//end while
	return 0;

}//end main



