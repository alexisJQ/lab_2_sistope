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
    int aux = 0;

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
		execl("main7", "main7", NULL);
	}
	else{//father section
		close(piped[READ]);
		write(piped[WRITE], str, 100); //send global values
	}


    for (int i = 1; i <= numb_images; i++){

        read(STDIN_FILENO, image_name, 100); // get name of the image
        write(piped[WRITE], image_name, 100); // send name of the image

        read(STDIN_FILENO, str, 100); // get dimension of the image
        sscanf(str, "%d %d", &width, &height);
        write(piped[WRITE], str, 100); //send dimension of the image
        
        int cantidad=0;
        int total=0;
        for (int pos = 0; pos < width * height; pos ++){
            read(STDIN_FILENO, str, 100); // get pixel
            sscanf(str, "%d", &aux);
            if (aux==0){
                cantidad+=1;
            }
            sprintf(str, "%d", aux);
            write(piped[WRITE], str, 100); // send pixel
            total=pos;
        }
        int porcentaje=(100*cantidad)/(total+1);
        if(porcentaje>=threshold_classify){
            sprintf(str, "%d", 1);
            write(piped[WRITE], str, 100);
        }
        else{
            sprintf(str, "%d", 0);
            write(piped[WRITE], str, 100);
        }
    }
    waitpid(pid, NULL, 0);
    exit(0);
}
