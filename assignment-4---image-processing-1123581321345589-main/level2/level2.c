/*
Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) is licensed under a Creative Commons
Attribution-NonCommercial 3.0 Unported License (http://creativecommons.org/licenses/by-nc/3.0/).
*/
//
// This program uses the STB library (http://nothings.org/)
// which points to the code at: https://github.com/nothings/stb
//
// You need to download the following two file:
// a) stb_image.h         to load images
// b) stb_image_write.h   to write images
//
// This library enables you to load images (png, jpg, etc).
// You can then manipulate the images at the pixel level.
// Then you can save the pixels as an image.
//
#include <stdio.h>
#include <pthread.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma GCC diagnostic pop

/** Holds the data of the entire image, and start and end indexes for each thread
 *
 */
struct threadArg {
    unsigned char* data; int start; int end;
};


/**
 * TODO: Describe this function. In particular, focus on how work is distributed
 * among threads.
 *
 * @param args
 * args contains a threadArg struct for each thread to change. Work is the same as level1, except the .start and .end of struct is used
 * @returns NULL
 */
void *threadFunc(void *args) {

	struct threadArg* thread = (struct threadArg*)args;

	for(int i = (*thread).start; i < (*thread).end; i++){

		if( (*thread).data[i] > 127 ) {
    			(*thread).data[i] = 255;
		}
		else {
    			(*thread).data[i] = 0;
		}

	}

	pthread_exit(NULL);

}


/**
 * TODO: Describe what command-line arguments are used
 * Argv[1] is the input file
 * Argv[2] is the output file
 * Argv[3] is the number of threads
 *
 */
int main(int argc, char *argv[]) {
   
    char* inputname = argv[1];
    char* outputname = argv[2];
   
    int nThreads = atoi(argv[3]);
    pthread_t tid[nThreads-1];

    int width = 0;
    int height = 0;
    int channel = 3;
   
    unsigned char* huh= stbi_load(inputname, &width, &height, &channel, 0);
   
    int row_length = channel * width;
   
    struct threadArg args[nThreads];
   
    int start = 0;
    int end = (height / nThreads) * row_length;
   
    if( height % nThreads == 0){
   
    for(int i = 0; i < nThreads ; i++){
   
    args[i].data = huh;
    args[i].start = start;
    args[i].end = end;
   
    pthread_create(&tid[i],NULL, threadFunc, &args[i]);
    pthread_join(tid[i], NULL);

    start = end;
    end = start + (height / nThreads) * row_length;
   
   
    }
   
    }
   
    else{
   
    for(int i = 0; i < nThreads; i++){
   
    if ( i == nThreads - 1 ) {
    args[i].data = huh;
    args[i].start = start;
    args[i].end = start + (height / nThreads) * row_length;
   
    pthread_create(&tid[i],NULL, threadFunc, &args[i]);
    pthread_join(tid[i], NULL);
   
    }
    else{
   
    args[i].data = huh;
    args[i].start = start;
    args[i].end = end;
   
   
    pthread_create(&tid[i],NULL, threadFunc, &args[i]);
    pthread_join(tid[i], NULL);

    start = end;
    end = start + (height / nThreads) * row_length;

    }
   
    }
   
    }
  
   int ret = stbi_write_png(outputname, width, height, channel, huh ,row_length);
   
   stbi_image_free(huh);
   
   return ret;
   
}
