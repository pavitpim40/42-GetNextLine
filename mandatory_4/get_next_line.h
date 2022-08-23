// #include <stdlib.h>

#include <stdio.h> // BUFSIZ
#include <stdlib.h> // malloc
#include <unistd.h> // read
#include <fcntl.h>

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#   define BUFFER_SIZE 420
# endif


typedef struct Stash{
  int fd;
  char *text;
  int read_byte;
} Stash;

char    *get_next_line(int fd);
int     ft_newline_idx(const char *s);
int     ft_terminate_idx(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
#endif