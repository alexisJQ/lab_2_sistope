#ifndef SUPPORT_FOR_MAIN_H
    
    #define SUPPORT_FOR_MAIN_H
    #define TRUE 1
    #define FALSE 0

    char* got_name(int number_image, char* name);
    void get_values_from_command(int argc, char* argv[], int* numb_images, int* threshold_binarize, int* threshold_classify, char** mask_file_name, int* show_results);


#endif