/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:09:15 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 12:21:21 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_cmd(t_pipe *ps)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	ps->cmd = NULL;
	while (i < ps->cmd_count)
	{
		cmd = malloc(sizeof(t_cmd));
		check_error(-!cmd, "init command", "malloc");
		cmd->index = i;
		cmd->ps = ps;
		cmd->args = ft_split(ps->argv[i + 2], ' ');
		if (!cmd->args)
			exit(EXIT_FAILURE);
		cmd->next = NULL;
		lstadd_back(&ps->cmd, cmd);
		i++;
	}
}

void	execute_all(t_cmd *cmd)
{
	while (cmd)
	{
		set_input_fd(cmd, cmd->ps);
		set_output_fd(cmd, cmd->ps);
		execute(cmd);
		cmd = cmd->next;
	}
}

int	wait_all(t_cmd *cmd)
{
	int	status;

	while (cmd->next)
	{
		waitpid(cmd->cpid, NULL, 0);
		free(cmd);
		cmd = cmd->next;
	}
	waitpid(cmd->cpid, &status, 0);
	free(cmd);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		return (status);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	ps;

	if (argc != 5)
		exit(2);
	ps.argc = argc;
	ps.argv = argv;
	ps.pipe_count = 2;
	ps.cmd_count = argc - 3;
	ps.pipe_fds = malloc(sizeof(int) * ps.pipe_count * 2);
	ps.paths = get_paths(envp);
	init_cmd(&ps);
	execute_all(ps.cmd);
	return (wait_all(ps.cmd));
}
