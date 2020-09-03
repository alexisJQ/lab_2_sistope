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
		execl("main6", "main6", NULL);
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
        int** image = malloc(height * sizeof(int*));
    
        for (int i = 0; i < height; i++){
        image[i] = malloc(width * sizeof(int));
        for (int j = 0; j < width; j++){
            read(STDIN_FILENO, str, 100); // get pixel
            sscanf(str, "%d", &aux);
            image[i][j] = aux; 
            
            }
        }
        int x=0;
        FILE* mask_file = fopen(mask_file_name, "r");
        int mask[3][3];
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                fscanf(mask_file, "%d", &x);
                mask[i][j] = x;
            }
    
        }
        fclose(mask_file);
        for (int i = 0; i < width; i ++){
            for(int j=0 ; j<height ; j ++){  
                int sum = 0;
            if ( i == 0){                               // upper edge case
                if (j == 0){                            // upper left corner case
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][2] * image[i][j + 1];
                    sum += mask[2][1] * image[i + 1][j];
                    sum += mask[2][2] * image[i + 1][j + 1];
                }
                else if (j + 1 == width){        // upper right corner case
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][0] * image[i][j - 1];
                    sum += mask[2][1] * image[i + 1][j];
                    sum += mask[2][0] * image[i + 1][j - 1];
                }
                else{
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][2] * image[i][j + 1];
                    sum += mask[2][1] * image[i + 1][j];
                    sum += mask[2][2] * image[i + 1][j + 1];
                    sum += mask[2][0] * image[i + 1][j - 1];
                    sum += mask[1][0] * image[i][j - 1];
                }
            }
            else if ( i + 1 == height){           // lower edge case
                if (j == 0){                            // lower left corner case
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][2] * image[i][j + 1];
                    sum += mask[0][2] * image[i - 1][j + 1];
                    sum += mask[0][1] * image[i - 1][j];
                }
                else if (j + 1 == width){        // lower right corner case
                    sum += mask[1][1] * image[i][j];
                    sum += mask[0][1] * image[i - 1][j];
                    sum += mask[0][0] * image[i - 1][j - 1];
                    sum += mask[1][0] * image[i][j - 1];
                }
                else{
                    sum += mask[1][1] * image[i][j];
                    sum += mask[1][2] * image[i][j + 1];
                    sum += mask[0][2] * image[i - 1][j + 1];
                    sum += mask[0][1] * image[i - 1][j];
                    sum += mask[0][0] * image[i - 1][j - 1];
                    sum += mask[1][0] * image[i][j - 1];
                }
            }
            else if (j == 0){                           // left edge case
                sum += mask[1][1] * image[i][j];
                sum += mask[0][1] * image[i - 1][j];
                sum += mask[0][2] * image[i - 1][j + 1];
                sum += mask[1][2] * image[i][j + 1];
                sum += mask[2][2] * image[i + 1][j + 1];
                sum += mask[2][1] * image[i + 1][j];
            }
            else if (j + 1 == width){             // right edge case
                sum += mask[1][1] * image[i][j];
                sum += mask[0][1] * image[i - 1][j];
                sum += mask[0][0] * image[i - 1][j - 1];
                sum += mask[1][0] * image[i][j - 1];
                sum += mask[2][0] * image[i + 1][j - 1];
                sum += mask[2][1] * image[i + 1][j];
            }
            else{
                sum += mask[1][1] * image[i][j];
                sum += mask[1][2] * image[i][j + 1];
                sum += mask[0][2] * image[i - 1][j + 1];
                sum += mask[0][1] * image[i - 1][j];
                sum += mask[0][0] * image[i - 1][j - 1];
                sum += mask[1][0] * image[i][j - 1];
                sum += mask[2][0] * image[i + 1][j - 1];
                sum += mask[2][1] * image[i + 1][j];
                sum += mask[2][2] * image[i + 1][j + 1];
            }
            sprintf(str, "%u", sum);
            write(piped[WRITE], str, 100);
        }
    }
    for (int i = 0; i < height; i++){
        free(image[i]);
    }
    free(image);
    }
    waitpid(pid, NULL, 0);
    exit(0);
}
