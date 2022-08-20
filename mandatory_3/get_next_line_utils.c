#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if(!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
int ft_newline_idx(const char *s)
{
	int		i;

	i = 0;
	if(!s)
		return (-1);
	while (s[i] != '\n')
	{
		if (s[i] == '\0')
			return (-1);
		i ++;
	}
	return i;
}


int ft_terminate_idx(const char *s, int c)
{
	int		i;

	i = 0;
	if(!s)
		return (-1);
	while (s[i] != (char)c && s[i] != '\0')
	{
		i++;
	}
	return i;
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	len1;
	size_t	len2;

	i = 0;
	// if (!s1 || !s2)
	// 	return (0);
	if(!s1)
		s1 = "";
	if(!s2)
		s2 = "";
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (0);
	while (i < len1)
	{
		res[i] = s1[i];
		i ++;
	}
	while (i < len1 + len2)
	{
		res[i] = s2[i - len1];
		i ++;
	}
	res[i] = '\0';
	return (res);
}





