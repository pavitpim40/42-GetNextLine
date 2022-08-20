// #include <stdlib.h>

#include <stdio.h> // BUFSIZ
#include <stdlib.h> // malloc
#include <unistd.h> // read
#include <fcntl.h>

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#   define BUFFER_SIZE 3
# endif


typedef struct Stash{
  int fd;
  char *text;
} Stash;

char    *get_next_line(int fd);
int     ft_newline_idx(const char *s);
int     ft_terminate_idx(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
// void    ft_cleanbuff(const char **buff,int len);
size_t	ft_strlen(const char *s);
#endif