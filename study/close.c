#include<stdio.h> 
#include <fcntl.h> 
#include <unistd.h> // close
#include <stdlib.h> // exit
// int main() 
// { 
//     int fd1 = open("foo.txt", O_RDONLY); 
//     if (fd1 < 0) 
//     { 
//         perror("c1"); 
//         exit(1); 
//     } 
//     printf("opened the fd = % d\n", fd1); 
      
//     // Using close system Call 
//     if (close(fd1) < 0) 
//     { 
//         perror("c1"); 
//         exit(1); 
//     } 
//     printf("closed the fd.\n"); 
// } 


int main() 
{ 
    // assume that foo.txt is already created 
    int fd1 = open("foo.txt", O_RDONLY, 0); 
    close(fd1); 
      
    // assume that baz.tzt is already created 
    int fd2 = open("baz.txt", O_RDONLY, 0); 
      
    printf("fd2 = % d\n", fd2); 
    exit(0); 
} 