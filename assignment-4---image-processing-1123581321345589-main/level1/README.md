# Level1 README

Image Processing

In this assignment we will use the STB library to load and manipulate images. Write a program that uses the STB library
to manipulate an image (provided as a PNG file) and resample the colors of the image.

Each pixel is composed of color channels, and would commonly be red, green, and blue. This is called the 24-bit RGB
color scheme, since we have 3 colors with 1 byte (8 bits) each. In this scheme, a single pixel red dot would be
3 bytes: (255, 0, 0). A single green pixel would be (0, 255, 0), and a single blue pixel would be (0, 0, 255).

The pixels are then laid out as a 2D matrix, one for each pixel. So, a 2x2 pixel would be:

    [R0][G0][B0][R1][G1][B1][R2][G2][B2][R3][G3][B3]

For a total of 12 bytes (4 pixels, 3 bytes each).

Cnvert each pixel using the following equation on each channel of each pixel:

    if( channelValue > 127 ) {
        channelValue = 255;
    } else {
        channelValue = 0;
    }

This will modify the colors of the image to effectively use 3-bit RGB instead of the usual 24-bit RGB. In other words,
the colors will be converted to one of the following:

    RED     GREEN    BLUE
     0        0        0
     0        0       255
     0       255       0
     0       255      255
    255       0        0
    255       0       255
    255      255       0
    255      255      255

To summarize you program will:

1. Your program will load an image.
2. Manipulate each channel of each pixel in the image.
3. Save the image.

Your program should accept 2 arguments on the command line:

1. The input image filename.
2. The output image filename.

## STB Library

You will use the following two files from the library:

- stb_image.h
- stb_image_write.h 

The first file is used to load images and contains the `stbi_load` function and the `stbi_image_free` function that we
will be using. The second file is used to save images and contains the `stbi_write_png` function.

To load the PNG file, we need to use the `stbi_load` function. This function has the following signature:

    unsigned char* stbi_load(char* filename, int* p_width, int* p_height, int* p_channel, int unused);

The first argument is the filename to use, and is passed in through the first command-line argument. The second and
third arguments are output arguments to the width and height of the image. The 4th argument is the channel, which is
explained above. The last argument is unused and is always 0.

The STB library will load the PNG file contents and convert it so that the image data is load out like the description
above.

You can use the following code as an example:

    char* filename = "A.png";
    int width = 0;
    int height = 0;
    int channel = 0;
    unsigned char* data = stbi_load(filename, &width, &height, &channel, 0);

To save the PNG file, we use the `stbi_write_png` function. This function has the following signature:

    int stbi_write_png(char* filename, int width, int height, int channel, unsigned char* data, int row_length);

The first argument is the filename to use, and is passed in through the second command-line argument. The second and
third arguments are the width and height of the image, as explained above. The 4th argument is the channel, also
explained above. The 5th argument is the data to save, and the last argument is the number of bytes per row.

The STB library will save the image data to a PNG file.

You can use the following code as an example:

    char* filename = "out-A.png";
    int ret = stbi_write_png(filename, width, height, channel, data, width * channel);
    if (ret != 0) {
        printf("Error writing file\n");
        exit(1);
    }

Lastly, the STB library creates the image data on the heap, so we need to clean up after ourselves, as any model citizen
will do. Use the `stbi_image_free` function to do so.

## Test Cases

There will be 4 test cases provided.

### 1D Red Line

Convert a simple 1D (width 200, height 1) red image (colors in RGB: 237 28 36). Can be run using:

    ./level1 ../data/red_line.png out/red_line.out.png

Or by running ./test-red_line.sh

### 2D Red Box

Convert a simple 1D (width 64, height 48) red image (colors in RGB: 237 28 36). Can be run using:

    ./level1 ../data/red_box.png out/red_box.out.png

Or by running ./test-red_box.sh

### Assorted

Convert a more complicated image with assorted shapes. Can be run using:

    ./level1 ../data/A.png out/A.out.png

Or by running ./test-A.sh

### Pencils

Convert a more complicated image with various colored pencils. Can be run using:

    ./level1 ../data/pencils.png out/pencils.out.png

Or by running ./test-pencils.sh
