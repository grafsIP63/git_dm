#include <stdint.h>
#include <iostream>
#include "Headers/bmp.h"

/*
**************************************
int8_t  : 1 byte
int16_t : 2 byte
int32_t : 4 byte
int64_t : 8 byte
**************************************
*/

int main(int argc, char* argv[]) 
{
    bmpHeader* bmp= new bmpHeader;
    char filename[] = "sample.bmp";
    resize(filename, bmp, 4);
    printf ("OFFSET: %d\n",bmp->bfOffBits);
    printf ("IMAGE HEADER: %d",bmp->biSize);
    return 0;
}