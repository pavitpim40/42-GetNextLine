/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:55 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/06 15:04:17 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

char *get_next_line(int fd)
{
    static char *storage;
    char *buf;
    char *temp;
    char *full_line;
    char *front;
    int newline_idx;
    int endfile_idx;
    ssize_t read_byte;

    if (fd <= 2 || BUFFER_SIZE <= 0)
        return NULL;
        
    buf = malloc(sizeof(char) * BUFFER_SIZE+1);
    if (buf == NULL)
        return NULL;

    temp =NULL;
    read_byte = read(fd,buf,BUFFER_SIZE);

    // CASE1 : CANNOT READ read_byte  <= 0
    if(read_byte <= 0)
    {
        if(buf)
            free(buf);
        if(storage)
            free(storage);
        return NULL;
    }

    // CASE2 : READ
    while(read_byte > 0)
    {
        // temp = ft_strdup(buf);
        // ft_bzero(buf,BUFFER_SIZE+1);
       
        printf("CURRENT READ BYTE is %zd\n",read_byte);
        printf("CURRENT TEMP IS %s\n",temp); 
        newline_idx = ft_find_index(buf,'\n');
        if(newline_idx != -1)
        {
            temp = ft_strdup(buf);
            printf("NEW LINE IDX IS %d\n", newline_idx);
            front = splice_string(&temp,newline_idx,'\n');
            full_line = ft_strjoin(storage,front);
            storage = temp;
            temp = NULL;
            if(front)
                free(front);
            return full_line;
        }
        
        endfile_idx = ft_find_index(buf,EOF);
        if(endfile_idx != -1)
        {
             temp = ft_strdup(buf);
            printf("NO new line in BUF\n");
            front = splice_string(&temp,endfile_idx ,'\0');
            free(temp);
            free(buf);
            full_line = ft_strjoin(storage,front);
            free(storage);
            free(front);
            return full_line;
        }


        read_byte = read(fd,buf,BUFFER_SIZE);
    }
    if(temp)
        free(temp);
    return storage;
}
