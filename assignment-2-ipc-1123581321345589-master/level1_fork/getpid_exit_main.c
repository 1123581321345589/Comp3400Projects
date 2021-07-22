#include <unistd.h> // For getpid()
#include <stdio.h> // For printf

int main() {
    // TODO: Complete the main function
    int pid = getpid();
    printf("My PID is %d\n", pid);
    exit(42);
}
