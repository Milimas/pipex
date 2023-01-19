/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:13:09 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 04:57:53 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_here_doc(t_cmd *cmd, t_pipe *ps)
{
	char	*buf;
	int		*here_doc;

	here_doc = malloc(sizeof(int) * 2);
	check_error(pipe(here_doc), "pipe");
	cmd->input = here_doc[0];
	check_error(cmd->input, "pipe here_doc");
	ft_putstr_fd("pipe heredoc> ", 1);
	buf = get_next_line(0);
	while (buf)
	{
		if (ft_strncmp(buf, ps->argv[2], ft_strlen(ps->argv[2])) == 0
			&& buf[ft_strlen(ps->argv[2])] == '\n')
			break ;
		ft_putstr_fd(buf, here_doc[1]);
		free(buf);
		ft_putstr_fd("pipe heredoc> ", 1);
		buf = get_next_line(0);
	}
	free(buf);
	close(here_doc[1]);
	free(here_doc);
}

void	set_input_fd(t_cmd *cmd, t_pipe *ps)
{
	if (cmd->index == 0 && ps->heredoc)
	{
		set_here_doc(cmd, ps);
	}
	else if (cmd->index == 0 && !ps->heredoc)
	{
		cmd->input = open(ps->argv[1], O_RDWR, 0666);
		check_error(cmd->input, ps->argv[1]);
	}
	else
	{
		cmd->input = *(ps->pipe_fds + cmd->index - 1);
		check_error(cmd->input, "pipe: input");
	}
}

void	set_output_fd(t_cmd *cmd, t_pipe *ps)
{
	if (cmd->index == ps->cmd_count - 1)
	{
		cmd->output = open(ps->argv[ps->argc - 1],
				O_RDWR | O_CREAT | O_APPEND * ps->heredoc
				| O_TRUNC * !ps->heredoc, 0666);
		check_error(cmd->output, ps->argv[ps->argc - 1]);
	}
	else
	{
		check_error(pipe(ps->pipe_fds + cmd->index), "pipe");
		cmd->output = *(ps->pipe_fds + cmd->index + 1);
		check_error(cmd->output, "pipe: output");
	}
}