#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../incl/images_data.h"
#include "../incl/stb_image_write.h"
#include "../incl/stb_image.h"
#include "../incl/image.h"

//Input: empty Struct of image data
//Output: Update of image data, with the RGB info to analyse
//Function: Read a image and save this in struct
image_data* RGB_read_image(image_data* data){
    char* name = malloc(sizeof(char) * 35);
    for(int i = 0; i < 35; i++){
        name[i] = '\0';
    }
    strcpy(name, data->image_name);
    int width = 0, height = 0, bpp = 0;
    uint8_t* rgb_image = stbi_load(strcat(name, ".jpg"), &width, &height, &bpp, 3);
    data->principal_image = rgb_image;
    data->width = width;
    data->height = height;
    data->bpp = bpp;
    
    free(name);
    return data;
}
/*
Input: 
    > int R: intensity of the red color in the pixel
    > int G: intensity of the green color in the pixel
    > int B: intensity of the blue color in the pixel
Output:
    > int sum: grayscale pixel value
Function: Apply Y=R∗0.3 +G∗0.59 +B∗0.11 on pixels and transform RGB on one channel (gray scale)
*/
int convert_gray_scale(int R, int G, int B){
        
    int sum = 0;
    sum += R*0.3;
    sum += G*0.59;
    sum += B*0.11;
    return sum;
}

//Input: Struct with a image data and int Umbral (depending on threshold) 
//Output: Struct updated with binary filter applied
//Function: Transform pixels to 0 or 255 depending on threshold
image_data* convert_binary(image_data* data, int umbral){
    data->binary_image = malloc((data->width * data->height) * sizeof(uint8_t));
    
    // loop through the image array
    for(int i = 0; i < data->width * data->height; i++ ){
       if(data->laplacian_image[i] > umbral){
           data->binary_image[i] = 255;
       }
       else{
           data->binary_image[i] = 0;
       }
    }
    return data;
}

//Input: Struct with a image data and file name of the mask
//Output: New Sttruct with apply mask on data image 
//Function: Apply the mask on input data image
image_data* convert_laplacian(image_data* data, char* mask_file_name){
    
    FILE* mask_file = fopen(mask_file_name, "r");
    data->laplacian_image = malloc((data->width * data->height) * sizeof(uint8_t));
    int** image = malloc(data->height * sizeof(int*));
    int k = 0;
    int mask[3][3];
    int x = 0;  

    // the array of the image convert to matrix
    for (int i = 0; i < data->height; i++){
        image[i] = malloc(data->width * sizeof(int));
        for (int j = 0; j < data->width; j++){
            image[i][j] = data->gray_image[k];
            k++;
        }
    }

    // get values of the mask
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            fscanf(mask_file, "%d", &x);
            mask[i][j] = x;
        }
    }

    k = 0;
    for(int i = 0; i < data->height; i++){
        for (int j = 0; j < data->width; j++){
            int sum = 0;
            if ( i == 0){                               // upper edge case
                if (j == 0){                            // upper left corner case
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][2] * image[i][j + 1];
                    sum += mask[2][1] * image[i + 1][j];
                    sum += mask[2][2] * image[i + 1][j + 1];
                }
                else if (j + 1 == data ->width){        // upper right corner case
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][0] * image[i][j - 1];
                    sum += mask[2][1] * image[i + 1][j];
                    sum += mask[2][0] * image[i + 1][j - 1];
                }
                else{
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][2] * image[i][j + 1];
                    sum += mask[2][1] * image[i + 1][j];
                    sum += mask[2][2] * image[i + 1][j + 1];
                    sum += mask[2][0] * image[i + 1][j - 1];
                    sum += mask[1][0] * image[i][j - 1];
                }
            }
            else if ( i + 1 == data->height){           // lower edge case
                if (j == 0){                            // lower left corner case
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][2] * image[i][j + 1];
                    sum += mask[0][2] * image[i - 1][j + 1];
                    sum += mask[0][1] * image[i - 1][j];
                }
                else if (j + 1 == data ->width){        // lower right corner case
                    sum += mask[1][1] * image[i][j];
                    sum += mask[0][1] * image[i - 1][j];
                    sum += mask[0][0] * image[i - 1][j - 1];
                    sum += mask[1][0] * image[i][j - 1];
                }
                else{
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][2] * image[i][j + 1];
                    sum += mask[0][2] * image[i - 1][j + 1];
                    sum += mask[0][1] * image[i - 1][j];
                    sum += mask[0][0] * image[i - 1][j - 1];
                    sum += mask[1][0] * image[i][j - 1];
                }
            }
            else if (j == 0){                           // left edge case
                sum += mask[1][1] * image[i][j];
                sum += mask[0][1] * image[i - 1][j];
                sum += mask[0][2] * image[i - 1][j + 1];
                sum += mask[1][2] * image[i][j + 1];
                sum += mask[2][2] * image[i + 1][j + 1];
                sum += mask[2][1] * image[i + 1][j];
            }
            else if (j + 1 == data->width){             // right edge case
                sum += mask[1][1] * image[i][j];
                sum += mask[0][1] * image[i - 1][j];
                sum += mask[0][0] * image[i - 1][j - 1];
                sum += mask[1][0] * image[i][j - 1];
                sum += mask[2][0] * image[i + 1][j - 1];
                sum += mask[2][1] * image[i + 1][j];
            }
            else{
                sum += mask[1][1] * image[i][j];
                sum += mask[1][2] * image[i][j + 1];
                sum += mask[0][2] * image[i - 1][j + 1];
                sum += mask[0][1] * image[i - 1][j];
                sum += mask[0][0] * image[i - 1][j - 1];
                sum += mask[1][0] * image[i][j - 1];
                sum += mask[2][0] * image[i + 1][j - 1];
                sum += mask[2][1] * image[i + 1][j];
                sum += mask[2][2] * image[i + 1][j + 1];
            }
            data->laplacian_image[k] = sum;
            k ++;
        }
    }

    // allocated memory freee
    for (int i = 0; i < data->height; i++){
        free(image[i]);
    }
    free(image);
    fclose(mask_file);
    return data;
}

//Input: Struct with a data image and threshold for classify
//Output: Change in the struct of data image 
//Function: Classify the nearly black of image
image_data* classified_image (image_data* data, int threshold_classify){
    int i=0;
    int j=0;
    int height=data->height;
    int width=data->width;
    int cantidad=0;
    uint8_t* image=data->binary_image;
    for ( i = 0; i < height*width; i++){
        if(image[i]==0){
            cantidad+=1;
        }
        
    }
     int porcentaje = (cantidad*100)/(height*width) ;

    if (porcentaje >= threshold_classify)
    {
        data->nearly_black=1;
        return data;
    }

    else
    {   
        data->nearly_black=0;
        return data; 
    }
    
    
    
    

}

//Input: Struct with image data and boolen for the show or not the results
//Output: nothing
//Function: Write image and print or not the results
void write_image(image_data* data, bool show_results){
    char* name = malloc(sizeof(char) * 35);
    for(int i = 0; i < 35; i++){
        name[i] = '\0';
    }
    
    //strcpy(name, data->image_name);
    //stbi_write_jpg(strcat(name, "_gray.jpg"), data->width, data->height, 1, data->gray_image, 100);
    strcpy(name, data->image_name);
    stbi_write_jpg(strcat(name, "_output.jpg"), data->width, data->height, 1, data->binary_image, 100);
    //strcpy(name, data->image_name);
    //stbi_write_jpg(strcat(name, "_laplacian.jpg"), data->width, data->height, 1, data->laplacian_image, 100);
    if(show_results){
        
        if(strcmp(data->image_name, "imagen_1") == 0){
            printf("| image    | nearly black |\n|----------|--------------|\n");
        }
        if (data->nearly_black==1){
            printf("| %s |     yes      |\n",data->image_name);
        }

        else{
            printf("| %s |     no       |\n",data->image_name);
    
        }
        
    }
    free(name);
    return;

}

void write_image_2(int width, int height, char str[100], uint8_t* data){
    stbi_write_jpg(strcat(str, "_output.jpg"), width, height, 1, data, 100);
}