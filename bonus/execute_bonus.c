/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:12:27 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 06:00:15 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute(t_cmd *cmd)
{
	cmd->cpid = fork();
	check_error(cmd->cpid, "fork");
	if (cmd->cpid == 0)
	{
		set_input_fd(cmd, cmd->ps);
		set_output_fd(cmd, cmd->ps);
		if (access(cmd->file, 0))
			exit(127);
		if (cmd->output > -1)
			check_error(dup2(cmd->output, STDOUT_FILENO), "dup output");
		if (cmd->input > -1)
			check_error(dup2(cmd->input, STDIN_FILENO), "dup input");
		execve(cmd->file, cmd->args, NULL);
		check_error(-1, cmd->file);
	}
	close(cmd->input);
	close(cmd->output);
	free(cmd->file);
	free_split(cmd->args);
}
