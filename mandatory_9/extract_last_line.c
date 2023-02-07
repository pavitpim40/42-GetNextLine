
#include "get_next_line.h"
char *extract_last_line(char *storage)
{
  int len;
  int i;
  char *full_line;

  len = ft_strlen(storage);
  i = 0;
 
  if (len == 0)
    return NULL;
  

  full_line = malloc(sizeof(char) * (len + 1));

  if (!full_line)
    return NULL;

  while (i < len)
  {
    full_line[i] = storage[i];
    i++;
  }

  full_line[i] = '\0';
  return full_line;
}
