/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:23:52 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 01:57:58 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_error(int status, char *s)
{
	if (status == -1)
	{
		perror(s);
		exit(errno);
	}
	return (status);
}
