#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int		ft_strlen(const char *s)
{
	int	x;

	x = 0;
	while (s[x] && s[x] != '\n')
		x++;
	return (x);
}

char	*ft_strjoin(char *s1, char *s2, int opt)
{
	char	*d;
	int		len;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(d = (char *)malloc(len)))
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[y] && s2[y] != '\n')
		d[i++] = s2[y++];
	d[i] = '\0';
	if (opt == 2)
		free(s1);
	return (d);
}

int	ft_checkbn(char *buffer)
{
	int x;

	x = -1;
	while (buffer[++x])
		if (buffer[x] == '\n')
			return (1);
	return (0);
}

int	ft_read(int fd, char ***line, char *buffer)
{
	int ret;
	int x;
	int y;

	while ((ret = read(fd, buffer, BUFFER_SIZE)) >= 0)
	{
		x = 0;
		y = 0;
		buffer[ret] = '\0';
		if (!(**line = ft_strjoin(**line, buffer, 2)))
			return (-1);
		if (ft_checkbn(buffer))
		{
			while (buffer[x] != '\n')
				x++;
			while (buffer[++x])
				buffer[y++] = buffer[x];
			buffer[y] = '\0';
			return (1);
		}
		if (ret == 0)
			return (0);
	}
	free(**line);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	static	char	buffer[255][BUFFER_SIZE + 1];
	int				x;
	int				y;

	x = 0;
	y = 0;
	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		if (!(*line = ft_strjoin(buffer[fd], "", 1)))
			return (-1);
		if (ft_checkbn(buffer[fd]))
		{
			while (buffer[fd][x] != '\n')
				x++;
			while (buffer[fd][++x])
				buffer[fd][y++] = buffer[fd][x];
			buffer[fd][y] = '\0';
			return (1);
		}
		return (ft_read(fd, &line, buffer[fd]));
	}
	return (-1);
}

int main(int argc, char **argv)
{
  if (argc > 1)
  {
    int fd;
    char *line;
    int x;

    x = 1;
    fd = open(argv[1], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
      printf("%d) %s\n", x, line);
      free(line);
      x++;
    }
    printf("%d) %s", x, line);
    free(line);
    return (0);
  }
  return (-1);
}
