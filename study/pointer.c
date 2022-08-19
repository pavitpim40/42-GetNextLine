
#include <stdio.h>


int main ()
{
    char *stash = "Hello It's me";
    char store[] = "Hello It's Pavit";

    printf("%s\n",stash);
    printf("%s\n",&stash[0]);
    printf("%p\n",&stash);
   

    printf("%s\n",store);
    printf("%s\n",&store[0]);
    printf("%p\n",&store);
}