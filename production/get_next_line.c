/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:27:55 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/10 12:06:15 by ppimchan         ###   ########.fr       */
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
    ssize_t read_btye;

    if(fd <= 2 || BUFFER_SIZE <= 0)
        return NULL;
    buf = malloc(sizeof(char) * BUFFER_SIZE);

    read_btye = read(fd,buf,BUFFER_SIZE);
    while(read_btye > 0)
    {   
        idx = ft_terminate_idx(buf);
        if(idx != -1)
        {
            temp = ft_strdup(buf);
            front = splice_string(&temp,idx);
            full_line = ft_strjoin(storage,front);
            storage = temp;
            return full_line;
        }
        temp = storage;
        storage = ft_strjoin(temp,buf);
        free(temp);
        read_btye = read(fd,buf,BUFFER_SIZE);
    }
    free(buf);
    return storage;
}
