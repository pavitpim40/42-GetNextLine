#include "get_next_line.h"

int main()
{   
    int fd;
    static Stash stash;
   
    fd = open("test.txt",O_RDONLY);
    // char *buff = get_next_line(fd);
    stash.fd = fd;
    stash.text = "HelloPavit";

    printf("%s\n", stash.text );
    // printf("%s\n",  get_next_line(fd));
    // printf("%s\n",  get_next_line(fd));
}