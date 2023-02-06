

#include <stdlib.h>
#include <stdio.h>

size_t ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int main ()
{
  char *buf;

  buf = malloc(sizeof(char) * 5);
  int len = (int)ft_strlen(buf);

  printf("%s\n", buf);
  printf("%d\n", len);
  free(buf);

  return (0);
}