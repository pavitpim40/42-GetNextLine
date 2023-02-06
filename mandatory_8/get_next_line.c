/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:28 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/06 19:18:19 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void truncate_storage(char *storage, int index)
{
  int len;
  int i;
  char *new_storage;

  len = ft_strlen(storage);
  new_storage = malloc(sizeof(char) * len - index);
  i = 0;
  while (i < len)
  {
    new_storage[i] = storage[index + 1 + i];
    i++;
  }
  free(storage);
  storage = new_storage;
}

char *get_next_line(int fd)
{
  static char *storage;
  char *buf;
  char *full_line;
  int index;
  ssize_t read_byte;

  // Invalid FD , Invalid Buffer_Size
  if (fd <= 2 || BUFFER_SIZE <= 0)
    return NULL;

  // #1 Check Old Storage
  index = ft_find_newline_index(storage);
  if (index != -1)
  {
    full_line = extract_full_line(storage, index);
    truncate_storage(storage, index);
    return full_line;
  }

  // #2 Go to read mor
  buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
  if (!buf)
    return NULL;

  read_byte = read(fd, buf, BUFFER_SIZE);
       // #2.1 Cannot read
  if (read_byte == -1)
  {
    free(buf);
    return NULL;
  }

 // #2.2 read with 0 byte
  if (read_byte == 0 && storage)
  {
      full_line = ft_strdup(storage);
      free(storage);
      free(buf);
      storage = NULL;
      return full_line;
  }

  if(read_byte == 0) {
    free(buf);
    return NULL;
  }
  buf[read_byte] = '\0';
  printf("Buf %s\n",buf);
  while(read_byte > 0)
  {

    index = ft_find_newline_index(storage);
    printf("NEWLINE INDEX %d\n",index);
  if (index != -1)
  {
    full_line = extract_full_line(storage, index);
    truncate_storage(storage, index);
    return full_line;
  }
 
    storage = ft_strjoin(storage,buf);
    read_byte = read(fd, buf, BUFFER_SIZE);
  }

  return NULL;
}
