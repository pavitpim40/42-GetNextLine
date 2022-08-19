
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
void recursive_read(int fd,int *readBytePtr,char **bufferPtr,Stash *stashPtr,int * idxPtr)
{
    (*stashPtr).text = ft_strjoin((*stashPtr).text,*bufferPtr);
    *readBytePtr = read(fd,*bufferPtr,BUFFER_SIZE);
    *idxPtr = ft_newline_idx(*bufferPtr);
    printf("BUFF : %s\n",*bufferPtr);
    printf("STASH : %s\n", (*stashPtr).text);
    printf("INDEX : %d\n",*idxPtr);
  
    if(*readBytePtr != 0 && *idxPtr == -1)
    {
         
         return recursive_read(fd,readBytePtr,bufferPtr,stashPtr,idxPtr);
    }
        
    if(*readBytePtr != 0 && *idxPtr != -1)
    {
        return ;
    }
            
}
char *get_next_line(int fd)
{
    static Stash stash;
    char *buffer;
    int read_btye;
    int idx;
    char *full_line;
    // int BUFFSIZE = 1;
    // #### 1.1 : VALIDATE : INCORRECT INPUT
    if(fd > 0 && fd < 2 || fd < 0 || BUFFER_SIZE < 0)
        return NULL;

    // ##### 1.2 : VALIDATE : DIFFERENT FILE
    validate_stash(&stash,fd);
    
    // ##### 2 START : FIND A LINE IN STASH
    idx = ft_terminate_idx(stash.text,'\n');
    printf("TERMINATE IDX %d\n",idx);
    if(stash.text && idx != -1) 
    {
        full_line = splice_string(&stash.text,idx);
        printf("FULL LINE %s\n",full_line);
        printf("STASH IN #2 %s\n",stash.text);
          return  full_line;
    }
        
      

    buffer =  (char *)malloc(BUFFER_SIZE * sizeof(char));
    // #### 3 : TRY TO READ ONCE
    read_btye = read(fd,buffer,BUFFER_SIZE);
    idx = ft_newline_idx(buffer);
    printf("READ BYTE : %d\n",read_btye);
    if(read_btye == 0)
        return splice_string(&stash.text,idx);
    // stash.text = ft_strjoin(stash.text,buffer);

    // ##### 4.1 : RECURSIVE READ ULTIL MET \n
    recursive_read(fd,&read_btye,&buffer,&stash,&idx);
    // #### 4.2 :  WHEN STOP RECURSIVE (MET \n) => CONCLUDE STRING
    printf("AFTER RECURSIVE INX %d\n",idx);
    full_line = ft_strjoin(stash.text,splice_string(&buffer,idx));
    printf("FULL LINE %s\n", full_line);
    free(stash.text);
    stash.text = buffer;
    printf("STASH END GNL %s with LEN %zu\n",stash.text,ft_strlen(stash.text));
    return full_line;
}

int main ()
{
    //###### MAIN
    int fd = open("test.txt",O_RDONLY);
   
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    // printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    // printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    // printf("########################### LINE >>>> : %s\n", get_next_line(fd));
    // printf("########################### LINE >>>> : %s\n", get_next_line(fd));

}