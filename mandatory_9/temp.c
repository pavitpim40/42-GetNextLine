#include "get_next_line.h"

char *extract_full_line(char *storage, int index)
{
  // int len;
  int i;
  char *full_line;

  // len = ft_strlen(storage);
  i = 0;
  // printf("SIZE OF MALLOC %d\n", index+2);
  full_line = malloc(sizeof(char) * index + 1 + 1);
  if (!full_line)
    return NULL;

  while (i < index)
  {
    full_line[i] = storage[i];
    i++;
  }
  if (storage[i] == '\n')
    full_line[i] = '\n';
  // printf("CURRENT I %d\n",i);
  // printf("CURRENT FULL_LINE %s",full_line);
  i++;
  //  printf("AFTER I %d\n",i);
  full_line[i] = '\0';
  return full_line;
}

char *extract_last_line(char *storage)
{
  int len;
  int i;
  char *full_line;

  len = ft_strlen(storage);
  i = 0;

  full_line = malloc(sizeof(char) * (len + 1));
  if (!full_line)
    return NULL;

  while (i < len)
  {
    full_line[i] = storage[i];
    i++;
  }
  // printf("SIGSEG\n");
  full_line[i] = '\0';
  // printf("EXT LST LINE IS %s\n", full_line);
  // printf("ADDRESS OF LST LINE IS %p\n", full_line);

  return full_line;
}

char *truncate_storage(char *storage, int index)
{
  int len;
  int i;
  char *new_storage;
  // printf("old storage is %s\n", storage);
  // i = 0;
  // while (!(storage[i] == '\0' || storage[i] == '\n'))
  // 	i++;
  // if (storage[i] == '\0')
  // {
  // 	free(storage);
  // 	return (NULL);
  // }

  len = ft_strlen(storage);
  if (len - index <= 1)
  {
    free(storage);
    return (NULL);
  }
  i = 0;
  // printf("TRUNCATE : LEN OF STORAGE %d\n" ,(int)len);
  // printf("TRUNCATE : VALUE OF STORAGE %s\n" ,storage);
  // printf("TRUNCATE : VALUE OF I %d\n" ,i);
  // printf("TRUNCATE : VALUE OF Index %d\n" ,index);
  // printf("TRUNCATE : LEN OF MALLOC %d\n" ,(int)(len - index));
  new_storage = malloc(sizeof(char) * (len - index));
  if (!new_storage)
    return NULL;

  while (storage && i < (len - index))
  {
    // printf("HI\n");
    new_storage[i] = storage[i + index + 1];
    i++;
  }

  new_storage[i] = '\0';
  // printf("Address of storage in TRUNCATE is %p\n",storage);
  free(storage);
  // printf("new storage is %s\n", new_storage);
  return new_storage;
}

// void storage_join(char **storage,char *buffer)
// {
//   char *new_storage;
//   size_t i;
//   size_t j;
//   size_t len1;
//   size_t len2;
//     // printf("STORE JOIN");
//   len1 = ft_strlen(*storage);
// 	len2 = ft_strlen(buffer);
//   new_storage = malloc(len1+len2+1);

//   i = 0;
//   while(*storage && (*storage)[i])
//   {
//     // printf("LOOP1");
//     new_storage[i] = (*storage)[i];
//     i++;
//   }
//   j = 0;
//   while(buffer[j])
//   {
//       //  printf("LOOP2");
//     new_storage[i+j] = buffer[j];
//     j++;
//   }
//   new_storage[i+j] = '\0';
//   *storage = new_storage;
// }

char *storage_join(char *storage, char *buffer)
{
  char *new_storage;
  size_t i;
  size_t j;
  size_t len1;
  size_t len2;
  // printf("STORE JOIN");
  len1 = ft_strlen(storage);
  len2 = ft_strlen(buffer);
  new_storage = malloc(len1 + len2 + 1);
  if (!new_storage)
    return NULL;

  i = 0;
  while (storage && storage[i])
  {
    // printf("LOOP1");
    new_storage[i] = storage[i];
    i++;
  }
  j = 0;
  while (buffer[j])
  {
    //  printf("LOOP2");
    new_storage[i + j] = buffer[j];
    j++;
  }
  new_storage[i + j] = '\0';
  // printf("ADDRESS OF STORAGE IN STR JOIN %p\n",storage);
  // printf("ADDRESS OF NEW-STORAGE IN STR JOIN %p\n",new_storage);
  if (storage)
    free(storage);
  return new_storage;
}

char *get_next_line(int fd)
{
  // ###############################
  // ############## DECLARE VARIABLE
  // ###############################
  char *buffer;
  int read_byte;
  char static *storage;
  // char *temp;
  // char *full_line;
  int index;
  // printf("================================================\n");
  // printf("STORAGE AT FIRST IS %s", storage);
  //  printf("================================================\n");

  // ###############################
  // ############## INVALID FD & BUFFER SIZE
  // ###############################
  if (fd < 0 || BUFFER_SIZE <= 0)
    return NULL;

  // ###############################
  // ###### ALLOCATE MEM FOR BUFFER
  // ###############################
  buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
  if (!buffer)
    return NULL;

  // ###############################
  // ##################### READ ONCE
  // ###############################
  // printf("GG");
  read_byte = (int)read(fd, buffer, BUFFER_SIZE);
   printf("READ BYTE %d\n",read_byte);
  if (read_byte == -1)
  {
    free(buffer);
    return NULL;
  }
  // printf("GG2");
  // printf("READ BYTE %d\n",read_byte);
  // printf("ADDRESS OF STORAGE %p\n",storage);
  // printf("ADDRESS OF BUFFER %p\n",buffer);




  // ###############################
  //  NOTHING TO READ :: NO STORAGE
  // ###############################
  if(read_byte == 0 && !storage)
  {
    printf("NOTHING TO READ && NO STORAGE\n");
    // printf("STR LENGTH IS %zu\n", ft_strlen(storage));
    // printf("SIZE OF POINTER IS %zu\n", sizeof(&storage));
    // printf("ADDRESS OF STORAGE  IS %p\n", storage);
    free(buffer);
    // printf("ADDRESS OF STORAGE IS %p\n", storage);
    // free(storage);
    return NULL;
  }

  index = ft_char_index(storage, '\n');
  // printf("GNL : INDEX %d\n", index);

  // ###############################
  // ############### NOTHING TO READ
  // ###############################
  if (read_byte == 0 && storage)
  {
    //  printf("NOTHING TO READ WITH STORAGE\n");
 
    if (index == -1)
    {
      free(buffer);
      // printf("THERE IS SOMETHING IN STORAGE BUT NO NEW LINE\n");
      // printf("STORAGE IS %s", storage);
      buffer = extract_last_line(storage);
      // printf("LAST BUFF %s\n",buffer);
        // printf("DD");
      // printf("address of buffer %p\n",buffer);
      // printf("address of storage %p\n",storage);
      free(storage);
      storage = NULL;
      // printf("C\n");
      return buffer;
    }

    free(buffer);
    buffer = extract_full_line(storage, index);
    // printf("ADDRESS OF STORAGE A  : %p\n",storage);
    
    storage = truncate_storage(storage, index);
    // printf("ADDRESS OF STORAGE B  : %p\n",storage);
    // free(storage);
    return buffer;

  

  }
 
 
 
 
    // printf("EE");
  // temp = NULL;
  // ###############################
  // ############### READ SUCCESSFUL
  // ###############################
  index = -1;
  // printf("READ BYTE IS %d\n",read_byte);
  if (read_byte > 0)
    buffer[read_byte] = '\0';
  // printf("CC");
  // printf("GNL : ADDRESS OF BUFFER BEFORE LOOP %p\n",buffer);
  while (read_byte > 0 && index == -1)
  {
    // printf("IN LOOP\n");
    // ###############################
    // ############### JOIN STORAGE
    // ###############################

    // #### LOG BEFORE ADDRESS
    // printf("BEF :: ADDRESS OF BUFFER %p\n", buffer);
    // printf("BEF :: ADDRESS OF TEMP %p\n", temp);
    // printf("BEF :: ADDRESS OF STORAGE %p\n", storage);
    // printf("BUF IS %s\n", buffer);
    // temp = storage;
    // printf("FF");
    storage = storage_join(storage, buffer);
    // printf("GG");
    // printf("GNL >> LOOP : storage is %s\n", storage);

    // #### LOG ADDRESS
    // printf("ADDRESS OF BUFFER %p\n", buffer);
    // printf("ADDRESS OF TEMP %p\n", temp);
    // printf("GNL >> LOOP : ADDRESS OF STORAGE %p\n", storage);

    // ###############################
    // ##### CHECK NEW LINE IN STORAGE
    // ###############################
    // printf("II");
    index = ft_char_index(storage, '\n');
    // printf("JJ");
    if (index != -1)
    {
      // printf("NEW LINE");
      // printf("GNL >> LOOP : FOUND NEW LINE AT INDEX %d\n", index);
      break;
    }

    // ###############################
    // ############### READ CONTINUE
    // ###############################
    // printf("KK");
    read_byte = (int)read(fd, buffer, BUFFER_SIZE);
    if (read_byte > 0)
      buffer[read_byte] = '\0';
    // printf("LL");
    // free(temp);
    // free(buffer);
    // return buffer;
  }

  // ###############################
  // #### BEFORE EXIT WITH LAST LINE
  // ###############################

  // printf("GNL :: INDEX %d\n", index);
  if (index == -1)
  {
    //  printf("A :: address of buff %p\n",buffer);
    free(buffer);

    buffer = extract_last_line(storage);

    // printf("B :: address of buff %p\n", buffer);
    // printf("B :: vale of buff %s\n", buffer);
    // printf("B :: address of storage %p\n", storage);
    free(storage);
    storage = NULL;
    // printf("C\n");
    return buffer;
  }

  // ###############################
  // ### BEFORE EXIT WITH FULL LINE
  // ###############################

  free(buffer);
  // printf("BEF NORMAL EXIT");
  buffer = extract_full_line(storage, index);
  // printf("GNL : AFTER EXTRACT FULLINE\n");
  // printf("GNL :VALUE OF EXTRACT FULL LINE %s\n", buffer);

  // printf("BEF : READ BYTE %d\n", read_byte);
  // printf("BEF : VALUE OF BUFFER %s\n", buffer);
  // printf("BEF : VALUE OF STORAGE %s", storage);
  // printf("BEF : ADDRESS OF STORAGE %p\n", storage);
  // printf("BEF : INDEX OF TRUNCATE %d\n", index);
  storage = truncate_storage(storage, index);
  // printf("GNL : AFTER TRUNCATE\n");
  // printf("GNL:AF : ADDRESS OF STORAGE %p\n", storage);
  // printf("GNL:AF : VALUE OF STORAGE %s", storage);
  // printf("AF : LENGTH OF STORAGE %d", (int)ft_strlen(storage));
  // printf("FINAL RESULT %s\n", buffer);

  // ###############################
  // ############## NORMAL RETURN
  // ###############################
  return buffer;
}
