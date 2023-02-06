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
	char *res;
	size_t i;
	size_t len1;
	size_t len2;

	i = 0;
	if (!storage)
	{
    storage = (char *)malloc(sizeof(char) * 1);
		storage[0] = '\0';
  }
	if (!storage || !buffer)
    return NULL;
	len1 = ft_strlen(storage);
	len2 = ft_strlen(buffer);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return NULL;
	while (i < len1)
	{
		res[i] = storage[i];
		i++;
	}
	while (i < len1 + len2)
	{
		res[i] = buffer[i - len1];
		i++;
	}
	res[i] = '\0';
  free(storage);
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