#ifndef IMAGES_DATA_H

    #define IMAGES_DATA_H


    typedef struct image_data{
        int width;
        int height;
        int bpp;
        int nearly_black;
        char* image_name;
        uint8_t* principal_image;
        uint8_t* gray_image;
        uint8_t* laplacian_image;
        uint8_t* binary_image;
        struct image_data* next;
    }image_data;

    image_data* insert_in_list(image_data* data, char* name);
    image_data* erase_list(image_data* data);
    void show_data_list(image_data* data);

#endif