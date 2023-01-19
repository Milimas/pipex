/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:12:27 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 10:41:33 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_cmd *cmd)
{
	cmd->cpid = fork();
	check_error(cmd->cpid, "fork");
	if (cmd->cpid == 0)
	{
		if (cmd->index == cmd->ps->cmd_count - 1)
			cmd->output = open(cmd->ps->argv[cmd->ps->argc - 1],
					O_RDWR | O_CREAT | O_APPEND * cmd->ps->heredoc
					| O_TRUNC * !cmd->ps->heredoc, 0666);
		if (cmd->index == 0 && !cmd->ps->heredoc)
			cmd->input = open(cmd->ps->argv[1], O_RDWR, 0666);
		check_error(cmd->output, "output");
		check_error(cmd->input, "input");
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
