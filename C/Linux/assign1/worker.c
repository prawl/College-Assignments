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
		
	Compiler Instructions: gcc -o coordinator coordinator.c
								  gcc -o worker worker.c


*/
//*****************************************************************************	
#include<stdio.h>

#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	printf("Successfully forked the process.  Worker is running...\n");

	int num1 = 0;
	int num2 = 0;
	int result;

	if(argv[1] != NULL){ //If there is valid input, use it.
		num1 = atoi(argv[1]);
	}//end if
	if(argv[2] != NULL){ //If there is valid input, use it.
		num2 = atoi(argv[2]);
	}//end if

	printf("Now adding users input...\n");
	printf("%d", num1);
	printf(" +");
	printf(" %d", num2);
	printf(" = ");
	result = num1 + num2;
	printf("%d\n", result);

	exit(result); 			//Returns the result to parent process.

}//end main
