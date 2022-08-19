
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
void recursive_read(int fd,int *readBytePtr,char **bufferPtr,Stash *stashPtr)
{
    // int read_btye;
    int BUFFSIZE = 1;
    int idx;

    (*stashPtr).text = ft_strjoin((*stashPtr).text,*bufferPtr); 
    *readBytePtr = read(fd,*bufferPtr,BUFFSIZE);
    idx = ft_terminate_idx(*bufferPtr,'\n');
    // if(*readBytePtr == 0)
    // {

    // }
    //  printf("IN RECURSIVE-1 %s\n",*bufferPtr);
    if(*readBytePtr != 0 && idx == -1)
         return recursive_read(fd,readBytePtr,bufferPtr,stashPtr);  
   

}
char *get_next_line(int fd)
{
    // static char *stash;
    static Stash stash;
    char *buffer;
    int read_btye;
    int idx;
    char *full_line;
    int BUFFSIZE = 1;
    // #### START : VALIDATE : INCORRECT INPUT
    if(fd > 0 && fd < 2 || fd < 0 || BUFFSIZE < 0)
        return NULL;
    // #### END : VALIDATE : INCORRECT INPUT

    // ##### START : VALIDATE : DIFFERENT FILE
    validate_stash(&stash,fd);
    // if(stash.fd && stash.fd != fd ) //เปิดอ่านไฟล์ใหม่ เคลียร์ stash เก่า
    // {
    //     stash.fd = fd;   
    //     free(stash.text);
    //     stash.text = NULL;
    // }
    // if(!stash.fd) //เปิดอ่านไฟล์ครั้งแรก ใช้งาน stash ครั้งแรก
    // {
    //     stash.fd = fd;
    //     stash.text = NULL;
    // }
    // ##### END : VALIDATE : DIFFERENT FILE


    // ##### START : FIND LINE IN STASH
    
    idx = ft_terminate_idx(stash.text,'\n'); 
    // if(idx != -1)
    if(stash.text && idx != -1)
        return splice_string(&stash.text,idx);
   
    // ##### END : FIND LINE IN STASH

    // #### START : FUNCTION CONTINUE READ
    buffer =  (char *)malloc(BUFFSIZE * sizeof(char));
    read_btye = read(fd,buffer,BUFFSIZE);
    idx = ft_terminate_idx(buffer,'\n');
     printf("STASH IN GNL %s\n",stash.text);
    if(read_btye == 0)
        return splice_string(&stash.text,idx);
    
    // ##### START : RECURSIVE READ
    recursive_read(fd,&read_btye,&buffer,&stash);
    // while(read_btye != 0 && idx == -1)
    // {
    //     stash.text = ft_strjoin(stash.text,buffer); 
    //     read_btye = read(fd,buffer,BUFFSIZE);
    //     idx = ft_terminate_idx(buffer,'\n');
    // }
    // #### END : RECURSIVE READ 
    // #### END : FUNTION CONTINUE READ

    // #### START : CONCLUDE STRING
    full_line = ft_strjoin(stash.text,splice_string(&buffer,idx));
    free(stash.text);
    stash.text = buffer;
    return full_line;
    // #### END : CONCLUDE STRING
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