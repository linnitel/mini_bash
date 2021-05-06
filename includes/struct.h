/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:38:46 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 20:54:39 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define PID_SIZE 1024

/*
** name = name of the variable
** value = value of the variable
** standard = is it a standard envp variable or added via export (takes values
** 0 if it was added by simply writing in the string, 1 if it is a standart and
** 2 if it was added via export)
*/

typedef struct		s_env
{
	char			*name;
	char			*value;
	short			standard;
	struct s_env	*next;
}					t_env;

/*
** name = name of the command (if it is redirect, the name is eaqual to empty
** string - "")
** argv = arguments of the command
** pipe = is there a pipe after the command (0 if there is no pipe and 1 if
** there is)
** redir = NULL if there is no redirect after the command. If there is one,
** it is stored in the variable.
*/
typedef struct		s_redir
{
	char			*file;
	char			r[2];
}					t_redir;

typedef struct		s_cmd
{
	char			*name;
	char			**argv;
	char			pipe;
	t_redir			*redir;
	int				fd_pipe[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

/*
** my_env = list of environmental variables
** cmd = list of commands
** pos = ??
** res = ??
** save_fd = variable that stores the copies of the closed 0 and 1 fds.
** pipe_fd = variables that stores the opened for pipe fds ??
** exit status = contains exit status of the process. if no errors occured
** it is eaqual to 0, otherwise it is eaqual to errno value.
*/

typedef struct		s_all
{
	t_env			*my_env;
	t_cmd			*cmd;
	char			*line;
	int				pos;
	int				res;
	int				save_fd[2];
	int				fdin;
	int				fdout;
	int				exit_status;
	int				semicol;
	pid_t			pid[PID_SIZE];
}					t_all;

#endif
