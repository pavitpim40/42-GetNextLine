

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

char *utilize_stash(char **stashPtr)
{
    size_t len;
    int i;
    int j;
    int idx;
      
    // printf("ADDRESS %p\n",stashPtr);
    // printf("Value @ ADDRESS %s\n",*stashPtr);
    // printf("LEN = %zu\n",len);
    // int idx = ft_stridx(*stashPtr,'\n');
    
    //   printf("IDX = %d\n",idx);
    idx = ft_stridx(*stashPtr,'\n');
    if(idx == -1)
     return NULL;
//    Other case found '\n' or '\0'
        i = 0;
        j = 0;
        len = ft_strlen(*stashPtr);
        char *line = (char *)malloc(idx+1 * (sizeof(char)));
        char *rest = (char *)malloc(len-idx+1 * (sizeof(char)));
      
        while(i < len && i < idx)
            line[j++] = (*stashPtr)[i++];
        line[j] = '\0';
        j = 0;
        i++; // skip \n
        while(i < len)
            rest[j++] = (*stashPtr)[i++];
        // printf("REST : %s\n",rest);
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
    printf("%s\n", utilize_stash(&stash));
    printf("%s\n", utilize_stash(&stash));
     printf("%s\n", utilize_stash(&stash));
    printf("STASH: %s",stash);
    printf("STASH LEN %zu",ft_strlen(stash));

}