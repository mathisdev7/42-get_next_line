/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:01:30 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/11 11:37:18 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *get_next_line(int fd)
{
	ssize_t		i;
	int	j;
    char		*buf;
	static char	*stash;
	ssize_t		fd_read;
	char		*result;
    
	buf = malloc(BUFFER_SIZE + 1 + 30);
	result = malloc(BUFFER_SIZE + 1 + 30);
	if (!stash)
		stash = malloc(BUFFER_SIZE + 1);
	i = 0;
	j = 0;
	if (!buf || !result)
		return (NULL);
    fd_read = read(fd, buf, 5);
    if (fd_read == -1)
	{
		perror("read");
		free(buf);
		return (NULL);
    }
	if (stash[0])
	{
		while (stash[j])
		{
			buf[i] = stash[j];
			stash[j] = '\0';
			j++;
			i++;
		}
	}
	j = 0;
	while (i < fd_read)
	{
		if (buf[i] == '\n')
		{
			stash[j++] = buf[i + 1];
			stash[j] = '\0';
			i++;
		}
		else
		{
			result[i] = buf[i];
			i++;
		}
	}
	result[i] = '\0';
    buf[fd_read] = '\0';
    return (result);
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
	while (i < 5)
	{
		char *line = get_next_line(fd);
		printf("%d. %s\n", i, line);
		i++;
		free(line);
	}
    close(fd);
    return 0;
}
