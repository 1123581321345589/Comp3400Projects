#include <unistd.h> // For getpid()
#include <stdio.h> // For printf
#include <sys/wait.h> // For wait()

int main(int argc, char* argv[]) {
    char* args[] = {"-q", argv[1], argv[2], argv[3]};
    int ret = execv("/usr/bin/diff", args);
  
    if(ret == -1){
    printf("Error in exec");
}
    return ret;
}
