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

int main(int argc, char const *argv[])
{   
    printf("main3\n");
    image_data* data = NULL;
    read(STDIN_FILENO, data, sizeof(image_data*));
    printf("end main3\n");
    printf("%s\n",data->image_name);
    return 0;
}
