/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:13:09 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 11:24:10 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_input_fd(t_cmd *cmd, t_pipe *ps)
{
	check_error(pipe(ps->pipe_fds + (cmd->index * 2) % 4), "pipe");
	if (cmd->index != 0)
		cmd->input = *(ps->pipe_fds + (cmd->index * 2 - 2) % 4);
}

void	set_output_fd(t_cmd *cmd, t_pipe *ps)
{
	if (cmd->index != ps->cmd_count - 1)
		cmd->output = *(ps->pipe_fds + (cmd->index * 2 + 1) % 4);
}
