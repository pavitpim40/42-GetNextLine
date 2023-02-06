#include "get_next_line.h"

char *extract_full_line(char *storage, int index)
{
  // int len;
  int i;
  char *full_line;

  // len = ft_strlen(storage);
  i = 0;

  full_line = malloc(sizeof(char) * index + 1 + 1);
  if (!full_line)
    return NULL;

  while (i < index)
  {
    full_line[i] = storage[i];
    i++;
  }
  full_line[i++] = '\n';
  full_line[i] = '\0';
  return full_line;
}

char *truncate_storage(char *storage, int index)
{
  int len;
  int i;
  char *new_storage;

  len = ft_strlen(storage);
  new_storage = malloc(sizeof(char) * (len - index+1));
  if(!new_storage)
    return NULL;
  i = 0;
  while (i < (len-index))
  {
    new_storage[i] = storage[index + 1 + i];
    i++;
  }
  new_storage[i] = '\0';
  // printf("Address of storage in TRUNCATE is %p\n",storage);
  free(storage);
  return new_storage;
}

char *get_next_line(int fd)
{
  char *buffer;
  int read_byte;
  char static *storage;
  char *full_line;
  int index;

  if(fd < 0)
    return NULL;

  //  index = ft_char_index(storage,'\n');
  //   if(index != -1)
  //   {
  //     // printf("FOUND NEW LINE");
  //    full_line =  extract_full_line(storage,index);
  //    storage = truncate_storage(storage,index);
  //    return full_line;
  //   }
  
  buffer = malloc(sizeof(char)*(BUFFER_SIZE+1));
  if(!buffer)
    return NULL;
  
  read_byte = (int)read(fd,buffer,BUFFER_SIZE);
  if(read_byte == 0)
  {
    free(buffer);
    return NULL;
  }
  storage = NULL;

  while(read_byte != 0 && read_byte != -1){
    buffer[read_byte] = '\0';
    storage = ft_strjoin(storage,buffer);
    // ######### CHECK STORAGE
    index = ft_char_index(storage,'\n');
    if(index != -1)
    {
      // printf("FOUND NEW LINE");
     full_line =  extract_full_line(storage,index);
    //  printf("address of buffer %p\n",buffer);
    //  printf("address of storage in gnl loop %p\n",storage);
    //  printf("address of fulline %p\n",full_line);
     free(buffer);
     free(storage);
    //  storage = truncate_storage(storage,index);
    //  printf("check terminate\n");
    //  storage = NULL;
     return full_line;
    }
    // ######### CHECK STORAGE
    read_byte = (int)read(fd,buffer,BUFFER_SIZE);
  }

    
  // printf("NORMAL EXIT\n");
    //  printf("address of storage in gnl %p\n",storage);
  // full_line = ft_strdup(storage);
  // storage = truncate_storage(storage,index);
  free(buffer);
  return storage;
}

// int main ()
// {
//     //###### MAIN
//     int fd = open("text.txt",O_RDONLY);
   
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
 
//     // printf("RESULT %s\n", check_eof(&"PAVIT"));
   

// }