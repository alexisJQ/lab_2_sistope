#ifndef WRITE_IMAGE_H
   
    #define WRITE_IMAGE_H
    #define TRUE 1
    #define FALSE 0
    #include <stdint.h>
    void write_image(uint8_t* imagen,int width,int height,int bpp,char* convert, char* principalName,int showResults, int classified);

#endif