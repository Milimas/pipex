/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:12:27 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 12:23:14 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_cmd *cmd)
{
	cmd->cpid = fork();
	check_error(cmd->cpid, *cmd->args, "fork");
	if (cmd->cpid == 0)
	{
		if (cmd->index == cmd->ps->cmd_count - 1)
			cmd->output = open(cmd->ps->argv[cmd->ps->argc - 1],
					O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);
		if (cmd->index == 0)
			cmd->input = open(cmd->ps->argv[1], O_RDWR, 0666);
		check_error(cmd->output, *cmd->args, "output");
		check_error(cmd->input, *cmd->args, "input");
		cmd->file = cmd_file(cmd->ps->paths, *cmd->args);
		if (cmd->output > -1)
			check_error(dup2(cmd->output, STDOUT_FILENO), "dup", "output");
		if (cmd->input > -1)
			check_error(dup2(cmd->input, STDIN_FILENO), "dup", "input");
		execve(cmd->file, cmd->args, NULL);
		check_error(-1, "execve", *cmd->args);
	}
	close(cmd->input);
	close(cmd->output);
	free(cmd->file);
	free_split(cmd->args);
}
