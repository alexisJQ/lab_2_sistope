#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../incl/support_for_main.h"
#include "../incl/images_data.h"
#include "../incl/image.h"

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{   

    int numb_images = 1;
    int threshold_binarize = 100;
    int threshold_classify = 100;
    char mask_file_name[20];
    int show_results = 0;
    char inputs[100];

    // data for the program
    char* image_name = NULL;
    image_data* data = NULL;

    read(STDIN_FILENO, inputs, 100);
    
    sscanf(inputs, "%s %d %d %d %d", mask_file_name,  &threshold_binarize, &threshold_classify, &numb_images, &show_results);

    int piped[2];
	pipe(piped);

	pid_t pid;
	pid = fork();

    if (pid == 0){//child section
        close(piped[WRITE]);
		dup2(piped[READ], STDIN_FILENO);
		execl("main3", "main3", NULL);
    }
    else{//father section
        close(piped[READ]);
        for(int i = 1; i <= numb_images; i++){
            // genera nodo con el nombre del archivo
            image_name = got_name(i, image_name);
            data = insert_in_list(data, image_name);
            
            data = RGB_read_image(data);
            write(piped[WRITE], data, sizeof(image_data*));
            data = erase_list(data);
        }

    }

    wait(NULL);
    exit(0);
}
