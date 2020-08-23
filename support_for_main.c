#include "../incl/Support_for_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void get_values_from_command(int argc, char* argv[], int* numb_images, int* threshold_binarize, int* threshold_classify, char** mask_file_name, int* show_results){
    int c;
    while((c = getopt(argc, argv, "c:u:n:m:b")) != -1){
        switch (c)
        {
        case 'c':
            *numb_images = atoi(optarg);
            break;
        
        case 'u':
            *threshold_binarize = atoi(optarg);
            break;
        
        case 'n':
            *threshold_classify = atoi(optarg);
            break;

        case 'm':
            *mask_file_name = optarg;
            break;

        case 'b':
            *show_results = TRUE;
            break;
        }
    }

    return;
}

char* got_name(int number_image, char* name){
    
    if(name  != NULL){
        free(name);
    }
    
    name = malloc(35 * sizeof(char));
    char* number = malloc(10 * sizeof(char));
    
    for (int i = 0; i < 35; i ++){
        name[i] = '\0'; 
    }
    
    for (int j = 0; j < 10; j ++){
        number[j] = '\0';
    }

    sprintf(number, "%d", number_image);

    
    strcat(name, "imagen_");
    strcat(name, number);
    

    free(number);
    return name;
}