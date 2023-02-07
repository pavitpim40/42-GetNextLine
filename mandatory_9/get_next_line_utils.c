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

