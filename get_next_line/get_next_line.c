/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 02:52:51 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/01/08 08:18:05 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*protect_on_error(char *buff, int fd)
{
	if (fd < 0)
		return (0);
	return (buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*lremind[OPEN_MAX];
	char		*buff;
	char		*tmp;

	while (!gnl_strchr(lremind[fd], '\n'))
	{
		buff = get_buff(fd);
		if (!buff)
		{
			line = lremind[fd];
			lremind[fd] = NULL;
			return (protect_on_error(line, fd));
		}
		lremind[fd] = gnl_strjoin(lremind[fd], buff);
		free(buff);
	}
	line = gnl_substr(lremind[fd],
			0, gnl_strchr(lremind[fd], '\n') - lremind[fd] + 1);
	tmp = lremind[fd];
	lremind[fd] = gnl_substr(gnl_strchr(lremind[fd], '\n') + 1,
			0, gnl_strchr(lremind[fd], 0) - lremind[fd]);
	free(tmp);
	return (line);
}
