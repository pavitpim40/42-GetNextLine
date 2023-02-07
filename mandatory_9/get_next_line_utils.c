#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char *ft_strjoin(char  *storage, char  *buffer)
{
  // printf("STR_JOIN\n");
	char *res;
	size_t i;
	size_t len1;
	size_t len2;

	i = 0;
  if (!storage && !buffer)
    return NULL;
	if (!storage)
	{
    // printf("malloc for storage\n");
    res = ft_strdup(buffer);
    return res;
    // storage = (char *)malloc(sizeof(char) * 1);
		// storage[0] = '\0';
  }
	
	len1 = ft_strlen(storage);
	len2 = ft_strlen(buffer);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return NULL;
  
  // printf("storage in join %s\n",storage);
	while (i < len1)
	{
    // printf("loop for storage\n");
    // printf("STR_JOIN STORAGE : LOOP AT %zu\n",i);
    // printf("STR_JOIN STORAGE : CHAR IS %c\n",storage[i]);
		res[i] = storage[i];
		i++;
	}
	while (i < len1 + len2)
	{
    //  printf("loop for buff\n");
    //  printf("STR_JOIN BUFF : LOOP AT %zu\n",i);
    // printf("STR_JOIN BUFF : CHAR  is %c\n",buffer[i - len1]);
		res[i] = buffer[i - len1];
		i++;
	}
	res[i] = '\0';
  // printf("A\n");
  // printf("ADDRESS OF STORAGE %p\n",storage);
  // free(storage);
  // printf("B\n");
  // printf("RES %s\n",res);
  // printf("RES LEN %zu\n", ft_strlen(res));
	return (res);
}

int ft_char_index(const char *s, int c)
{
	int	i;
  int len;

	len = ft_strlen((char *)s);
  i=0;
	while (i < len)
	{
		if (s[i] == (char)c)
			return (i);
		i ++;
	}
	return (-1);
}

char *ft_strdup(const char *s1)
{
	int len;
	int i;
	char *result;

	i = 0;
	len = (int)ft_strlen(s1);
	result = malloc(len + 1);
	if (result == 0)
		return (0);
	while (i < len)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}