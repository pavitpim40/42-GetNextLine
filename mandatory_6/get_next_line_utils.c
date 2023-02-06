/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:18:32 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/06 16:26:02 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char *ft_strjoin(char const *s1, char const *s2)
{
	char *res;
	size_t i;
	size_t len1;
	size_t len2;

	i = 0;
	// if (!s1 || !s2)
	// 	return (0);
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (0);
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		res[i] = s2[i - len1];
		i++;
	}
	res[i] = '\0';
	return (res);
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

int ft_find_index(const char *s, char target)
{
	int i;
	int len;

	i = 0;
	if (!s)
		return (-1);

	len = (int)ft_strlen(s);
	while (i < len && s[i])
	{

		// if (target == '\0')
		// {
		// 	printf("#FT_FIND_INDEX :: TEMP LENGTH is %zd\n",ft_strlen(s));
		// 	printf("#FT_FIND_INDEX :: LOOP ROUND %d AND TARGET IS %c\n\n", i, target);
		// }
		if (s[i] == target)
		{

			return i;
		}

		i++;
		
	}
	return (-1);
}

char *splice_string(char **stringPtr, int idx, char end)
{
	size_t len;
	int i;
	int j;
	char *front;
	char *back;

	i = 0;
	j = 0;
	len = ft_strlen(*stringPtr);
	if (!*stringPtr || len == 0)
		return NULL;
	front = (char *)malloc(idx + 1 * (sizeof(char)));
	back = (char *)malloc(len - idx * (sizeof(char))); // ##REMARK original len-idx+1 for null terminate

	while ((i < (int)len) && (i < idx))
		front[j++] = (*stringPtr)[i++];

	front[j] = end;
	j = 0;
	i++; // skip \n ior \0;
	while (i < (int)len)
		back[j++] = (*stringPtr)[i++];
	// back[j] = '\0'; // ##REMARK
	free(*stringPtr);
	*stringPtr = back;
	return front;
}