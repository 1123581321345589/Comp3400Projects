#include <unistd.h> // For getpid()
#include <stdio.h> // For printf
#include <sys/wait.h> // For wait()

int main() {

int pid = fork();

if(pid > 0) {

int status = 0;
wait(&status);

status = WEXITSTATUS(status);

printf("I'm the parent. Their PID is %d\n", pid);
printf("Child's status is %d\n", status);

exit(status);
}
else if(pid < 0){ 
exit(1);
}
else{
printf("Child process PID is %d\n", getpid());
exit(42);
}

return 0;
}
