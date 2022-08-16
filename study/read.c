// C program to illustrate 
// read system Call 
#include<stdio.h> 
#include <fcntl.h> 
#include <unistd.h> // read
#include <stdlib.h> // exit
// int main() 
// { 
// int fd, sz; 
// char *c = (char *) calloc(100, sizeof(char)); 
  
// fd = open("foo.txt", O_RDONLY); 
// if (fd < 0) { perror("r1"); exit(1); } 
  
// sz = read(fd, c, 20); 
// printf("called read(% d, c, 10). returned that"
//         " %d bytes were read.\n", fd, sz); 
// c[sz] = '\0'; 
// printf("Those bytes are as follows: %s\n", c); 
// } 

int main() 
{ 
    char c; 
    int fd1 = open("sample.txt", O_RDONLY, 0); 
    int fd2 = open("sample.txt", O_RDONLY, 0); 
    read(fd1, &c, 1); 
    read(fd2, &c, 1); 
    read(fd2, &c, 1); 
    printf("c = %c\n", c); 
    read(fd2, &c, 1); 
    printf("c = %c\n", c); 
    exit(0); 
} 