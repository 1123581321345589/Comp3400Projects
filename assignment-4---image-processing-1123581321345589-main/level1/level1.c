/*
Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) is licensed under a Creative Commons
Attribution-NonCommercial 3.0 Unported License (http://creativecommons.org/licenses/by-nc/3.0/).
*/
//
// This program uses the STB library (http://nothings.org/)
// which points to the code at: https://github.com/nothings/stb
//
// You need to download the following two file:
//	a) stb_image.h         to load images
//	b) stb_image_write.h   to write images
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

/**
 * TODO: Describe this function.
 *
 * @param data
 * @param width
 * @param height
 * @param channels:
 */
void convert_image(unsigned char* data, int width, int height, int channels) {

for(int i = 0; i < width * height * channels; i = i + 1) {
if(data[i] > 127) {
data[i] = 255;
}
else {
data[i] = 0;
}

}

}

/**
 * TODO: Describe what command-line arguments are used
 */
int main(int argc, char *argv[]) { 

    char* filename = argv[1];
    char* fileout = argv[2];
    
    int height = 0; int width = 0; int channel = 3;
  
    // TODO: Use stbi_load
    unsigned char* data = stbi_load(filename, &width, &height, &channel, 0);
    // TODO: call convert_image
    convert_image(data, width, height, channel);
    // TODO: Use stbi_write_png
    int row = channel * width;
    // TODO: Use stbi_image_free
    int ret = stbi_write_png(fileout, width, height, channel, data, row);
    
	return ret;
}
