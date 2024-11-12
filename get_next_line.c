/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:01:30 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/12 10:37:17 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*fill_stash(int fd, char *stash)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while ((!ft_strchr(buffer, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			perror("read");
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash = fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = fill_line(stash);
	stash = create_stash(stash);
	return (line);
}

int main(void)
{
    char *fileName = "./test.txt";
    int fd = open(fileName, O_RDWR);
	int i = 0;

    if (fd == -1) {
        perror("open");
        return 1;
    }
	while (i < 50000)
	{
		char *line = get_next_line(fd);
		if (line)
		{
			printf("%d. %s\n", i, line);
		}
		else
			break;
		i++;
		free(line);
	}
    close(fd);
    return 0;
}
