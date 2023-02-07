/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:39:45 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/07 13:25:20 by ppimchan         ###   ########.fr       */
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
int ft_char_index(const char *s, int c);
char *truncate_storage(char *storage, int index);
char *ft_strdup(const char *s1);

char *storage_join(char *storage,char *buffer);
char *extract_last_line(char *storage);
// void storage_join(char **storage,char *buffer);