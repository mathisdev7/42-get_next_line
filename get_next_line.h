/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:02:09 by mazeghou          #+#    #+#             */
/*   Updated: 2024/11/11 10:09:57 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

ssize_t	read(int fildes, void *buf, size_t nbyte);
int	open(const char *path, int oflag, ... );

# endif