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
    int** matrix = NULL;

    // get global values
    read(STDIN_FILENO, str, 100);
    sscanf(str, "%s %d %d %d %d", mask_file_name,  &threshold_binarize, &threshold_classify, &numb_images, &show_results);

    // mask
    FILE* mask_file = fopen(mask_file_name, "r");
    int mask[3][3];

    // get values of the mask
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            fscanf(mask_file, "%d", &aux);
            mask[i][j] = aux;
        }
    }

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

    for(int x = 1; x <= numb_images; x ++){
        
        read(STDIN_FILENO, image_name, 100); // get name of the image
        write(piped[WRITE], image_name, 100); // send name of the image
        
        read(STDIN_FILENO, str, 100); // get dimension of the image
        sscanf(str, "%d %d", &width, &height);
        write(piped[WRITE], str, 100); //send dimension of the image

        matrix = (int**)malloc(sizeof(int*) * height);

        // get grayscale image
        for (int i = 0; i < height; i++){
            matrix[i] = (int*)malloc(sizeof(int) * width);
            for (int j = 0; j < width; j++){
                read(STDIN_FILENO, str, 100); // get pixel
                sscanf(str, "%d", &aux);
                matrix[i][j] = aux;
            }

		}

        for (int i = 0; i < height; i++){   // traverse rows of image
            for (int j = 0; j < width; j++){ // traverse columns of image
                aux = 0;
                for (int f = 0; f < 3; f++){
                    for (int c = 0; c < 3; c++){
                        if (i + f - 1 < 0 || i + f - 1 >= height || j + c - 1 < 0 || j + c - 1 >= width){
                            aux += 0;
                        }
                        else{
                            aux = aux + matrix[i + f - 1][j + c - 1] * matrix[f][c];
                        }
                    }
                }
                sprintf(str, "%d", aux);
                write(piped[WRITE], str, 100); // send pixel

            }
        }

        for (int i = 0; i < height; i++){
            free(matrix[i]);
        }

        free(matrix);
        
    }

    // close file of the mask
    fclose(mask_file);
    exit(0);
}
