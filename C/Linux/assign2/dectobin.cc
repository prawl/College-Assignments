/*
	Patrick Rawlings
	CSCI 4630
	Spring 2012
	Assignment 2
	2/27/12

	Description:  This program reads in decimal numbers from a file called
	dec.dat and produces their binary conversion to a output file bin.dat. The 
	purpose of this program is to demonstrate the functionality of pipes in
	a linux based system.  Dectobin (Acting as a controller)
	will read in the data, pass the decimal data to another program called 
	"dectohex.cc" which will convert the data into hexidecimal and them pass 
	the hexidecimal result to another program called "hextobin.cc".  Hextobin
	will then take it's data recieved via the pipe and convert the data into
	binary.  Then it will pass it's result back to this program which will
	write the result to a file.  NOTE: All 3 programs must be in the same
	directory.

	I/O format: The input will be recieved from a txt file called "dec.dat" and
	the output will write to a file called "bin.dat"

	Error Handling:   

	ASSUMPTIONS: There will be no user interactivity when running the program.
	AKA no output to the screen.
	
	Compiler Instructions: Used g++ compiler. 

*/
#include <stdio.h>		//standard input/output.
#include <unistd.h>		//fork, pipe, execlp system calls.
#include <stdlib.h>		//exit calls.
#include <string.h>		//strlen call.
#include <sys/wait.h>	//system wait call.

int main(){

	int status;
	int PIPE[3];			//initializes 3 pipes.				
	pid_t child_pid;		//initializes child's process id.
	

	int pfd1[2];			//making the pipes.
	int pfd2[2];
	int pfd3[2];


	char buf1[101];		//buffer used to read and write to the txt files.
	char buf2[100];

	FILE *inputFile;		//initializes the input and out files.
	FILE *outputFile;

	inputFile = fopen("dec.dat", "r");
	outputFile = fopen("bin.dat", "w");

	PIPE[0] = pipe(pfd1);//connecting each pipe with their read/write IO.
	PIPE[1] = pipe(pfd2);
	PIPE[2] = pipe(pfd3);

	child_pid = fork();	//fork the process for dectohex.
	
	if(child_pid == -1){ //FORK FAILED.
		perror("Error!  Fork 1 Failed!");
		exit(1);
	}//end if

	if((PIPE[0] == -1) || (PIPE[1] == -1) || (PIPE[2] == -1)){ //PIPE FAILED.
		perror("Error! Pipe Failed!");
		exit(1);
	}//end if

	if(child_pid == 0){	//CHILDS CODE
		close(pfd1[1]);	//IMPORTANT: You must close the unused pipes or 
		close(pfd2[0]);	//serious errors could occur.  The consequnces
		close(pfd3[1]);	//will never be the same! :(
		close(pfd3[0]);
		

		dup2(pfd1[0],0);	//You must duplicate the standard in and out and
		dup2(pfd2[1],1);	//replace the normal one with your own to create
								//a stream to correctly use the pipe.

		execlp("./dectohex", "dectohex", NULL); //run the program "dectohex.cc"
	}//end if
	
	child_pid = fork();	//fork the process for hextobin.

	if(child_pid == -1){ //FORK FAILED
		perror("Error! Fork 2 Failed!");
		exit(1);
	}//end if

	if(child_pid == 0){ 	//CHILDS CODE
		close(pfd3[0]);	//IMPORTANT: You must close the unused pipes or							
		close(pfd2[1]);	//serious errors could occur.  The consequnces
		close(pfd1[0]);	//will never be the same! :(
		close(pfd1[1]);

		dup2(pfd2[0], 0);	//You must duplicate the standard in and out and					
		dup2(pfd3[1], 1);	//replace the normal one with your own to create
								//a stream to correctly use the pipe.

		execlp("./hextobin", "hextobin", NULL);	//run the program "hextobin.cc"				
	}//end if
								//PARENT CODE
	close(pfd1[0]);		//IMPORTANT: You must close the remaining pipes or	
	close(pfd2[0]);		//serious errors could occur.  I crashed the VM doing
	close(pfd2[1]);		//this.
	close(pfd3[1]);

	while((fgets(buf1, 100, inputFile)) != NULL)	//Look through the input file.
		write(pfd1[1], buf1, strlen(buf1));			//Store the data into buffer for
																//manipulation.

	close(pfd1[1]);		//Close the pipe after we're finished using it.
	dup2(pfd3[0], 0);		//Duplicate the standard in and out again.

	wait(&status);			//Wait for both child p_id's to exit before writing output.

	while((fgets(buf2, 100, stdin)) != NULL){		//Write the content of buffer to 																
		fprintf(outputFile, "%s", buf2);				//the output file.
	}//end while
	fclose(inputFile);									//Close file for good measure.
	fclose(outputFile);

	return 0;

}//end main

