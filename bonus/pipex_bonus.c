/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:09:15 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/21 18:39:22 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_cmd(t_pipe *ps)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	ps->cmd = NULL;
	while (i < ps->cmd_count)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		check_error(-!cmd, "init command", "malloc");
		cmd->index = i;
		cmd->ps = ps;
		cmd->args = ft_split(ps->argv[i + 2 + ps->heredoc], ' ');
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

	if (argc < 5)
		exit(2);
	ps.heredoc = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		ps.heredoc = 1;
	if (ps.heredoc && argc < 6)
		exit(2);
	ps.argc = argc;
	ps.argv = argv;
	ps.envp = envp;
	ps.pipe_count = 2;
	ps.cmd_count = argc - 3 - ps.heredoc;
	ps.pipe_fds = ft_calloc(ps.pipe_count * 2, sizeof(int));
	ps.paths = get_paths(envp);
	init_cmd(&ps);
	execute_all(ps.cmd);
	return (wait_all(ps.cmd));
}
