/*
	Patrick Rawlings
	CSCI 4630
	Spring 2012
	Assignment 1
	1/26/12

	Description: The program is to add single digit integers with the use of
	child processes in conjunction with worker.c
	
	There are two kinds of processes for this program:

	1) A set of "worker" processes.  Each worker process gets two small integers
	as command line parameters (they will be available in its argv), computes 
	their sum and returns the result using exit system call.  So, for every sum
	a worker process is created.

	2) A "coordinator" process.  It is responsible for creating the "worker"
	processes, and coordinating the computation.  Note that all the computation is
	done by the "worker" processes.  All the numbers to be added are provided in 
	the command line for the coordinator process.

	I/O format: The program will take input from the user in the form of 
	single integers with spaces.  (Ex: coordinator 1 2 3 4 5 6 7 8 9) Each
	integer will be added delineated by the spaces between each int.  The
	output will display the results of the addition.

	Error Handling:   

	ASSUMPTIONS: We are assuming no number will be over 10.  Only single digits.
*/
//*****************************************************************************	

#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

void cvtInt( char *str, int num){
    sprintf( str, "%d", num );
}

main(int argc, char *argv[]){
	
	int x;					//Holds fork's return value.
	int message, messageHolder;
	pid_t child_pid;		//Holds the ID of the child process.
	int size = 0;			//Max size of ansArray.
	int calcSize = 0;		//Used to calculate the total size needed by the ansArray		
	int newCount = 0;    //Holds the last item in ansArray.
	char *ptr_1;  			//Allocate the pointer 1.
   char *ptr_2;			//Allocate the pointer 2.
	char **ptr_3;	
	printf("Debug:arg size %d\n", argc);
	
	newCount = argc;		
	calcSize = argc - 1; 
	
	size = (2 *calcSize)  ; // Calculates the max size of ansArray.
	printf("Debug: Total size of need to hold all additons: %d\n", size);
	ptr_3 = calloc(size, sizeof(char*));//Sets a pointer to a array  

/*
	int i = 0;	
	for(i; i < size; i++){ 		 //Fill ansArray with 0's
		ansArray[i] = 0;
		printf("Debug:ansArray1: %d\n", ansArray[i]);
	}//end for
*/
	int i2 = 0;						//Puts buffer into ptr_3 array.
	for(i2; i2 < argc; i2++){
		ptr_3[i2] = argv[i2];
	}//end for

	int i4 = 0;				
	for(i4; i4 < size; i4++){  //Prints out the contents of ptr_3 array.
		printf("Debug:ptr_3: %s\n", ptr_3[i4]);
	}//end for	

	int inc = 1;
	while(inc < size){ //while there are number to add, add them.
		//printf("Debug: ANSARRAY: %d\n", ansArray[inc] );
		

		
		if(inc == size -1){ //Last spot
			printf("Debug: Answer = %s:\n", ptr_3[size - 1]);
			return 0;
		}
	

		ptr_1 = ptr_3[inc];
		ptr_2 = ptr_3[inc+1];
	
	
		printf("Debug: PTR =%c:\n", *ptr_1);
		printf("Debug: PTR =%c:\n", *ptr_2 );		

		printf("Debug: Attempting to fork the process...\n");
		x = fork();
		if(x == -1){	//error in process	
			perror("Error: Fork Failed!\n");
		}//end if
		if(x == 0){ 	//child process
			printf("Debug: Child's process successfully created!\n");
			execlp("./worker", "./worker", ptr_1, ptr_2, NULL); //run the program worker
		}//end if
		else{ 			//parents process
			child_pid = wait(&message);
			printf("Debug: Process id is: ");
			printf("%d:\n", child_pid);
			if(WIFEXITED(message) != 0){

				printf("Debug: Worker ended normally!\n");
		   	messageHolder=WEXITSTATUS(message);
		      printf("Debug: messageHolder: %d\n", messageHolder);

				ptr_3[newCount] =  malloc(10);			  //Creates new space in memory for the string.
				cvtInt( ptr_3[newCount], messageHolder); //Stores the result of the additon into a string in ptr_3[index].

				printf("Debug: newCount = %d\n", newCount); 
				printf("Debug: size = %d\n", size); 
		      //printf("Debug: Successfully saved %d\n", ansArray[newCount]); 
				printf("Debug:newCount is: %d\n" , newCount );
			   newCount = newCount+1;
				//printf("Debug:newCount is: %d\n" , newCount );
				
				int i5 = 0;				
				for(i5; i5 < size; i5++){  //Prints out the contents of ptr_3 array.
					printf("Debug:ptr_3: %s\n", ptr_3[i5]);
				}//end for	r
			
			}//end if				
			else{
				printf("Error in worker process!");
			}//end else
		}//end else
		inc= inc +2;
		printf("Debug: inc is now %d\n", inc); 
	}//end while






}//end main




