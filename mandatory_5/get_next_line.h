/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:37:34 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/06 01:31:47 by ppimchan         ###   ########.fr       */
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
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int ft_terminate_idx(const char *s);
char	*ft_strdup(const char *s1);
char *splice_string(char **stringPtr,int idx,char end);
int ft_find_index(const char *s, char target);