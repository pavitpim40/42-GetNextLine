/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpintook <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:10:00 by tpintook          #+#    #+#             */
/*   Updated: 2023/02/02 16:10:02 by tpintook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char	*str);
char	*ft_strjoin(char *start, char *buff);
char	*ft_join(char *dest, char *s1, char *s2);
char	*ft_strchr(char *s, char c);

size_t	ft_strlen(char	*str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *fnt, char *buff)
{
	char	*dest;

	if (!fnt)
	{
		fnt = (char *)malloc(1 * sizeof(char));
		fnt[0] = '\0';
	}
	if (!fnt || !buff)
		return (NULL);
	dest = (char *)malloc(ft_strlen(fnt) + ft_strlen(buff) + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	dest = ft_join(dest, fnt, buff);
	free(fnt);
	return (dest);
}

char	*ft_join(char *dest, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
