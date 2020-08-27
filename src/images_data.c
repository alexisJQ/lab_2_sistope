#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../incl/stb_image.h"
#include "../incl/images_data.h"


//Input: empty Struct of image data, and char* name, with the name of the file to open
//Output: Update of list with the info of the images, with the name of the file 
//Function: Generate a new node to the list
image_data* insert_in_list(image_data* data, char* name){
    
    // memory allocation, tomsave the image data
    image_data* new_node = malloc(sizeof(image_data));

    // save the info of the image in the list, with NULL or 0 values
    new_node->width = 0;
    new_node->height = 0;
    new_node->bpp = 0;
    new_node->nearly_black = 0;
    new_node->image_name = name;
    new_node->principal_image = NULL;
    new_node->gray_image = NULL;
    new_node->laplacian_image = NULL;
    new_node->binary_image = NULL;
    new_node->next = NULL;
    
    // return the new node or the list of the image in the pipeline 
    if (data == NULL){
        data = new_node;
    }
    else{
        new_node->next = data;
        data = new_node;
    }

    return data;
}

//Input: strcut of image data
//Output: NULL pointer
//Function: free the memory of the allocated memory from the list
image_data* erase_list(image_data* data){

    // verify data in the list
    if (data == NULL){
        return NULL;
    }
    

    image_data* aux = data;
    while (aux != NULL){

        data = data->next;
        // free the image data in the list
        stbi_image_free(aux->principal_image);
        free(aux->gray_image);
        free(aux->laplacian_image);
        free(aux->binary_image);
        free(aux);

        aux = data;    
    }

    return data;
}

void show_data_list(image_data* data){
    if (data == NULL){
        return;
    }
    do{
        printf("%d %d %d %d %s ", data->width, data->height, data->bpp, data->nearly_black, data->image_name);
        if(data->principal_image != NULL){
            printf("principal_image ");
        }
        if(data->gray_image != NULL){
            printf("gray_image ");
        }
        if(data->laplacian_image != NULL){
            printf("laplacian_image ");
        }
        if(data->binary_image != NULL){
            printf("binary_image");
        }
        printf("\n");
        data = data->next;
    }while(data != NULL);
    return;
}