/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:55 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/06 14:10:38 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *storage;
    char *buf;
    char *temp;
    char *full_line;
    char *front;
    int idx;
    ssize_t read_byte;

    if (fd <= 2 || BUFFER_SIZE <= 0)
        return NULL;
    // buf = malloc(sizeof(char) * BUFFER_SIZE);
    buf = calloc(sizeof(char), BUFFER_SIZE);
    if (buf == NULL)
        return NULL;

    read_byte = read(fd, buf, BUFFER_SIZE);
    // printf("READ BYTE %zd\n", read_byte);
    if (read_byte <= 0)
    {
        // printf("BUF length %zu\n", ft_strlen(buf));
        // printf("BUF %s\n", buf);
        if (ft_strlen(buf))
            free(buf);

        // free(storage);

        if (ft_strlen(storage))
        {
            // printf("storage length %zu\n", ft_strlen(storage));
            // printf("storage are %s\n", storage);
            // free(storage);
        }

        return NULL;
    }
    printf("FIRST READ BYTE %zu AND BUF IS %s\n\n",read_byte,buf);
    while (read_byte > 0 && buf)
    {
        
        idx = ft_find_index(buf, '\n');
        // printf("TERMINATE IDX %d\n",idx);
        // printf("BUF  %d\n",BUFFER_SIZE);

        if (idx != -1)
        {
            // printf("#1");
            temp = ft_strdup(buf);
            front = splice_string(&temp, idx, '\n'); // truncate front with temp
            full_line = ft_strjoin(storage, front);  // storage aren't free
            free(storage);
            free(front);
            storage = temp;
            free(temp);
            // printf("NEWLINE\n");
            return full_line;
        }

        idx = ft_find_index(buf, '\0');
        printf("Index of EOF %d\n\n",idx);
        if (idx != -1)
        {
            printf("#2");
            temp = ft_strdup(buf);
            front = splice_string(&temp, idx, '\0'); // truncate front with temp
            full_line = ft_strjoin(storage, front);  // storage aren't free
            free(storage);
            storage = NULL;
            free(buf);
            free(temp);
            free(front);
            
            return full_line;
        }

        // Case 2 : Not found new line
        temp = storage;
       
        storage = ft_strjoin(temp, buf);
         printf("str length of temp %zu\n", ft_strlen(temp));
         printf("CURRENT TMP IS %s AND BUF %s\n",temp,buf);
         printf("CURRENT STORAGE IS %s\n", storage);
        // printf("#A\n");
        free(temp);
        // printf("#B\n");

        // Continue read
        read_byte = read(fd, buf, BUFFER_SIZE);
        printf("RD BYTE %zd AND CURRENT BUF IS %s\n",read_byte,buf);
    }
    printf("#3");
    free(buf);
    full_line = ft_strdup(storage);
    free(storage);
    storage = NULL;
    return full_line;
}

// int main()
// {
//     int fd = open("raw.txt",O_RDONLY);
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));

// }