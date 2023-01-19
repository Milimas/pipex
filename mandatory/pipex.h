/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:06:02 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/19 11:22:20 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

struct	s_pipe;

typedef struct s_cmd
{
	int				index;
	pid_t			cpid;
	int				input;
	int				output;
	char			*file;
	char			**args;
	struct s_pipe	*ps;
	void			*next;
}	t_cmd;

typedef struct s_pipe
{
	int		argc;
	char	**argv;
	t_cmd	*cmd;
	char	**paths;
	int		pipe_count;
	int		cmd_count;
	int		*pipe_fds;
}	t_pipe;

char	**get_paths(char **envp);
char	*cmd_file(char **envp, char *cmd);
void	free_split(char **split);
void	execute(t_cmd *cmd);
t_cmd	*lstlast(t_cmd *lst);
void	lstadd_back(t_cmd **lst, t_cmd *new);
int		check_error(int status, char *s);
void	set_here_doc(t_cmd *cmd, t_pipe *ps);
void	set_input_fd(t_cmd *cmd, t_pipe *ps);
void	set_output_fd(t_cmd *cmd, t_pipe *ps);

#endif