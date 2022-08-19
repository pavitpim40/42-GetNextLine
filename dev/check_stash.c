

#include <stdio.h>
#include <stdlib.h>
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int ft_stridx(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
	    i ++;
	
	return i;
}

char *utilize_stash(char **stashPtr,int idx)
{
    size_t len;
    int i;
    int j;
    char *line;
    char *rest;
 
    i = 0;
    j = 0;
    len = ft_strlen(*stashPtr);
    *line = (char *)malloc(idx+1 * (sizeof(char)));
    *rest = (char *)malloc(len-idx+1 * (sizeof(char)));
      
    while(i < len && i < idx)
        line[j++] = (*stashPtr)[i++];
    
    line[j] = '\0';
    j = 0;
    i++; // skip \n
    while(i < len)
        rest[j++] = (*stashPtr)[i++];
     
    rest[j] = '\0';
    free(*stashPtr);
    *stashPtr = rest;
    return line;   
}


int main()
{
   
    char *mock =  "Hello\nPavit\nPimchanagul";
   
    int i = 0;
    static char *stash;
    stash = (char *)malloc(sizeof(char)*24);
    while(mock[i] != '\0')
    {
        stash[i] = mock[i];
        i++;
    }
    stash[i] = '\0';

    // printf("%s\n",stash);
    // printf("%c\n",*stash);
    // printf("%p\n",&stash);
    int idx;

    idx = ft_stridx(stash,'\n');
    if(idx != -1)
    {   
    printf("%s\n", utilize_stash(&stash,idx));
    // printf("%s\n", utilize_stash(&stash,idx));
    // printf("%s\n", utilize_stash(&stash,idx));
    printf("STASH:%s\n",stash);
    printf("STASH LEN %zu",ft_strlen(stash));

    }
        
    
    
   

}