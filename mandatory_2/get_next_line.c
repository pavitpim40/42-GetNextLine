
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
    char *tmp;
     printf("________ IN RECURSIVE __________\n");
     printf("BUFF B4 READ : %s, BUFF LEN %zu\n",*bufferPtr,ft_strlen(*bufferPtr));
    (*stashPtr).text = ft_strjoin((*stashPtr).text,*bufferPtr);
 
    *readBytePtr = read(fd,*bufferPtr,BUFFER_SIZE);
    *idxPtr = ft_newline_idx(*bufferPtr);
  

    printf("STASH : %s\n", (*stashPtr).text);
    printf("READ BYTE : %d\n", *readBytePtr);
    printf("BUFF : %s, BUFF LEN %zu\n",*bufferPtr,ft_strlen(*bufferPtr));
    printf("INDEX NEW LINE: %d\n",*idxPtr);
   
    if (*readBytePtr != 0 && *readBytePtr < BUFFER_SIZE)
    {      
          tmp = *bufferPtr;
         *bufferPtr = splice_string(&tmp,*readBytePtr);
         free(tmp);
    }
       
      printf("BUFF AFTER READ : %s, BUFF LEN %zu\n",*bufferPtr,ft_strlen(*bufferPtr));
       printf("_____________________________________________\n");
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
    idx = ft_newline_idx(stash.text);
    //  idx = ft_terminate_idx(stash.text,'\n');
    printf("TERMINATE IDX %d\n",idx);
    printf("OLD STASH %s\n",stash.text);
    printf("STASH LENNGTH %zu\n", ft_strlen(stash.text));
    if(idx == 0) // กรณีมี '\n'  อยู่หน้าสุด แล้วข้อความข้างหลังยังไม่ครบ 
        splice_string(&stash.text,idx); // update stash เป็น string ครึ่งหลัง
    else if(stash.text && idx != -1) // มีข้อความ และ มี '\n' ที่ idx
    {
        full_line = splice_string(&stash.text,idx); // เฉือนฝั่งหน้า
          printf("FULL LINE %s\n",full_line); 
        printf("STASH IN #2 %s\n",stash.text);
        if(full_line)
             return  full_line;
    } 

        
      

    buffer =  (char *)malloc(BUFFER_SIZE * sizeof(char));
    // #### 3 : TRY TO READ ONCE
    read_btye = read(fd,buffer,BUFFER_SIZE);
    idx = ft_newline_idx(buffer);
    printf("READ BYTE @ FIRST : %d\n",read_btye);
     printf("TERMINATE IDX @ FIRST %d\n",idx);
    if(read_btye != 0 && idx >0)
    {
        full_line = splice_string(&buffer,idx);
        stash.text = buffer;
        return full_line;
    }
    if(read_btye == 0 && ft_strlen(stash.text) == 0)
        return NULL;
    // else if(read_btye == 0 && ft_terminate_idx(stash.text, '\n') != ft_strlen(stash.text))
    else if(read_btye == 0 && idx != -1)
        return splice_string(&stash.text,idx);
    else if (read_btye == 0 && ft_terminate_idx(stash.text, '\n') == ft_strlen(stash.text))
    {
        if(stash.text)
            return splice_string(&stash.text,ft_strlen(stash.text));
    }
       
       
    // stash.text = ft_strjoin(stash.text,buffer);
    // ##### 4.1 : RECURSIVE READ ULTIL MET \n
    recursive_read(fd,&read_btye,&buffer,&stash,&idx);
    // #### 4.2 :  WHEN STOP RECURSIVE (MET \n) => CONCLUDE STRING
    
    printf("STASH BE4 FULL LINE : %s\n", stash.text);
    printf("AFTER RECURSIVE INX %d\n",idx);
    printf("BUFFER BE4 FULL LINE : %s\n",buffer);
    // idx = ft_newline_idx(stash.text);
    full_line = ft_strjoin(stash.text,splice_string(&buffer,idx));
    // full_line =ft_strjoin(stash.text,splice_string(&stash.text,idx));
    // printf("FULL LINE %s\n", full_line);
    free(stash.text);
   
    stash.text = buffer;
    //  free(buffer);
    // printf("STASH END GNL %s with LEN %zu\n",stash.text,ft_strlen(stash.text));
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

}