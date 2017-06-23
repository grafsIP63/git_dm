#include <fstream>
#include <iostream>

#define colorTable 1024

typedef struct
{
    int8_t  bfType[2];       // The characters "BM"
    int32_t bfSize;          // The size of the file in bytes
    int16_t bfReserved1;     // Unused - must be zero
    int16_t bfReserved2;     // Unused - must be zero
    int32_t bfOffBits;       // Offset to start of Pixel Data
    int32_t biSize;          // Header Size - Must be at least 40
    int32_t biWidth;         // Image width in pixels
    int32_t biHeight;        // Image height in pixels
    int16_t biPlanes;        // Must be 1 (для 24-бітних зображень)
    int16_t biBitCount;      // Bits per pixel - 1, 4, 8, 16, 24, or 32 ; 24 (для 24-бітних зображень)
    int32_t biCompression;   // Compression type (0 = uncompressed)
    int32_t biSizeImage;     // Image Size - may be zero for uncompressed images
    int32_t biXPelsPerMeter; // Preferred resolution in pixels per meter
    int32_t biYPelsPerMeter; // Preferred resolution in pixels per meter
    int32_t biClrUsed;       // Number Color Map entries that are actually used
    int32_t biClrImportant;  // Number of significant colors
} bmpHeader;

typedef struct 
{
    int8_t redComponent;
    int8_t greenComponent;
    int8_t blueComponent;
   // int8_t reserver = 0; 
} pixelData;              

typedef struct
{
    int x;
    int y;
} Q;

int getColor(pixelData pixel)
{
    return pixel.redComponent + pixel.greenComponent*256 + pixel.blueComponent*65536;
}

void setColor(pixelData &pixel , int RGBsumm)
{
    pixel.blueComponent = RGBsumm/65536;
    pixel.greenComponent = (RGBsumm - pixel.blueComponent*65536)/256;
    pixel.redComponent = RGBsumm - pixel.blueComponent*65536 - pixel.greenComponent * 256;
}

void setColor(pixelData &pixel , int r ,int g ,int b)
{
    pixel.redComponent = r;
    pixel.greenComponent = g;
    pixel.blueComponent = b;
}

void output(bmpHeader * bmp , pixelData ** pixels,int  zoom)
{
    int w = bmp -> biWidth;
    int h = bmp -> biHeight;
    pixelData ** newPixels = new pixelData * [h * zoom];
    for (int i = 0; i < h * zoom; i++)
    {
        newPixels[i] = new pixelData[w * zoom];
    }
    
    //************************************
    pixelData p;
    p.redComponent =0;
    p.greenComponent=0;
    p.blueComponent=0;
    for (int i = 0; i < h * zoom; i++)
    {
        for (int j = 0; j < w * zoom; j++) 
        {
            newPixels[i][j] = pixels[i / zoom][j / zoom];

        } 
    }
    
    pixelData nullpixel;
    nullpixel.redComponent = 0;
    nullpixel.blueComponent = 0;
    nullpixel.greenComponent = 0;
    int8_t t = 0;
    FILE *fd = fopen("Vitia.bmp","wb");
    bmp -> biWidth = w * zoom;
    bmp -> biHeight = h * zoom;
    fwrite(bmp, 1, 2, fd);
    fwrite(&(bmp -> bfSize) ,sizeof(bmpHeader) - 4, 1, fd);
    fseek(fd, bmp->bfOffBits, SEEK_SET);
    for (int i = 0; i < h*zoom; i++)
    {
       //fwrite(newPixels[i] , 3, w*zoom, fd);
       std::cout<<fwrite(newPixels[i] , 3, w*zoom, fd)*3<< std::endl;
       fwrite(&t, 1, (4-((w*zoom*3)%4))%4, fd);
    }
    
 
}

void interpoliationZOOM(bmpHeader *bmp , pixelData ** pixels , double zoom)
{
    
    int w = bmp -> biWidth;
    int h = bmp -> biHeight;
    int heigh = h * zoom;
    int width = w * zoom;
    pixelData ** newPixels = new pixelData*[heigh];
    for (int i = 0; i < heigh; i++)
    {
        newPixels[i] = new pixelData[width];
    }
    
    //**********************
            Q Q11;
            Q Q12;
            Q Q21;
            Q Q22;
            pixelData pixel;
            int color = 0;
    //*********************
    
    for(int i = 5; i < heigh - 5; i++)
    {
        for(int j = 5; j < width - 5; j++)
        {
            double xP = j / zoom;
            double yP = i / zoom; 
            
            Q11.x = xP;
            Q11.y = yP;
            Q12.x = xP+1;
            Q12.y = yP;
            Q21.x = xP;
            Q21.y = yP+1;
            Q22.x = xP+1;
            Q22.y = yP+1;
            
            int colorQ11R = pixels[Q11.y][Q11.x].redComponent;
            int colorQ21R = pixels[Q21.y][Q21.x].redComponent;
            int colorQ12R = pixels[Q12.y][Q12.x].redComponent;
            int colorQ22R = pixels[Q22.y][Q22.x].redComponent;
            
            int colorQ11G = pixels[Q11.y][Q11.x].greenComponent;
            int colorQ21G = pixels[Q21.y][Q21.x].greenComponent;
            int colorQ12G = pixels[Q12.y][Q12.x].greenComponent;
            int colorQ22G = pixels[Q22.y][Q22.x].greenComponent;
            
            int colorQ11B = pixels[Q11.y][Q11.x].blueComponent;
            int colorQ21B = pixels[Q21.y][Q21.x].blueComponent;
            int colorQ12B = pixels[Q12.y][Q12.x].blueComponent;
            int colorQ22B = pixels[Q22.y][Q22.x].blueComponent;
            
            
            
            // посмотри вывод
            double R1R = (Q22.x - xP)/(Q22.x - Q21.x)*colorQ21R + (xP - Q21.x)/(Q22.x - Q21.x)*colorQ22R;
            double R2R = (Q12.x - xP)/(Q12.x - Q11.x)*colorQ11R + (xP - Q11.x)/(Q12.x - Q11.x)*colorQ12R;
            
            double R1G = (Q22.x - xP)/(Q22.x - Q21.x)*colorQ21G + (xP - Q21.x)/(Q22.x - Q21.x)*colorQ22G;
            double R2G = (Q12.x - xP)/(Q12.x - Q11.x)*colorQ11G + (xP - Q11.x)/(Q12.x - Q11.x)*colorQ12G;
            
            double R1B = (Q22.x - xP)/(Q22.x - Q21.x)*colorQ21B + (xP - Q21.x)/(Q22.x - Q21.x)*colorQ22B;
            double R2B = (Q12.x - xP)/(Q12.x - Q11.x)*colorQ11B + (xP - Q11.x)/(Q12.x - Q11.x)*colorQ12B;
            
            int FPR = (Q11.y - yP)/(Q11.y - Q21.y)*R1R + (yP - Q21.y)/(Q11.y - Q21.y)*R2R; 
            int FPG = (Q11.y - yP)/(Q11.y - Q21.y)*R1G + (yP - Q21.y)/(Q11.y - Q21.y)*R2G;
            int FPB = (Q11.y - yP)/(Q11.y - Q21.y)*R1B + (yP - Q21.y)/(Q11.y - Q21.y)*R2B;// Не меняй пока что
            
            setColor(newPixels[i][j], FPR, FPG, FPB);
        }
    }
    
    FILE *fd = fopen("Vitia.bmp","wb");
    bmp -> biWidth = w * zoom;
    bmp -> biHeight = h * zoom;
    fwrite(bmp, 2, 1, fd);
    fwrite(&(bmp -> bfSize) ,1, sizeof(bmpHeader) - 4, fd);
    for (int i = 0; i < heigh; i++)
    {
        fwrite(newPixels[i] , 3, width, fd);
        fseek(fd, (4-((width*3)%4))%4, SEEK_CUR);
    }
}

void resize(char * filename, bmpHeader * bmp, double zoom)
{   
    FILE *fd = fopen(filename , "rb");
    fread(bmp, 1, 2, fd);
    bmp -> biSize = bmp -> biWidth*zoom + bmp -> biHeight*zoom + 54;
    fread(&(bmp -> bfSize) , 1, sizeof(bmpHeader) - 4, fd);
    int offset = bmp -> bfOffBits;
    int w = bmp -> biWidth;
    int h = bmp -> biHeight;
    pixelData ** pixels = new pixelData*[h];
    for (int i = 0; i < h; i++)
    {
        pixels[i] = new pixelData[w];
    }
    fseek(fd , offset , SEEK_SET);
    for (int i = 0; i < h; i++)
    {
       fread(pixels[i] , 3 , w, fd);
       fseek(fd, (4-((w*3)%4))%4, SEEK_CUR);
    }
    interpoliationZOOM(bmp, pixels , zoom);
}