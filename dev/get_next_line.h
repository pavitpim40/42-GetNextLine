// #include <stdlib.h>

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h> // read
#include<fcntl.h>

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#   define BUFFER_SIZE BUFSIZ
# endif

char    *get_next_line(int fd);
int 	ft_stridx(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
#endif