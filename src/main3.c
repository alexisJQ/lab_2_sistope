#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../incl/support_for_main.h"
#include "../incl/images_data.h"
#include "../incl/image.h"

#define READ 0
#define WRITE 1

int main(int argc, char const *argv[])
{   

    // data from command
    int numb_images = 1;
    int threshold_binarize = 100;
    int threshold_classify = 100;
    char mask_file_name[20];
    int show_results = 0;
    char image_name[100];
    char str[100];
    int width = 0;
    int height = 0;
    int bpp = 0;
    uint8_t* gray_scale;
    int aux = 0;
    int sum = 0;

    // get global values
    read(STDIN_FILENO, str, 100);
    sscanf(str, "%s %d %d %d %d", mask_file_name,  &threshold_binarize, &threshold_classify, &numb_images, &show_results);
    
    for(int i = 1; i <= numb_images; i ++){
        
        read(STDIN_FILENO, image_name, 100); // get name of the image
        read(STDIN_FILENO, str, 100); // get dimension of the image
        sscanf(str, "%d %d %d", &width, &height, &bpp);

        gray_scale = (uint8_t*)malloc(sizeof(uint8_t)*width*height);
        int pos = 0;

        // get gray scale of the image
        for (int i = 0; i < width * height * bpp; i++){
            read(STDIN_FILENO, str, 100); // get pixel
            sscanf(str, "%d", &aux);
            if (i % 3 == 0){
                sum += aux * 3 / 10;
            }
            else if (i % 3 == 1){
                sum += aux * 59 / 100;
            }
            else if (i % 3 == 2){
                sum += aux * 11 / 100;
                gray_scale[pos] = sum;
                sum = 0;
                pos += 1;
            }

		}
        write_image_2(width, height, image_name, gray_scale);
        free(gray_scale);
        
    }
    exit(0);
}
