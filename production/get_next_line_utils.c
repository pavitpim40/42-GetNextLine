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
    // free(s1);
	return (res);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*result;

	i = 0;
	len = ft_strlen(s1);
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

int ft_terminate_idx(const char *s)
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

	// while (s[i] != '\n' && s[i] != '\0')
	// {
		
	// 	i ++;
	// }
	return i;
}

char *splice_string(char **stringPtr,int idx)
{
    size_t len;
    int i;
    int j;
    char *front;
    char *back;

    i=0;
    j=0;
    len = ft_strlen(*stringPtr);
    if(!*stringPtr || len == 0)
        return NULL;
    front = (char *)malloc(idx+2 * (sizeof(char)));
    back =  (char *)malloc(len-idx+1 * (sizeof(char)));
    //   printf("FRONT BEFORE %s\n",front);
    // printf("LEN %zu\n",len);
    while((i < (int)len) && (i < idx))
    {   
        // printf("CHAR IN FRONT %c at i = %d and idx = %d\n",(*stringPtr)[i],i,idx );
         front[j++] = (*stringPtr)[i++];
    }
       
     front[j] = '\n';
     front[j+1] = '\0';
    // printf("FRONT %s\n",front);
    // printf("======================\n");
    j = 0;
    i++; // skip \n
    while(i < (int)len)
        back[j++] = (*stringPtr)[i++];
    // back[j] = '\0';
    free(*stringPtr); 
    *stringPtr = back; 
    return front;   
}