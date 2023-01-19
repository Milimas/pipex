/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:23:52 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 12:19:45 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_error(int status, char *cmd, char *s)
{
	if (status == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		if (*cmd)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
		}
		perror(s);
		exit(EXIT_FAILURE);
	}
	return (status);
}
