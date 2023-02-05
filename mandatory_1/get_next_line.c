
#include "get_next_line.h"

char *splice_string(char **stringPtr,int idx)
{
    size_t len;
    size_t i;
    size_t j;
    char *front;
    char *back;

    i=0;
    j=0;
    len = ft_strlen(*stringPtr);
    if(!*stringPtr || len == 0)
        return NULL;
    front = (char *)malloc(idx+1 * (sizeof(char)));
    back =  (char *)malloc(len-idx+1 * (sizeof(char)));
    while(i < len && i < (size_t)idx)
        front[j++] = (*stringPtr)[i++];
     front[j] = '\0';
    j = 0;
    i++; // skip \n
    while(i < len)
        back[j++] = (*stringPtr)[i++];
    back[j] = '\0';
    free(*stringPtr); 
    *stringPtr = back; 
    return front;   
}

char *get_next_line(int fd)
{
    static char *stash;
    char *buffer;
    int read_btye;
    int idx;
    char *full_line;
    int BUFFSIZE = 1;
    if(fd < 0 || BUFFSIZE < 0)
        return NULL;
    idx = ft_terminate_idx(stash,'\n'); 
    if(idx != -1)
        return splice_string(&stash,idx);
    // START : FUNCTION CONTINUE READ
    buffer =  (char *)malloc(BUFFSIZE * sizeof(char));
    read_btye = read(fd,buffer,BUFFSIZE);
    idx = ft_terminate_idx(buffer,'\n');
    if(read_btye == 0)
        return splice_string(&stash,idx);
    while(read_btye != 0 && idx == -1)
    {
        stash = ft_strjoin(stash,buffer); 
        read_btye = read(fd,buffer,BUFFSIZE);
        idx = ft_terminate_idx(buffer,'\n');
    }
    // END : FUNTION CONTINUE READ
    full_line = ft_strjoin(stash,splice_string(&buffer,idx));
    free(stash);
    stash = buffer;
    return full_line;
}

int main ()
{
    //###### MAIN
    int fd = open("test.txt",O_RDONLY);
   
    printf("RESULT : %s\n", get_next_line(fd));
    printf("RESULT : %s\n", get_next_line(fd));
    printf("RESULT : %s\n", get_next_line(fd));
    printf("RESULT : %s\n", get_next_line(fd));
    printf("RESULT : %s\n", get_next_line(fd));
    printf("RESULT : %s\n", get_next_line(fd));

}