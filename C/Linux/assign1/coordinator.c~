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
	
	Compiler Instructions: gcc -o coordinator coordinator.c
								  gcc -o worker worker.c

*/
//*****************************************************************************	

#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

	/*
	void sigproc is a function that disables ctrl-c and prints msg when pressed.
	*/
	void sigproc(){ 		 
		signal(SIGINT, sigproc);
		printf("you have pressed ctrl-c ");
		signal(SIGALRM, sigproc);
	}//end sigproc


	/*
	void cvtInt is a funtion that converts an int into a string.  The arguments
	are the char *str in which that int will be placed in and the int num in which
	you want to convert to a string.
	*/

void cvtInt( char *str, int num){
    sprintf( str, "%d", num );
}

	/*
	Void handle is a function that runs after alarm timer is up.  The function
	will run after the specified time and send a signal to the CPU to kill the
	program.
	*/
void handle(int sig) {
    signal(SIGALRM, SIG_IGN);
    exit(1);			
    signal(SIGALRM, handle);
}//end handle


main(int argc, char *argv[]){
	
	int x;					//Holds fork's return value.
	pid_t child_pid;		//Holds the ID of the child process.
	int size = 0;			//Max size of ansArray.
	int calcSize = 0;		//Used to calculate the total size needed by the ansArray		
	int newCount = 0;    //Holds the last item in ansArray.
	char *ptr_1;  			//Allocate the pointer 1.
   char *ptr_2;			//Allocate the pointer 2.
	char **ptr_array;		//Pointer to an array of addresses of strings.
	int workerID;			//The ID num for the worker process.
	int workerAns;			//The return value of the worker process

	newCount = argc;		 //Holds  the position of the first empty spot after buffer input.
	calcSize = argc - 1;  //Used to calc the total number of spots need for additon.
	
	size = (2 *calcSize)  ; // Calculates the max size of ptr_array array.
	ptr_array = calloc(size, sizeof(char*));//Sets a pointer to a array  


	int i2 = 0;						//Puts buffer into ptr_array array.
	for(i2; i2 < argc; i2++){
		ptr_array[i2] = argv[i2];
	}//end for

	signal(SIGALRM, handle);   //Initiates the alarm.
   alarm(10); 						//Starts the alarm, after 10 seconds the program 
										//will automatically end.
	int inc = 1;
	while(inc < size){ //while there are number to add, add them.
			
		signal(SIGINT, sigproc); //Disables ctrl C and prints msg if pressed.
	
		if(inc == size -1){ //Last spot
			printf("Total: %s:\n", ptr_array[size - 1]);
			return 0;
		}//end if
	
		ptr_1 = ptr_array[inc];
		ptr_2 = ptr_array[inc+1];
	
		x = fork();
		if(x == -1){	//error in process	
			perror("Error: Fork Failed!\n");
		}//end if
		if(x == 0){ 	//child process
			execlp("./worker", "./worker", ptr_1, ptr_2, NULL); //run the program worker
		}//end if
		else{ 			//parents process
			child_pid = wait(&workerID);
			printf("Child process id is: ");
			printf("%d.\n", child_pid);
			if(WIFEXITED(workerID) != 0){					  //Child process eneded normally.
		   	workerAns=WEXITSTATUS(workerID);		     //Saves the result from the child process.
				ptr_array[newCount] =  malloc(10);		  //Creates new space in memory for the string.
				cvtInt( ptr_array[newCount], workerAns); //Stores the result of the addition into a string in ptr_array[index].
			   newCount = newCount+1;	
			}//end if				
			else{													  //Child process errored out.
				printf("Error in worker process!");
			}//end else
		}//end else
		inc=inc+2;

	}//end while

}//end main




