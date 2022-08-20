
#include "get_next_line.h"

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
    front = (char *)malloc(idx+1 * (sizeof(char)));
    back =  (char *)malloc(len-idx+1 * (sizeof(char)));
    while(i < len && i < idx)
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

void validate_stash(Stash *stashPtr,int fd)
{
     if((*stashPtr).fd && (*stashPtr).fd != fd ) //เปิดอ่านไฟล์ใหม่ เคลียร์ stash เก่า
    {
        (*stashPtr).fd = fd;   
        free((*stashPtr).text);
        (*stashPtr).text = NULL;
    }
    if(!(*stashPtr).fd) //เปิดอ่านไฟล์ครั้งแรก ใช้งาน stash ครั้งแรก
    {
         (*stashPtr).fd = fd;   
        (*stashPtr).text = NULL;
    }
}


void recursive_read(int fd,int *readBytePtr,char **bufferPtr,Stash *stashPtr,char **fullinePtr)
{
    int idx;
    int len;

    *readBytePtr = read(fd,*bufferPtr,BUFFER_SIZE);
    (*bufferPtr)[*readBytePtr] = '\0';
    idx =  ft_newline_idx(*bufferPtr);

    if (*readBytePtr == 0)
    {
        len = ft_strlen((*stashPtr).text);  
        if (len == 0)
             *fullinePtr = NULL;
        *fullinePtr = splice_string(&(*stashPtr).text,len);
    }
    if(*readBytePtr != 0 && idx == -1)
    {  
        (*stashPtr).text = ft_strjoin((*stashPtr).text,*bufferPtr); 
         return recursive_read(fd,readBytePtr,bufferPtr,stashPtr,fullinePtr);
    }
    if(*readBytePtr != 0 && idx >= 0)
    {
        *fullinePtr = ft_strjoin((*stashPtr).text,splice_string(bufferPtr,idx));
        free((*stashPtr).text);
        (*stashPtr).text = *bufferPtr;
    } 
}

char    *get_next_line(int fd)
{
    static Stash stash;
    char *buffer;
    int read_btye;
    int idx;
    int len;
    char *full_line;

    // #### 1.1 : VALIDATE : INCORRECT INPUT
    if(fd > 0 && fd < 2 || fd < 0 || BUFFER_SIZE < 0)
        return NULL;
    // ##### 1.2 : VALIDATE : DIFFERENT FILE
    validate_stash(&stash,fd);

    // Check STASH
    len = ft_strlen(stash.text);
    idx = ft_newline_idx(stash.text);
    if(len != 0 && idx != -1)
        return splice_string(&stash.text,idx);
    else if(len != 0 && idx == 0)
        splice_string(&stash.text,idx); 

    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    recursive_read(fd,&read_btye,&buffer,&stash,&full_line);
    // free(buffer);
    return full_line;
}



int main ()
{
    //###### MAIN
    int fd = open("text.txt",O_RDONLY);
   
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
   

}