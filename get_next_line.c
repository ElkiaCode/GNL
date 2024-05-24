/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:21:04 by cparodi           #+#    #+#             */
/*   Updated: 2024/05/24 16:51:35 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_gnl(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*treat_gnl(char *storage, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		size_bytes;

	size_bytes = 1;
	if (!storage)
		storage = calloc(1, 1);
	while (size_bytes > 0)
	{
		size_bytes = read(fd, buffer, BUFFER_SIZE);
		if (size_bytes == -1)
			return (NULL);
		buffer[size_bytes] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*newline;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	storage = treat_gnl(storage, fd);
	if (storage == NULL)
		return (NULL);
	line = extract_gnl(storage);
	newline = ft_strchr(storage, '\n');
	if (newline)
	{
		temp = ft_strdup(newline + 1);
		free(storage);
		storage = temp;
	}
	else
	{
		free(storage);
		storage = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("./empty", O_RDONLY);
// 	line = get_next_line(fd);
// 	if (line == NULL)
// 		printf("Succes");
// 	i = 1;
// 	while (i <= 3)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	free(line);
// 	close(fd);
// 	return (0);
// }
