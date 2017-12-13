#include <stdio.h>
#include <stlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(){
	/* the size (in bytes) of shared memory object */
	const int SIZE 4096;
	/* name of the shared memory object */
	const char *name = "OSPoblem3";
	/* shared memory file descriptor */
	int shm_fd;
	/* pointer to shared memory obect */
	void *ptr;
	int number;
	static int count = 0;
    
	printf("Please enter a number \n");
    scanf("%d", &number);
	if(number < 0)
    {
		printf("Please enter a positive number, greather than 0 \n");
        scanf("%d", &number);
    }
	if(number > 0){
	pid_t pid;
	/* fork a child process */
	pid = fork();
	
	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		return 1;
	}else if (pid == 0) {	/* child process */
	int shm_fd;
        void *ptr;
        shm_fd = shm_open(name, O_RDWR, 0666);
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

        sprintf(ptr, "%d", number);
        ptr += sizeof(int);
        count ++;
	
	while(number != 1){
        printf("%d \t",number);
    if(number%2 == 0)
    {
        number = number/2;
    }
    else
    {int shm_fd;
        void *ptr;
        shm_fd = shm_open(name, O_RDWR, 0666);
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

        sprintf(ptr, "%d", num);
        ptr += sizeof(int);
        count ++;
       number = (3 * number) + 1;
    }

    if (number == 1){
    printf("%d ",number);
   }
   }
   }else { /* parent process */
	/* parent will wait for the child to complete */
	wait(NULL);
	/* open the shared memory object */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	/* memory map the shared memory object */
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	/* read from the shared memory object */
	int *p = (int*) ptr;
        printf("%d ", *p++);
        while(count > 0){
            printf("%d ",*p++);
            count --;
        }
	/* remove the shared memory object */
	shm_unlink(name);
	printf("Child Complete");
	}
	return 0;
}
	
 
    