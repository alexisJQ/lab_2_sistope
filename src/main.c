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


int main(int argc, char* argv[])
{
    // data from command
    int numb_images = 1;
    int threshold_binarize = 100;
    int threshold_classify = 100;
    char* mask_file_name = NULL;
    int show_results = 0;
	char out[100];

    int piped[2];
	pipe(piped);

	pid_t pid;
	pid = fork();

	if (pid == 0){ //child section
		close(piped[WRITE]);
		dup2(piped[READ], STDIN_FILENO);
		execl("main2", "main2", NULL);
	}
	else if (pid > 0){ // father section
		close(piped[READ]);
		get_values_from_command(argc, argv, &numb_images, &threshold_binarize, &threshold_classify, &mask_file_name, &show_results);
		sprintf(out, "%s %d %d %d %d", mask_file_name, threshold_binarize, threshold_classify, numb_images, show_results);
		write(piped[WRITE], out, 100);
 	}
	wait(NULL);
  	return 0;
}
