#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void wastesometime(int n);
void prtastr(const char *s, int fd, int n);


int main(int argc,  char *argv[ ]) {
   pid_t childpid;             /* indicates process should spawn another     */
   int error;                  /* return value from dup2 call                */
   int fd[2];                  /* file descriptors returned by pipe          */
   int i;                      /* number of this process (starting with 1)   */
   int nprocs;                 /* total number of processes in ring          */ 
   
   char buffer[50];
   int n = 0;
   /* check command line for a valid number of processes to generate */
   if ( ((argc != 2) && (argc != 3)) || ((nprocs = atoi (argv[1])) <= 0) || ((n = atoi (argv[2])) <= 0 )) {
       fprintf (stderr, "Usage: %s nprocs\n", argv[0]);
       return 1; 
   }  
   if (pipe (fd) == -1) {      /* connect std input to std output via a pipe */
      perror("Failed to create starting pipe");
      return 1;
   }
   if ((dup2(fd[0], STDIN_FILENO) == -1) ||
       (dup2(fd[1], STDOUT_FILENO) == -1)) {
      perror("Failed to connect pipe");
      return 1;
   }
   if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
      perror("Failed to close extra descriptors");
      return 1; 
   }        
   for (i = 1; i < nprocs;  i++) {         /* create the remaining processes */
      if (pipe (fd) == -1) {
         fprintf(stderr, "[%ld]:failed to create pipe %d: %s\n",
                (long)getpid(), i, strerror(errno));
         return 1; 
      } 
      if ((childpid = fork()) == -1) {
         fprintf(stderr, "[%ld]:failed to create child %d: %s\n",
                 (long)getpid(), i, strerror(errno));
         return 1; 
      } 
      if (childpid > 0)               /* for parent process, reassign stdout */
          error = dup2(fd[1], STDOUT_FILENO);
      else                              /* for child process, reassign stdin */
          error = dup2(fd[0], STDIN_FILENO);
      if (error == -1) {
         fprintf(stderr, "[%ld]:failed to dup pipes for iteration %d: %s\n",
                 (long)getpid(), i, strerror(errno));
         return 1; 
      } 
      if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
         fprintf(stderr, "[%ld]:failed to close extra descriptors %d: %s\n",
                (long)getpid(), i, strerror(errno));
         return 1; 
      } 
      if (childpid)
         break;
   }   
   /* say hello to the world */
   sprintf(buffer, "This is process %d with ID %ld and parent id %ld\n",
           i, (long)getpid(), (long)getppid());
   prtastr(buffer,STDERR_FILENO,n);
   return 0; 
}     

void prtastr(const char *s, int fd, int n){
   int i = 0;
   while (s[i] != '\0') {
      write (fd, &s[i++], 1);
      wastesometime(n);
   }
}

void wastesometime(int n) {
   static volatile int dummy = 0;
   int i;
   for (i=0; i < n; i++)
      dummy++;
}