/*
	Patrick Rawlings
	CSCI 4630
	Spring 2012
	Assignment 3
	4/20/12

	Description:  This program will simulate the behaviour of the UNIX
	command 'ls -l".  This UNIX command basically gives a long listing of the 
	files in a spcific directory.  It will produce one line of output for each
	file/directory in the directory.  This line will tell you the permission
	that the user, group and other have to read, write and execute the file, 
	the number of hardlinks to the file, the login name of the owner, the group
	name ot to which the file belings, the number of characters in the file
	the last time the file's contents were modified and last but not least,
	the name of the file/directory.  For example, some typcial lines are below.

	drwxr-xr-- 1 gopal staff  7783 Feb 19 09:57 junk
	-rw-r--r-- 1 gopal staff  18806 Feb 2 1998 zero.tex 

	I/O format: The program will run with no input to display the current 
	directory, and with a supplied command will output the specifed directory 

	Error Handling: You may assume that the current directory will not have 
	a text file named myls.txt   
	
	Compiler Instructions: Used g++ compiler. 

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <errno.h>

main(int argc, char *argv[]){

	//printf("Debug: Starting program...\n");

	struct dirent *dptr;		 //A structure type used to return information about directory entires.

	DIR *dirp;    				 //DIR represents a directory stream, which is and ordered sequence of all the 										 //directory entires in a particular directory.

	char directory [50];		//Holds the directory if the users inputs one as an argument.

	//create file
	FILE *dirFile;				
	dirFile = fopen("./myls.txt", "a+");	//"w" mean write.

	if(argc > 2){   			
	perror("Error!");
	return 1;
	}//end if
	if(argc == 1){
	dirp  = opendir(".");
	}//end if
	else{
	dirp = opendir(argv[1]);
	}//end else

	if(dirp==NULL){ 
	perror("Error");
	return 1;
	}//end if

	while(dptr=readdir(dirp)){

		struct stat fileStat; 	 //A structure type used to return data about a file inode. 
		//strcat(directory, dptr->d_name);

		if(argc == 1){
		  if(stat(dptr->d_name,&fileStat) < 0){    //No file path is given, use current directory.
				perror("Oh dear, your no file path errored out.\n");				
				return 1;
			}//end if
		}//end if
		else{													//File path was specified, append this path and use it.
			strcpy(directory, argv[1]);
			strcat(directory, "/");
			strcat(directory, dptr->d_name);
			if(stat(directory,&fileStat) < 0){
				perror("Oh no, your specified file path errored out.");
				return 1;
			}//end if
		}//end else

			if(!(strcmp(dptr->d_name,".") == 0 || strcmp(dptr->d_name,"..") == 0)){  //Gets rid of entries with ". in them.
			 	
			fprintf(dirFile, (S_ISDIR(fileStat.st_mode)) ? "d" : "-");					//Print the read/write info.
			fprintf(dirFile, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
			fprintf(dirFile, (fileStat.st_mode & S_IWUSR) ? "w" : "-");		
			fprintf(dirFile, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
			fprintf(dirFile, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
			fprintf(dirFile, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
			fprintf(dirFile, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
			fprintf(dirFile, (fileStat.st_mode & S_IROTH) ? "r" : "-");
			fprintf(dirFile, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
			fprintf(dirFile, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	
         fprintf(dirFile," ");
			//fprintf("%2d", fileStat.st_nlink);	
			fprintf(dirFile, "%d", fileStat.st_nlink);										//Print the link info.
			fprintf(dirFile," ");

			struct passwd *uid;   			  // User ID (uid)
			uid = getpwuid(fileStat.st_uid);
			//printf(" %s ", uid -> pw_name);
			fprintf(dirFile, uid -> pw_name);
			fprintf(dirFile," ");

			struct group *grp;
			grp = getgrgid(fileStat.st_gid);										
			//printf(" %s ", grp-> gr_name);
			fprintf(dirFile, grp-> gr_name);														//Print the name info.
			fprintf(dirFile," ");			

			//printf("%8d", (intmax_t)fileStat.st_size);
			fprintf(dirFile, "%d", fileStat.st_size);	
	
			struct tm *timeInfo;
			char datestring[256];

			timeInfo = localtime(&fileStat.st_mtime);
    		strftime(datestring, sizeof(datestring)," %Y-%m-%d %H:%M ", timeInfo); 

		   //printf(" \t\b\b\b\b\b\b%s", datestring);
			fprintf(dirFile, datestring);															//Print the time info.
			fprintf(dirFile,"\t");

 			//printf(" %4s", dptr->d_name);
			fprintf(dirFile, dptr->d_name);														//Print the name.
			fprintf(dirFile," ");

			fprintf(dirFile,"\n");
		}//end if
	}//end while
	fclose (dirFile); 
	closedir(dirp);
																			//After writing all the contents to the text file
	if(dirFile != NULL){												//sort the print out the result.
		fopen("./myls.txt", "r");	//"w" means write.
	}//end if
	else{
		perror("Error in opening file!");
	}//end else
	
	system("sort -f -t \"\t\" +1 myls.txt ");
	fclose(dirFile);
	system("rm myls.txt");

	//printf("Debug: Ending program...\n");

}//end main
