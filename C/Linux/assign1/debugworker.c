/*
	Patrick Rawlings
	CSCI 4630
	Spring 2012
	Assignment 1
	1/26/12

	Description: The program is to run when coordinator.c opens it and add
	two integers given by coodinator.c.
	
	There are two kinds of processes for this program:

	1) A set of "worker" processes.  Each worker process gets two small integers
	as command line parameters (they will be available in its argv), computes 
	their sum and returns the result using exit system call.  So, for every sum
	a worker process is created.

	2) A "coordinator" process.  It is responsible for creating the "worker"
	processes, and coordinating the computation.  Note that all the computation is
	done by the "worker" processes.  All the numbers to be added are provided in 
	the command line for the coordinator process.

	I/O format: The program will take input from the program coodinator.c
	and add the inputs and return the sum of those two input.

	Error Handling:   

	ASSUMPTIONS: We are assuming no number will be over 10.  Only single digits.
*/
//*****************************************************************************	
#include<stdio.h>

int main(int argc, char *argv[]){

	printf("Debug: Worker is running...\n");

	int num1 = 0;
	int num2 = 0;
	int result;


   printf("Debug: Output: \n");
	int i = 1;
	for(i; i < argc; i++){
		printf("arg %d: %s\n", i, argv[i]);
	}//end for

	

   printf("Debug: Worker output...\n");
	printf(argv[1]);
	printf("\n");
	printf(argv[2]);
	printf("\n");


	if(argv[1] != NULL){ //If there is valid input, use it.
		num1 = atoi(argv[1]);
		printf("Debug: 1 Data succesfully passed to worker!\n");
	}//end if
	if(argv[2] != NULL){ //If there is valid input, use it.
		num2 = atoi(argv[2]);
		printf("Debug: 2 Data succesfully passed to worker!\n");
	}//end if


	printf("Debug: Now adding users input...\n");
	printf("Debug: Num1 + Num2\n");
	printf("Debug: %d\n", num1);
	printf("Debug: %d\n", num2);
	result = num1 + num2;
	printf("Debug: %d\n", result);

	exit(result);
	// code to pass result back to coordinator.c

}//end main
