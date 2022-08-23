
#include "get_next_line.h"

// static char *check_eof(char **stashPtr)
// {
//     int len = ft_strlen(*stashPtr);
//     int i = 0;
//     while(i <= len)
//     {   
//         // printf("CHAR : %c and CONVERT TO INT %d\n",((*stashPtr)[i]),(int)((*stashPtr)[i]));
//         if((int)((*stashPtr)[i]) == 0)
//             return "TRUE";
//         i++;
//     }
//     return "FALSE";
// }

static char *splice_string(char **stringPtr,int idx)
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
    back[j] = '\0';
    free(*stringPtr); 
    *stringPtr = back; 
    return front;   
}

static void validate_stash(Stash *stashPtr,int fd)
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


static void recursive_read(int fd,int *readBytePtr,char **bufferPtr,Stash *stashPtr,char **full_linePtr)
{
    int idx;
    int len;

    *readBytePtr = read(fd,*bufferPtr,BUFFER_SIZE);
    (*stashPtr).read_byte = *readBytePtr;
    //   printf("BUFF %s\n", (*bufferPtr));
    // // printf(" -------> EOF : %s\n", check_eof(bufferPtr));
    // printf("BUFFSIZE %d\n", BUFFER_SIZE);
    // printf("READ BYTE %d\n",  *readBytePtr);

    (*bufferPtr)[*readBytePtr] = '\0';
    idx =  ft_newline_idx(*bufferPtr);
    // printf("STASH %s\n", (*stashPtr).text);
   
    // printf("IDX %d\n", idx);
    if (*readBytePtr == 0)
    {
        len = ft_strlen((*stashPtr).text);  
        if (len == 0)
             *full_linePtr = NULL;
        *full_linePtr = splice_string(&(*stashPtr).text,len);
    }
    if(*readBytePtr != 0 && idx == -1)
    {  
        (*stashPtr).text = ft_strjoin((*stashPtr).text,*bufferPtr); 
         return recursive_read(fd,readBytePtr,bufferPtr,stashPtr,full_linePtr);
    }
    if(*readBytePtr != 0 && idx >= 0)
    {
        *full_linePtr = ft_strjoin((*stashPtr).text,splice_string(bufferPtr,idx));
        free((*stashPtr).text);
        (*stashPtr).text = *bufferPtr;
    } 
}



char    *get_next_line(int fd)
{
    static Stash stash;
    char *buffer;
    int read_byte;
    int idx;
    int len;
    char *full_line;
    char *tmp;

    // #### 1.1 : VALIDATE : INCORRECT INPUT
    if((fd > 0 && fd < 2) || fd < 0 || BUFFER_SIZE < 0)
        return NULL;
    // ##### 1.2 : VALIDATE : DIFFERENT FILE
    validate_stash(&stash,fd);
    

    // Check STASH
    // printf("STASH %s\n", stash.text);
    // printf("EOF %s\n", check_eof(&(stash.text)));
    // printf(" -------> EOF : %s\n", check_eof(&(stash.text)));

    len = ft_strlen(stash.text);
    idx = ft_newline_idx(stash.text);
    // printf("IDX %d\n", idx);
    // if(len != 0 && (stash.text)[len+1] == EOF)
    //     return "Hey\n";
    //  if(read_byte == 0 && len != 0 && idx == -1 && (stash.text)[len] == '\n')
    //     return "Hey\n";
    //  printf("STASH %s\n",stash.text);
    if (stash.text && (stash.read_byte < BUFFER_SIZE) && idx == -1){
            // printf("HI\n");
            tmp = ft_strdup(stash.text);
            if(!tmp)
                NULL;
            // printf("TEMP %s\n", tmp);
            stash.text = NULL;
            return tmp;
    }
    if(len != 0 && idx != -1) {
        
        tmp = splice_string(&stash.text,idx);
        // printf("TEMP %zu\n",ft_strlen(tmp));
        if(ft_strlen(tmp) == 1 && tmp[0] == '\n')
                return NULL;
        // printf("STASH AFTER %s\n",stash.text);
        return tmp;
    }
    if(len != 0 && idx == 0) {
        tmp = splice_string(&stash.text,idx);
        // printf("TEMP %zu\n",ft_strlen(tmp));
        if(ft_strlen(tmp) == 1 && tmp[0] == '\n')
                return NULL;
        // printf("STASH AFTER %s\n",stash.text);
        return tmp;
    }
        

    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    recursive_read(fd,&read_byte,&buffer,&stash,&full_line);
    // free(buffer);
    return full_line;
}



// int main ()
// {
//     //###### MAIN
//     int fd = open("text.txt",O_RDONLY);
   
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     printf("########################### LINE >>>> : %s\n", get_next_line(fd));
//     // printf("RESULT %s\n", check_eof(&"PAVIT"));
   

// }