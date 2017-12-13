#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
   int number;
   pid_t pid;

   number = atoi(argv[1]);
 
   if (number <= 0) {
	printf("Please provide postive Number \n");	
	return -1;
    }

   pid = fork();

     if (pid < 0){
	printf("Unable to fork \n");
 	return -1;
     }else if (pid > 0){
	printf("waiting in Parent Process \n");

	wait(NULL);
     
     }else if (pid == 0){
        printf("Child Process \n");
	
	while(number != 1){
        	printf("%d \t",number);
    		if(number%2 == 0){
		        number = number/2;
    		}
    		else {
       			number = (3 * number) + 1;
    		}

    		if (number == 1) {
    		printf("%d \n",number);
    		 }
   	   }  
     }
  
   return 0;
}
