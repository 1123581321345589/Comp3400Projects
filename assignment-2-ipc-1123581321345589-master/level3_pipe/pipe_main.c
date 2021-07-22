#include <unistd.h> // For getpid()
#include <stdio.h> // For printf
#include <sys/wait.h> // For wait()


struct time {
int seconds;
int milli;
};

int main() {
    
    struct time t1;
    int timeA[2];
    pipe(timeA);
    int read_fd = timeA[0];
    int write_fd = timeA[1];
    
    int pid = fork();
    
    if(pid == 0){
close(read_fd);
struct time t1 = {.seconds = 10, .milli = 500};
write(write_fd, &t1, sizeof(t1));
exit(0);
}
else{
close(write_fd);
struct time t0;
read(read_fd, &t0, sizeof(t0));
printf("Child results\n");
printf("%d seconds %d milli-seconds\n", t0.seconds, t0.milli);
}

}

