# Level2 README

Parallel Image Processing

In this assignment we will use threads to distribute the image processing among multiple threads. The basic idea of
the program will be identical to level1, but now we accept an additional command line argument: the number of
threads to use.

Using the code from level1 as the starting point, modify it to create threads and distribute rows to each thread. If the
rows are not dividable by N, then give slightly less to the last thread. For example, if you have an image with 48 rows,
give each thread 12 rows. If you have an image with 45 rows, however, you can give 3 threads 12 rows and the last one 9
rows. Note that in this case you need to make sure the last thread does *not* process 12 rows and *not* step outside the
buffer.

To summarize you program will:

1. Your program will load an image.
2. Your program will create N-1 threads.
3. Distribute equal number of rows to each thread (except for the last one).
4. Manipulate each channel of each pixel in the image.
5. Wait for everyone to complete the work.
6. Save the image.

Your program should accept 3 arguments on the command line:

1. The input image filename.
2. The output image filename.
3. The number of threads to use.

## Test Cases

There will be 12 test cases provided.

### 2D Red Box with 1 thread

Convert a simple 1D (width 64, height 48) red image (colors in RGB: 237 28 36). Can be run using:

    ./level2 1 ../data/red_box.png out/red_box-1.out.png

Or by running ./test-red_box-1.sh

### 2D Red Box with 2 threads

Convert a simple 1D (width 64, height 48) red image (colors in RGB: 237 28 36). Can be run using:

    ./level2 2 ../data/red_box.png out/red_box-2.out.png

Or by running ./test-red_box-2.sh

### 2D Red Box with 4 threads

Convert a simple 1D (width 64, height 48) red image (colors in RGB: 237 28 36). Can be run using:

    ./level2 4 ../data/red_box.png out/red_box-4.out.png

Or by running ./test-red_box-4.sh

### Assorted with 1 thread

Convert a more complicated image with assorted shapes. Can be run using:

    ./level2 1 ../data/A.png out/A.out.png

Or by running ./test-A-1.sh

### Assorted with 2 threads

Convert a more complicated image with assorted shapes. Can be run using:

    ./level2 2 ../data/A.png out/A.out.png

Or by running ./test-A-2.sh

### Assorted with 4 threads

Convert a more complicated image with assorted shapes. Can be run using:

    ./level2 4 ../data/A.png out/A.out.png

Or by running ./test-A-4.sh

### Pencils with 1 thread

Convert a more complicated image with various colored pencils. Can be run using:

    ./level2 1 ../data/pencils.png out/pencils.out.png

Or by running ./test-pencils-1.sh

### Pencils with 2 threads

Convert a more complicated image with various colored pencils. Can be run using:

    ./level2 2 ../data/pencils.png out/pencils.out.png

Or by running ./test-pencils-2.sh

### Pencils with 4 threads

Convert a more complicated image with various colored pencils. Can be run using:

    ./level2 4 ../data/pencils.png out/pencils.out.png

Or by running ./test-pencils-4.sh
