/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:33 by tpintook          #+#    #+#             */
/*   Updated: 2023/02/07 11:30:13 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(char *s);
char	*ft_cut_line(char *s);
char	*get_next_line(int fd);

char	*ft_read_line(char *s)
{
	int		i;
	char	*rt_line;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	rt_line = (char *)malloc(sizeof(char) * i + 1);
	if (!rt_line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		rt_line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		rt_line[i++] = '\n';
	rt_line[i] = '\0';
	return (rt_line);
}

char	*ft_cut_line(char	*s)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (!(s[i] == '\0' || s[i] == '\n'))
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	i = i + 1;
	new_str = (char *)malloc(ft_strlen(s) + 1 - i);
	if (!new_str)
		return (NULL);
	j = 0;
	while (s[i + j])
	{
		new_str[j] = s[i + j];
		j++;
	}
	new_str[j] = '\0';
	free(s);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			fd_read;
	static char	*present_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_read = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (fd_read > 0 && !(ft_strchr(present_str, '\n')))
	{
		fd_read = read(fd, buffer, BUFFER_SIZE);
		if (fd_read == -1)
		{
			free(buffer);
			// printf("buffer %s",buffer);
			return (NULL);
		}
		buffer[fd_read] = '\0';
		present_str = ft_strjoin(present_str, buffer);
	}
	free(buffer);
	buffer = ft_read_line(present_str); // extract line 
	present_str = ft_cut_line(present_str); // truncate storage
	return (buffer);
}

// int main()
// {
//     char *string;
//     int fd;
// 	int i = 0;

//     fd = open("foo.txt", O_RDONLY);

// 	while (i < 1)
// 	{
//     	string = get_next_line(42);
//     	string = get_next_line(42);
// 		printf("%s", string);
// 		i++;
// 	}

// 	free(string);
//     close(fd);
//     return (0);
// }