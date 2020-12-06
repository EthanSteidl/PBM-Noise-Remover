# PBM-Noise-Remover
Removes pixilated noise from PBM images

## Description

Takes black and white PBM images (P1 format) and removes pixel noise using the Grahm's Scan
algorithm. This has a run-time of N lg2 N where N is the amount of pixels

## Usage

Refer to main.cpp for usage. The constructor of rthe image reducer is called passing in a filename.
Next the user enters a threshold value for wich to remove pixelation. The threshold value is a 
double between the values 0.0 and 1.0 inclusive. The algorithm will check to see if there is another
pixel within threshold% of the closest pixels to the current pixel. If there is no others, the pixel
is removed.
