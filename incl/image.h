#ifndef IMAGE_H

    #define IMAGE_H

    image_data* RGB_read_image(image_data* data); 
    void write_image(image_data* data, bool show_results);
    int convert_gray_scale(int R, int G, int B);
    image_data* convert_binary(image_data* data, int umbral);
    image_data* convert_laplacian(image_data* data, char* mask_file_name);
    image_data* classified_image (image_data* data,int threshold_classify);
    void write_image_2(int width, int height, char str[100], uint8_t* data);

#endif

