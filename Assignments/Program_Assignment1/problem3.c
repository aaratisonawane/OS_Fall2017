#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>

int main(int argc, char *argv[])
{
   int number;
   number = atoi(argv[1]);
   if (number <= 0) {
     printf("Please provide postive Number \n"); 
     return -1;
    }

  const char *name = "OSProblem3";
  const int SIZE = 4096;
  int shm_fd;
  void *ptr;

  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  
  if (shm_fd == -1) {
	    printf("Shared memory failed: %s\n", strerror(errno));
	    exit(1);
  }
	
  ftruncate(shm_fd, SIZE);
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

  pid_t pid;
  pid = fork();

  if (pid < 0){
	  printf("Unable to fork \n");
 	  return -1;
  }else if (pid > 0){
	  printf("waiting in Parent Process \n");
	  wait(NULL);
    printf("In Parent process = \n");
    printf("%s\n", (char*) ptr);
	  shm_unlink(name);
     
  }else if (pid == 0){
    printf("In Child Process \n");
    shm_fd = shm_open(name, O_RDWR, 0666);
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
    while(number != 1){
	    printf("%d \t",number);
      ptr += sprintf(ptr, "%d ", number);

    	if(number%2 == 0){
		        number = number/2;
    		}
    		else{
       			number = (3 * number) + 1;
    		}

    	if (number == 1) {
    		printf("%d \n",number);
		    ptr += sprintf(ptr, "%d ", number);
    	}
   	}  
  } 
 return 0;
}
