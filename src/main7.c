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
    char namePri[100]="imagen_1_output.jpg";
    int numb_images = 1;
    int threshold_binarize = 100;
    int threshold_classify = 100;
    char mask_file_name[20];
    int show_results = 0;
    
    // data of the image 
    char image_name[100];
    char str[100];
    int width = 0;
    int height = 0;
    int aux = 0;
    uint8_t* image = NULL;

    // get global values
    read(STDIN_FILENO, str, 100);
    sscanf(str, "%s %d %d %d %d", mask_file_name,  &threshold_binarize, &threshold_classify, &numb_images, &show_results);
      for (int i = 1; i <= numb_images; i++){
        read(STDIN_FILENO, image_name, 100); // get name of the image
        
        read(STDIN_FILENO, str, 100); // get dimension of the image
        sscanf(str, "%d %d", &width, &height);

        image = (uint8_t*)malloc(sizeof(uint8_t) * width * height);

        for (int pos = 0; pos < width * height; pos ++){
            read(STDIN_FILENO, str, 100); // get pixel
            sscanf(str, "%d", &aux);
            image[pos] = aux;
        }

        write_image_2(width, height, image_name, image);
        if(show_results==1){
            read(STDIN_FILENO, str, 100); // get pixel
            sscanf(str, "%d", &aux);
            if(strcmp(namePri,image_name)==0){
               printf("\n| image    | nearly black |\n|----------|--------------|\n");
                
            }
            if(aux==1){
                    printf("| %s |     yes      |\n",image_name);
                }
                else{
                    printf("| %s |     no       |\n",image_name);
                }

        }
        free(image);
    }
    exit(0);
}
