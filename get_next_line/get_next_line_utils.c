/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:57:33 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/01/08 08:17:56 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	s = (const char *)src;
	d = (char *)dst;
	if (!s && !d)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	s1len = gnl_strchr((char *)s1, 0) - s1;
	s2len = gnl_strchr((char *)s2, 0) - s2;
	str = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	gnl_memcpy(str, s1, s1len);
	gnl_memcpy(str + s1len, s2, s2len);
	str[s1len + s2len] = 0;
	free(s1);
	return (str);
}

char	*gnl_strchr(char *buff, char c)
{
	if (buff != NULL)
	{
		while (*buff && *buff != c)
			buff++;
		if (*buff == c)
			return (buff);
	}
	return (NULL);
}

char	*get_buff(int fd)
{
	char	*buff;
	ssize_t	rbytes;

	buff = malloc(BUFFER_SIZE + 1);
	rbytes = read(fd, buff, BUFFER_SIZE);
	if (rbytes > 0 && rbytes <= BUFFER_SIZE)
	{
		buff[rbytes] = 0;
		return (buff);
	}
	free(buff);
	return (NULL);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (len > (size_t)(gnl_strchr((char *)s + start, 0) - s + start))
		len = gnl_strchr((char *)s + start, 0) - s + start;
	if (len <= 0 || !s)
		return (NULL);
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	gnl_memcpy(sub, s + start, len);
	sub[len] = 0;
	return (sub);
}
