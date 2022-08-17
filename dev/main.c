

#include "get_next_line.h"

int main()
{   
    int fd;
   
    fd = open("test.txt",O_RDONLY);
    char *buff = get_next_line(fd);

    printf("%s", buff);
}