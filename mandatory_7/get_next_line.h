/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:39:45 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/06 16:24:49 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h> // for printf , remove before submut
#include <fcntl.h> // for O_RDONLY
#include <unistd.h> // read
#include <stdlib.h> // malloc



# ifndef BUFFER_SIZE
#   define BUFFER_SIZE 20
# endif

char *get_next_line(int fd);
size_t ft_strlen(const char *s);
char *ft_strjoin(char  *storage, char  *buffer);
int ft_find_newline_index(const char *s);
char *ft_slice_string(char *storage, int index);