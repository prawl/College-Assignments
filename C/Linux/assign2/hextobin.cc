/*
	Patrick Rawlings
	CSCI 4630
	Spring 2012
	Assignment 2
	2/27/12

	Description:  This program is controlled by dectobin.cc.  See that program
	for the description.  The program converts hexideciaml to binary.  

	ASSUMPTIONS:  This program is controlled by dectobin.cc.  See that program
	for the description.

	IMPORTANT: Do not use cin or cout as it interferes with reading from sandard in/out.

*/

#include <string.h>		//strdup calls.
#include <stdlib.h>		//exit calls
#include <stdio.h>		//standard input/output.

/*
	hexToBin is a function that reads through an array of hexidecimal
	and prints out decimal.  
*/

void hexToBin(char myArray[]){

	int inc = 0;
	int flag = 0;  							//Set only if a zero exist

	while(myArray[inc] != '\n'){			//Run until end of data is reached.

		if(flag == 0){							//No flag exist.

			switch(myArray[inc]){			//Repalce the hex value with binary value
					case '0':printf("0");					
						flag++; 
						break;
	
					case '1':printf("1");
						flag++;
						break;
	
					case '2':printf("10");
						flag++;
						break;

					case '3':printf("11");
						flag++;
						break;

					case '4':printf("100");
						flag++;
						break;

					case '5':printf("101");
						flag++;
						break;

					case '6':printf("110");
						flag++;
						break;

					case '7':printf("111");
						flag++;
						break;

					case '8':printf("1000");
						flag++;
						break;

					case '9':printf("1001");
						flag++;
						break;

					case 'a':
					case 'A':printf("1010"); 
						flag++;
						break;     
            
					case 'b':
					case 'B':printf("1011");
						flag++;
						break;

					case 'c':
					case 'C':printf("1100");
						flag++;
						break;

					case 'd':
					case 'D':printf("1101");
						flag++;
						break;

					case 'e':
					case 'E':printf("1110");
						flag++;
						break;

					case 'f':
					case 'F':printf("1111");
						flag++;
						break;

					case ' ':printf(" "); 
						flag++;
						break;
			}//end switch
		}// end if
		else{

			switch(myArray[inc]){								

					case '0':printf("0000"); 
						break;

					case '1':printf("0001");
						break;

					case '2':printf("0010");
						break;

					case '3':printf("0011");
						break;

					case '4':printf("0100");
						break;

					case '5':printf("0101");
						break;

					case '6':printf("0110");
						break;

					case '7':printf("0111");
						break;

					case '8':printf("1000");
						break;

					case '9':printf("1001");
						break;

					case 'a':
					case 'A':printf("1010"); 
						break;

					case 'b':
					case 'B':printf("1011");
						break;

					case 'c':
					case 'C':printf("1100");
						break;

					case 'd':
					case 'D':printf("1101");
						break;

					case 'e':
					case 'E':printf("1110");
						break;

					case 'f':
					case 'F':printf("1111");
						break;

					case ' ':printf(" "); 
						break;
			}//end switch
		}//end else
		inc++; 										
    }//end while
	printf("\n");
							
}//end hexToBin

int main(){

	int inc1 = 0;
	int inc2 = 0;

	char *binArray[200];				//Array to hold binary conversions.
	char inputBuf[200];				//Buffer to the data from standard in to be
	bool done;							//passed to the binArray.

	while(!done){									//Get input from "stdin"
		fgets(inputBuf, 100, stdin);			//Read from stdin which is piped in.
			if(feof(stdin)){						//Break when you hit end of the values.
				break;
			}//end if
		binArray[inc1] = strdup(inputBuf);  //Put the input data into a separate buffer.
		inc1++;
    }//end while

	while(inc2 < inc1){
		hexToBin(binArray[inc2]);			//Coversion here.
		inc2++;
    }//end while
	
	return 0;
}//end main
