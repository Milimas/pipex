/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:58:04 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 12:09:57 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_paths(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	*cmd_file(char **envp, char *cmd)
{
	char	**paths;
	char	*path_tmp;
	char	*file;

	paths = envp;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths && cmd)
	{
		path_tmp = ft_strjoin(*paths, "/");
		file = ft_strjoin(path_tmp, cmd);
		free(path_tmp);
		if (access(file, X_OK) == 0)
			return (file);
		free(file);
		paths++;
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	exit(127);
	return (NULL);
}
