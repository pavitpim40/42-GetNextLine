
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
    // printf("LENGTH %zu\n",len);
    // printf("IDX %d\n",idx);
    front = (char *)malloc(idx+1 * (sizeof(char)));
    back =  (char *)malloc(len-idx+1 * (sizeof(char)));

    while(i < len && i < idx)
        front[j++] = (*stringPtr)[i++];

     front[j] = '\0';
    j = 0;
    i++; // skip \n
    // printf("FRONT %s\n",front);
    while(i < len)
        back[j++] = (*stringPtr)[i++];
     
    back[j] = '\0';
    // printf("BACK %s\n",back);
    free(*stringPtr); // ตัวที่ pass เข้ามาถูก free
    *stringPtr = back; // assign ให้เป็น string ใหม่ (เหมือน Modify)
    return front;   
}
// char *extract_stash(char **stashPtr,int idx)
// {
//     size_t len;
//     int i;
//     int j;
//     char *line;
//     char *rest;
 
//     i = 0;
//     j = 0;
//     len = ft_strlen(*stashPtr);
//     line = (char *)malloc(idx+1 * (sizeof(char)));
//     rest = (char *)malloc(len-idx+1 * (sizeof(char)));
      
//     while(i < len && i < idx)
//         line[j++] = (*stashPtr)[i++];
    
//     line[j] = '\0';
//     j = 0;
//     i++; // skip \n
//     while(i < len)
//         rest[j++] = (*stashPtr)[i++];
     
//     rest[j] = '\0';
//     free(*stashPtr);
//     *stashPtr = rest;
//     return line;   
// }

// void recursive_read(int fd,char **stashPtr,char **bufferPtr,int read_byte)
// {
//          *stashPtr = ft_strjoin(*stashPtr,*bufferPtr); 
//         if(read_byte != 0 && ft_stridx(*bufferPtr,'\n') == -1)
//           return  recursive_read(fd,stashPtr,bufferPtr,read_byte);
//         else
//           return;
// }

char *get_next_line(int fd)
{

    // GET NEXT LINE
     static char *stash;
   
    char *buffer;
    int read_btye;
    int idx;
    char *full_line;
    int BUFFSIZE = 1;
    // ##### #0 Validate

    // ###### #1 CHECK STASH 
    // IF CAN EXTRACT ==> RETURN SUDDENLY
    // ELSE ==> GO TO PROGRAM 2 (CONTINUE READING)
    idx = ft_terminate_idx(stash,'\n'); 
    if(idx != -1)
        return splice_string(&stash,idx);
   
      

     // ###### #2 CONTINUE READING PROGRAM
    buffer =  (char *)malloc(BUFFSIZE * sizeof(char));
    read_btye = read(fd,buffer,BUFFSIZE);
    idx = ft_terminate_idx(buffer,'\n');
    while(read_btye != 0 && idx == -1)
    {
        // UPDATE STASH AND RE READ
        stash = ft_strjoin(stash,buffer); 
        read_btye = read(fd,buffer,BUFFSIZE);
        idx = ft_terminate_idx(buffer,'\n');
    }
    // #### 3 SUMMARY : EXTRACT LINE and UPDATE STASH
    full_line = ft_strjoin(stash,splice_string(&buffer,idx));
    free(stash);
    stash = buffer; 
    return full_line;
          //   printf("FULLINE = %s\n",full_line);
        // printf("END GNL STASH = %s\n",stash);
    
}

int main ()
{
    //###### MAIN
    int fd = open("test.txt",O_RDONLY);
   
    printf("RESULT : %s\n", get_next_line(fd));
    printf("RESULT : %s\n", get_next_line(fd));
    printf("RESULT : %s\n", get_next_line(fd));
  

}