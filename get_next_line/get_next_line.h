/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:50:39 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/01/08 20:49:00 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char	*gnl_strjoin(char *line, const char *buff);
char	*gnl_strchr(char *buff, char c);
char	*get_buff(int fd);
void	*gnl_memcpy(void *dst, const void *src, size_t n);
char	*gnl_substr(char const *s, unsigned int start, size_t len);

char	*get_next_line(int fd);

#endif
