


#include "get_next_line.h"


char    *get_next_line(int fd)
{
    // printf("%d\n",BUFFER_SIZE);
    char *result;
    char *buf = malloc((BUFSIZ + 1) * sizeof(char));
    if(buf == 0)
        return "";
    size_t read_byte;
    int index;
    do {
        read_byte = read(fd,buf,3);
       

        
    printf("READ BYTE %zu\n",read_byte);
    

        // if(read_byte == 0) // EOF
        // if(read_byte == -1) // error

        if(read_byte <= 3) {
        index = ft_stridx(buf,'\n');
        printf("INDEX %d\n",index);
        if(index != -1)
            result = ft_strjoin(result,ft_split(buf,'\n')[0]);
        else 
            result = ft_strjoin(result,buf);
        printf("RESULT %s\n",result);
    }
    } while (read_byte != 0 && index == -1);

    // } while (read_byte != 0 || read_byte != -1 || index != -1 );
   
    
  
    
    return "Hello";
}