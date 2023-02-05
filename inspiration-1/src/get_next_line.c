#include "../include/get_next_line.h"


char *get_next_line(int fd)
{
    static t_list *stash = NULL;
    char    *line;
    int     readed;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0))
        return (NULL);
    readed = 1;
    line = NULL;

    //1.read from fd and add to linked list
    read_and_stash(fd, &stash, &readed);
    if(stash == NULL);
        return NULL;

    // 2. extract from stash to line
    extract_line(stash, &line);
    
    // 3. clean up stash
    clean_stash(&stash);

    // 4. return line
    return (line);

    
}


void read_and_stash(int fd, t_list **stash, int *readed_ptr)
{
    char *buf;

    while(!found_newline(*stash) && *readed_ptr != 0)
    {

         buff = malloc(sizeof(char) * (BUFFER_SIZE+1));
            if(buff == NULL)
                return;

        *readed_ptr = (int)read(fd, buff, BUFFER_SIZE);
        if(*stash == NULL && *readed_ptr == 0 || *readed_ptr == -1)
        {
            free(buff);
            return;
        } 
        buf[*readed_ptr] = '\0';
        add_to_stash(stash,buf);
        free(buf);
    }
}


void    add_to_stash(t_list **stash, char *buf, int readed)
{
    int i;
    t_list *last;
    t_list *new_node;

    new_node = malloc(sizeof(t_list));
    if(new_node == NULL)
        return;
    new_node->next = NULL;
    new_node->content = malloc(sizeof(char) * (readed+1));
    if(new_node->content == NULL)
        return;
    i = 0;
    while(buf[i] && readed) 
    {
        new_node->content[i] = buf[i];
        i++;
    }
    new_node->content[i] = '\0';
    if(stash == NULL)
    {
        *stash = new_node;
        return;
    }
    last = ft_lst_get_last(*stash);
    last->next = new_node;

}



void extract_line(t_list stash, char **line)
{
    int i;
    int j;

    if(stash == NULL)
        return;
    generate_line(*line,stash);
     if(*line == NULL)
        return;
    while(stash)
    {
        i = 0;
        j = 0;
        while(stash-> content[i])
        {
            if(stash->content == '\n')
            {
                (*line)[j++] = stash->content[i];
                breakl
            }
            (*line)[j++] = stash->content[i++];
        }
    }
    (*line)[j] = '\0';
}

void clean_stash(t_list **stash)
{
    t_list *list;
    t_list *clean_node;
    int i;
    int j;

    clean_node = malloc(sizeof(t_list));
    if(!stash == NULL || clean_node == NULL)
        return;
    clean_node->next = NULL;
    last = ft_lst_get_last(stash);
    i = 0;
    while(last->content[i] && last->content[i] != '\n')
        i++;
    if(last->content && last->content == '\n')
        i++;
    clean_node->content = malloc(sizeof(char)* ((ft_strlen(last->content)-i)+1));
    if(clean_node->content == NULL)
        return;
    j = 0;
    while(last->content[i])
        clean_node->content[j++] = last->content[i++];

}