#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *s1)
{
  int x;

  x = 0;
  while (s1[x] && s1[x] != '\n')
    x++;
  return (x);
}

char *ft_strjoin(char *s1, char *s2, int opt)
{
  char *ret;
  int i;
  int j;

  i = 0;
  j = 0;
  if (!(s1 || s2))
    return (NULL);
  if (!(ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
    return (NULL);
  while (s1[i] && s1[i] != '\n')
  {
    ret[i] = s1[i];
    i++;
  }
  while (s2[j] && s2[j] != '\n')
    ret[i++] = s2[j++];
  ret[i] = '\0';
  if (opt == 2)
    free(s1);
  return (ret);
}

int ft_test(char *buffer)
{
  int i;
  int j;

  i = -1;
  j = 0;
	while (buffer[++i])
		if (buffer[i] == '\n')
    {
      i = 0;
      while (buffer[i] != '\n')
        i++;
      while (buffer[++i])
        buffer[j++] = buffer[i];
      buffer[j] = '\0';
      return (1);
    }
  return (0);
}

int ft_read(char ***line, int fd, char *buffer)
{
  int ret;

  while ((ret = read(fd, buffer, BUFFER_SIZE)) >= 0)
  {
    buffer[ret] = '\0';
    if (!(**line = ft_strjoin(**line, buffer, 2)))
      return (-1);
    if (ft_test(buffer) == 1)
      return (1);
    if (ret == 0)
      return (0);
  }
  free(**line);
  return (-1);
}

int get_next_line(int fd, char **line)
{
  static char buffer[256][BUFFER_SIZE + 1];

  if (fd > 0 && BUFFER_SIZE > 0)
  {
    if (!(*line = ft_strjoin(buffer[fd], "", 1)))
      return (-1);
    if (ft_test(buffer[fd]) == 1)
      return (1);
    return (ft_read(&line, fd, buffer[fd]));
  }
  return (-1);
}
