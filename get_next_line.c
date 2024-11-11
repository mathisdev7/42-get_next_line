/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:01:30 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/11 16:19:22 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char *get_next_line(int fd)
{
	ssize_t		i;
	int			j;
    char		*buf;
	static char	*stash;
	ssize_t		fd_read;
	char		*result;
    
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);

	if (!stash)
		stash = malloc(BUFFER_SIZE + 1);
	result = malloc(ft_strlen(stash) + BUFFER_SIZE + 1);
	if (!result || !stash)
	{
		free(buf);
		return (NULL);
	}
	i = 0;
	fd_read = read(fd, buf, BUFFER_SIZE);
	if (fd_read == -1)
	{
		perror("read");
		free(buf);
		free(result);
		return (NULL);
	}
	buf[fd_read] = '\0';
	while (stash[i])
	{
		result[i] = stash[i];
		fd_read -= 1;
		i++;
	}
	result[i] = '\0';
	j = 0;
	while (j < fd_read && buf[j] && buf[j] != '\n')
		result[i++] = buf[j++];
	if (buf[j] == '\n')
	{
		result[i + 1] = buf[j];
		i++;
		j++;
	}
	result[i] = '\0';
	i = 0;
	while (buf[j])
	{
		if (buf[j] != '\n')
			stash[i++] = buf[j];
		j++;
	}
	stash[i] = '\0';
	free(buf);
    return (result);
}

int main(void)
{
    char *fileName = "./test.txt";
    int fd = open(fileName, O_RDWR);
	int i = 0;
	int k = 0;

    if (fd == -1) {
        perror("open");
        return 1;
    }
	while (i < 12)
	{
		char *line = get_next_line(fd);
		if (line)
		{
			while (line[k])
			{
				if (line[k] == '\n')
					printf("backslash detected.\n");
				k++;
			}
			k = 0;
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
