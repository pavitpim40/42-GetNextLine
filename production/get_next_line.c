/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:55 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/05 03:08:36 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char *read_until_newline(int fd,char **strorage_ptr, char **buf_ptr,char **full_line)
// {
//     ssize_t read_btye;
//     /* PSUEDO-CODE
//     - try to read
    
//     */

//     read_byte = read(fd,*buf_ptr,BUFFER_SIZE);

//     if(read_btye > 0)
//     {
//         *fulline = ft_strjoin()
//     }
    
//     return (*full_line);
// }

char *get_next_line(int fd)
{
    static char *storage;
    char *buf;
    char *temp;
    char *full_line;
    char *front;
    int idx;
    ssize_t read_btye;

    if(fd <= 2 || BUFFER_SIZE <= 0)
        return NULL;
    buf = malloc(sizeof(char) * BUFFER_SIZE);

    read_btye = read(fd,buf,BUFFER_SIZE);
    while(read_btye > 0)
    {   
        idx = ft_terminate_idx(buf);
        // printf("TERMINATE IDX %d\n",idx);
        // printf("BUF  %s\n",buf);
        // Case 1 : Found new line OR end of file
        if(idx != -1)
        {
            temp = ft_strdup(buf);
            front = splice_string(&temp,idx);
            full_line = ft_strjoin(storage,front);
            // printf("temp %s\n", temp);
            // printf("temp len %zu\n", ft_strlen(temp));
            // free(storage);
            storage = temp;
            return full_line;
        }

        // Case 2 : Not found new line
        temp = storage;
        storage = ft_strjoin(temp,buf);
        free(temp);

        // Continue read
        read_btye = read(fd,buf,BUFFER_SIZE);
    }
    free(buf);
    return storage;
}


int main()
{
    int fd = open("raw.txt",O_RDONLY);
    printf("%s\n",get_next_line(fd));
     printf("%s\n",get_next_line(fd));
      printf("%s\n",get_next_line(fd));

}