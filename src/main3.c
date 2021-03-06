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
    int bpp = 0;
    int aux = 0;
    uint8_t sum = 0;

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
		execl("main4", "main4", NULL);
	}
	else{//father section
		close(piped[READ]);
		write(piped[WRITE], str, 100); //send global values
	}
    
    for(int i = 1; i <= numb_images; i ++){
        
        read(STDIN_FILENO, image_name, 100); // get name of the image
        write(piped[WRITE], image_name, 100); // send name of the image
        
        read(STDIN_FILENO, str, 100); // get dimension of the image
        sscanf(str, "%d %d %d", &width, &height, &bpp);
        sprintf(str, "%d %d", width, height);
        write(piped[WRITE], str, 100); //send dimension of the image

        int pos = 0;

        // get gray scale of the image
        for (int i = 0; i < width * height * bpp; i++){
            read(STDIN_FILENO, str, 100); // get pixel
            sscanf(str, "%d", &aux);
            if (i % 3 == 0){
                sum += aux * 3 / 10;
            }
            else if (i % 3 == 1){
                sum += aux * 59 / 100;
            }
            else if (i % 3 == 2){
                sum += aux * 11 / 100;
                sprintf(str, "%u", sum);
                write(piped[WRITE], str, 100); //send pixel
                sum = 0;
                pos += 1;
            }

		}
        
    }
    waitpid(pid, NULL, 0);
    exit(0);
}
