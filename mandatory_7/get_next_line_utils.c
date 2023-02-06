/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:31 by ppimchan          #+#    #+#             */
/*   Updated: 2023/02/06 16:26:34 by ppimchan         ###   ########.fr       */
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


int ft_find_newline_index(const char *s)
{
	int i;
	// int len;

	i = 0;
	if (!s)
		return (-1);

	while (s[i])
	{
		if (s[i] == '\n')
			break;

		i++;
		
	}
	return (-1);
}