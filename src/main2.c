#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "../incl/support_for_main.h"
#include "../incl/images_data.h"
#include "../incl/image.h"

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{   
	// data from command
    int numb_images = 1;
    int threshold_binarize = 100;
    int threshold_classify = 100;
    char mask_file_name[20];
    int show_results = 0;
    char str[100];

    // data for the program
    char* image_name = NULL;
    image_data* data = NULL;

	// get global values
    read(STDIN_FILENO, str, 100);
    sscanf(str, "%s %d %d %d %d", mask_file_name,  &threshold_binarize, &threshold_classify, &numb_images, &show_results);

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
		write(piped[WRITE], str, 100); //send values of the command
	}

	for (int i = 1; i <= numb_images; i++){
		
		// read of the .jpg file
		image_name = got_name(i, image_name);
        data = insert_in_list(data, image_name);
        data = RGB_read_image(data);
		
		sprintf(str, "%s", data->image_name);
		write(piped[WRITE], str, 100); // send name of the image

		sprintf(str, "%d %d %d", data->width, data->height, data->bpp);
		write(piped[WRITE], str, 100);

		// send pixel one by one to the next process
		for (int i = 0; i < data->width * data->height * data->bpp; i++){
			sprintf(str, "%u", data->principal_image[i]);
			write(piped[WRITE], str, 100); // send pixel
		}


	}
	data = erase_list(data);
	free(image_name);
	waitpid(pid, NULL, 0);
    exit(0);
}
