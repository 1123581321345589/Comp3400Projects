#include <stdio.h> // For printf

int main(int argc, char* argv[]) {
    if(argc == 0){ 
    return 0;
    }
    else if(argc == 1){
    printf("argc: %d\n", argc);
    printf("argv[0]: %s\n", argv[0]);
    }
    else if(argc ==2){
    printf("argc: %d\n", argc);
    printf("argv[0]: %s\n", argv[0]);
    printf("argv[1]: %s\n", argv[1]);
    printf("argv[2]: %s\n", argv[2]);
    }
    
    return 0;
}
