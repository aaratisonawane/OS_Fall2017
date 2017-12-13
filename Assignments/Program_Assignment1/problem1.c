 #include <sys/types.h>
 #include <stdio.h>
 #include <unistd.h>
 
int main()
{
   pid_t pid, pid1;
   /* fork a child process */
   pid = fork();

   if (pid < 0) { 
     /* error occurred */
     fprintf(stderr, "Fork Failed");
     return 1;
     }
   else if (pid == 0) { 
     /* child process */
     printf("Child process \n");
     exit(0);
    }
    else { 
     /* parent process */
     printf("Parent process \n");
     sleep(10);
    }
       return 0;
}
