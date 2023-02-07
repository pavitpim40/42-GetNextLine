
// #include "get_next_line.h"

char *extract_full_line(char *storage)
{
  int i;
  char *full_line;
  int index;
  int len;
  int count;

  i = 0;
  index = ft_char_index(storage,index);
  len = ft_strlen(storage);
  if(index != -1)
  {
     full_line = malloc(sizeof(char) * index + 1 + 1);
     count = index;
  }
   
  else 
  {
     full_line = malloc(sizeof(char) * (len + 1));
      count = len;
  }
   
  if (!full_line)
    return NULL;

  while (i < count)
  {
    full_line[i] = storage[i];
    i++;
  }
  if (storage[i] == '\n')
  {
       full_line[i] = '\n';
  i++;
  }
 
  full_line[i] = '\0';
  return full_line;
}

