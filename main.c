#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "../incl/Support_for_main.h"
#include "../incl/images_data.h"
#include "../incl/image.h"

int printStartClassify= 1;

int main(int argc, char* argv[])
{
    // data from command
    int numb_images = 1;
    int threshold_binarize = 100;
    int threshold_classify = 100;
    char* mask_file_name = NULL;
    int show_results = 0;

    // data for the program
    char* image_name = NULL;
    image_data* data = NULL;

  	get_values_from_command(argc, argv, &numb_images, &threshold_binarize, &threshold_classify, &mask_file_name, &show_results);
    
    for (int i = 1; i <= numb_images; i++){
        
        // genera nodo con el nombre del archivo
        image_name = got_name(i, image_name);
        data = insert_in_list(data, image_name);
        
        data = RGB_read_image(data);

        data = convert_gray_scale(data);

        data = convert_laplacian(data, mask_file_name);

        data = convert_binary(data, threshold_binarize);

        data = classified_image(data,threshold_classify);
        write_image(data, show_results);
    }
    //show_data_list(data);
    free(image_name);
    data = erase_list(data);
  	return 0;
}
