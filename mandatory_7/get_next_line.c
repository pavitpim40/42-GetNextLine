/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:28 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/06 17:38:57 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char *ft_slice_string(char *storage, int idx)
{
    char *front;
    char *back;
    int   len;
    int i;
    int j;
    if(!storage)
      return NULL;

    len = (int)ft_strlen(storage);
    front = malloc(sizeof(char)* idx+ 1 + 1);
    if(!front)
      return NULL;
    back  = malloc(sizeof(char) * len - (idx+1) + 1);
    if(!back)
    return NULL;
    i = 0;
    j = 0;
    while(i <= idx)
    {
      front[j++] = storage[i++];
    }
    front[j] = '\0';
    j = 0;
    while(i < len)
    {
      back[j++] = storage[i++];
    }
    free(storage);
    storage = back;
    return front;
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


    buf = malloc(sizeof(char)* BUFFER_SIZE+1);
    // Cannot Allocate
    if(!buf)
      return NULL;

    read_byte = read(fd,buf,BUFFER_SIZE);
    if(read_byte == -1) 
    {
      free(buf);
      return NULL;
    }
    
    buf[read_byte] = '\0';

    while(read_byte > 0)
    {
      // printf("IN HERE");
      storage = ft_strjoin(storage,buf);
      index = ft_find_newline_index(storage);
      if(index != -1)
      {
       full_line = ft_slice_string(storage,index); 
   
       return full_line;
      }
       read_byte = read(fd,buf,BUFFER_SIZE);
      //  printf("READ BYTE %zd\n", read_byte);
       buf[read_byte] = '\0';

    }
  // printf("NORMAL EXIT\n");
  // printf("BUF IS %s and BUF LEN IS %zu\n", buf, ft_strlen(buf));
    free(buf);
  return storage;
  
}
