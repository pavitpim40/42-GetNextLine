#include "get_next_line.h"

// ########### NOT FREE STORAGE
char *extract_full_line(char *storage, int index)
{

  int i;
  char *full_line;

  i = 0;

  full_line = malloc(sizeof(char) * index + 1 + 1);
  //  printf("FULLINE ADDRESS IS %p\n", full_line);
  // printf("SIZE OF FULLINE  %d\n", index + 1 + 1);
  if (!full_line)
    return NULL;

  while (i < index)
  {
    full_line[i] = storage[i];
    i++;
  }
  if (storage[i] == '\n')
    full_line[i] = '\n';
  i++;

  full_line[i] = '\0';
  return full_line;
}

// ########### NOT FREE STORAGE
char *extract_last_line(char *storage)
{
  int len;
  int i;
  char *full_line;

  len = ft_strlen(storage);
  i = 0;
  // printf("length of storage is %d\n",len);
  if (len == 0)
  {
    // printf("EMPTY STORAGE");
    return NULL;
  }

  full_line = malloc(sizeof(char) * (len + 1));
  // printf("LAST LINE ADDRESS IS %p\n", full_line);
  // printf("SIZE OF LAST LINE  %d\n", len + 1);
  //  printf("ADDRESS IS   %p\n", full_line);
  // printf("SIZE OF IS   %d\n", len+1);

  if (!full_line)
    return NULL;

  while (i < len)
  {
    full_line[i] = storage[i];
    i++;
  }

  full_line[i] = '\0';
  return full_line;
}

// ###########  FREE STORAGE
char *truncate_storage(char *storage, int index)
{
  int len;
  int i;
  char *new_storage;

  len = ft_strlen(storage);
  if (len - index <= 1)
  {
    free(storage);
    return (NULL);
  }
  i = 0;

  new_storage = malloc(sizeof(char) * (len - index));
  // printf("NEW STORAGE ADDRESS IS %p\n", new_storage);
  // printf("SIZE OF NEW STORAGE  %d\n", len - index);
  // printf("ADDRESS IS   %p\n", new_storage);
  // printf("SIZE OF IS   %d\n", len-index);

  if (!new_storage)
    return NULL;

  while (storage && i < (len - index - 1))
  {

    new_storage[i] = storage[i + index + 1];
    i++;
  }

  new_storage[i] = '\0';

  free(storage);

  return new_storage;
}

// ###########  FREE STORAGE
char *storage_join(char *storage, char *buffer)
{
  char *new_storage;
  size_t i;
  size_t j;
  size_t len1;
  size_t len2;

  len1 = ft_strlen(storage);
  len2 = ft_strlen(buffer);
  //  printf("JOIN : OLD STORAGE ADDRESS IS %p\n", storage);
  //  printf("JOIN : BUFFER  ADDRESS IS %p\n", buffer);
  new_storage = malloc(len1 + len2 + 1);
  //  printf("JOIN : NEW STORAGE ADDRESS IS %p\n", new_storage);
  // printf("JOIN : SIZE OF NEW STORAGE  %lu\n", len1 + len2 + 1);

  if (!new_storage)
    return NULL;

  i = 0;
  while (storage && storage[i])
  {

    new_storage[i] = storage[i];
    i++;
  }
  j = 0;
  while (buffer[j])
  {
    new_storage[i + j] = buffer[j];
    j++;
  }
  new_storage[i + j] = '\0';

  if (storage)
    free(storage);
  return new_storage;
}

char *get_next_line(int fd)
{
  char *buffer;
  int read_byte;
  char static *storage;
  int index;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return NULL;
  buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
  if (!buffer)
    return NULL;
  // printf("ADD OF BUFF %p\n", buffer);
  // printf("ADD OF BUFF %p\n", BUFFER_SIZE + 1);
  index = -1;
  read_byte = 1;
  while (read_byte > 0 && index == -1)
  {
    read_byte = (int)read(fd, buffer, BUFFER_SIZE); // 217
    buffer[read_byte] = '\0';
    // printf("BUFFER LEN IS %zd\n",ft_strlen(buffer));
    //  printf("ADDRESS OF BUFFER %p\n", buffer);
    storage = storage_join(storage, buffer);
    // printf("ADDRESS OF STORAGE %p\n", storage);
    index = ft_char_index(storage, '\n');
    // printf("\nREAD BYTE IS %d\n",read_byte);
    // printf("INDEX IS %d\n",index);
  }
  //  printf("BEF : address of buffer %p\n",buffer);
  // printf("BEF : value of buffer %s\n", buffer);
  // printf("BEF : buffer length %zu\n\n", ft_strlen(buffer));
  free(buffer);
  // buffer = NULL;
  // printf("AF : address of buffer %p\n",buffer);
  // printf("AF : value of buffer %s\n", buffer);
  // printf("AF : buffer length %zu\n", ft_strlen(buffer));
  if (index == -1)
  {
    buffer = extract_last_line(storage);
    //  printf("ADDRESS #3 %p\n",storage);
    //  printf("\n STORAGE LENGTH %zu\n",ft_strlen(storage));
    free(storage);
    //  printf("ADDRESS #4 %p\n",storage);

    storage = NULL;
    return buffer;
  }
  buffer = extract_full_line(storage, index);
  // printf("ADDRESS %p\n",storage);
  storage = truncate_storage(storage, index);
  //  printf("\n STORAGE LENGTH %zu\n",ft_strlen(storage));
  return buffer;
}


// int main()
// {
//     char *string;
//     int fd;
// 	int i = 0;

//     fd = open("text.txt", O_RDONLY);

// 	while (i < 11)
// 	{
//      printf("LOOP AT %d\n",i+1);
//     	string = get_next_line(fd);
//     	// string = get_next_line(fd);
// 		printf("%s", string);
   
// 		i++;
// 	}
  
// 	free(string);
//     close(fd);
//     return (0);
// }