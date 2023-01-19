/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:23:52 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/17 23:48:15 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_error(int status, char *s)
{
	if (status == -1)
	{
		perror(s);
		exit(errno);
	}
	return (status);
}
