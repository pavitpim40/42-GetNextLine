#include "get_next_line.h"




char *get_next_line(int fd)
{
  char *buffer;
  int read_byte;
  // char *storage;

  if(fd <= 2)
    return NULL;
  
  buffer = malloc(sizeof(char)*(BUFFER_SIZE+1));
  if(!buffer)
    return NULL;
  
  read_byte = (int)read(fd,buffer,BUFFER_SIZE);
  if(read_byte == 0)
  {
    free(buffer);
    return NULL;
  }
  if(read_byte != -1){
    // printf("RD BYTE %d\n", read_byte);
    // printf("Buffer is %s", buffer);
    // printf("========\n");
    // free(buffer);
    buffer[read_byte] = '\0';
    return (buffer);
    // return NULL;
  }
    
  // printf("NORMAL EXIT\n");
  free(buffer);
  return NULL;
}

// int main ()
// {
//     //###### MAIN
//     int fd = open("text.txt",O_RDONLY);
   
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
 
//     // printf("RESULT %s\n", check_eof(&"PAVIT"));
   

// }