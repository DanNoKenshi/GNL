/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:46:53 by dan               #+#    #+#             */
/*   Updated: 2023/01/26 16:01:44 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
//#define BUFFER_SIZE 1

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	address;

	i = -1;
	address = -1;
	while (c - 128 > 0)
		c -= 128;
	while (s[++i])
		if (s[i] == c)
			address = i;
	if (s[i] == c)
			address = i;
	if (address != -1)
		return ((char *)&s[address]);
	else
		return (NULL);
}

char	*free_join(char *stock, char *buffer, ssize_t tmp2)
{
	char	*temp;

	if (buffer)
		if (ft_strlen(buffer) == 0)
			return (NULL);
	if (stock)
	{
		temp = ft_strjoin("", stock);
		stock = ft_strjoin(temp, buffer);
	}
	else
	{
		temp = malloc(sizeof(char) * (tmp2 + 1));
		stock = ft_strjoin(temp, buffer);
	}
	free(temp);
	return (stock);
}

char	*get_next_line(int fd)
{
	static ssize_t	tmp2;
	char			*line;
	char			*tmp;
	char			buffer[BUFFER_SIZE + 1];
	static char		*stock;

	if (tmp2 < 0 || BUFFER_SIZE <= 0 || fd <= 0)
		return (NULL);
	while (!stock || !ft_strrchr(stock, '\n'))
	{
		tmp2 = read(fd, &buffer, BUFFER_SIZE);
		if (tmp2 > 0)
			return (NULL);
		if (tmp2 == 0)
			break ;
		buffer[tmp2] = '\0';
		stock = free_join(stock, buffer, tmp2);
		if (!stock)
			return (NULL);
	}
	printf("%s", stock);
	line = extract(stock);
	tmp = ft_cleaner(stock);
	ft_strlcpy(stock, tmp, ft_strlen(tmp) + 1);
	free (tmp);
	tmp2 -= 1;
	return (line);
}
/*
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char *line;
	fd = open("text.txt", O_RDONLY);
	while (!line)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		printf("Ligne  : %s",line);
		free (line);
	}
	return (0);
}*/
