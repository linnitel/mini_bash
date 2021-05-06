/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabel <tisabel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:01 by tisabel           #+#    #+#             */
/*   Updated: 2021/03/16 21:51:31 by mazor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"
# include "struct.h"
# include <errno.h>

# define PROMPT "\x1b[36mmini_bash$ \x1b[0m"

/*
** General functions for reading input and processing arguments and variables
*/

int				check_digit(char *str);
int				clear_all(t_all *all);
char			**deconvert_env(t_env **env);
char			**convert_argv(t_cmd *lst);
char			*get_full_cmd_name(t_all *all, t_cmd *lst);
char			*get_var(t_env *my_env, char *var_name);
int				get_next_line(int fd, char **line, t_all *all);
int				dup2_closer(t_all *all, int fd, int std);
int				close_dup2_closer(t_all *all, int fd, int std);
void			free_null(char *ptr);

/*
** Parcer functions
*/

int				parser_string(t_all *all);
int				get_shielding(t_all *all, char **text);
int				get_variables(t_all *all, char **text);
int				get_strong_quotes(t_all *all, char **text);
int				get_quotes(t_all *all, char **text);
int				run_cmd(t_all *all);
int				start_cmd(t_all *all, t_cmd *lst);
int				start_execve(t_all *all, t_cmd *lst);
int				exec_command(t_all *all, t_cmd *cmd);
int				free_local(char **arr_1, char **arr_2, char **text, int ret);
int				get_spec(t_all *all, char **text);
int				check_syntax(t_all *all);
char			*syntax_err_text(char *line);
char			*syntax_err_flag_to_text(int flag);
int				trim_space_in_line(char **line);
int				check_shielding(char **line);

/*
** Cmd utils functions
*/

t_cmd			*cmdlast(t_cmd *lst);
void			cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd			*init_cmd(void);
int				is_null_cmd(t_cmd *lst);
void			clear_cmd(t_cmd **cmd_lst);
int				check_arg(char *argum);
int				put_value(char *argum, t_env **temp);

/*
** Env utils functions
*/

t_env			*init_env(void);
t_env			*copy_env(t_env *my_env);
int				count_env(t_env *my_env);
void			sort_env(t_env **my_env);
void			free_t_env(t_env **my_env);
int				change_env(t_all *all, char *var_name, char *new_value);
void			del_one_env(t_env *my_env);
int				convert_env(t_env **env_var, char **env, t_all *all);
t_env			*env_last(t_env *env);
int				add_arg(t_all *all, char *argum, t_env **my_env);
void			add_back_env (t_env **my_env, t_env *new_env);
t_env			*creat_env(char *argum, t_all *all);

/*
** buildin functions
*/

int				ft_echo(t_all *all, t_cmd *cmd);
int				ft_pwd(t_all *all, t_cmd *cmd);
int				ft_export(t_all *all, t_cmd *cmd);
int				ft_env(t_all *all, t_cmd *cmd);
int				ft_unset(t_all *all, t_cmd *cmd);
int				ft_cd(t_all *all, t_cmd *cmd);
int				ft_exit(t_all *all, t_cmd *cmd);

/*
** execve functions
*/

int				join_char(char **text, char c);
int				join_str(char **text, char *s);
void			trim_space(t_all *all);
char			**remalloc_args(char **args);
int				add_remalloc_argv(t_all *all, t_cmd *lst, int *i);
void			*free_array(char **text);

/*
** errors processing functions
*/

int				ft_error(char *name, char *text, int ret, t_all *all);
int				ret_err(t_all *all, char *text);

/*
** Pipe & redirect functions
*/

void			save_fds(t_all *all);
void			restore_fds(t_all *all);
int				exec_command_pipe(t_all *all, t_cmd **lst);
void			clear_redir(t_redir *redir);
int				check_redir(t_all *all, t_cmd *lst);
int				count_redir(t_redir *redir);
int				open_file(char redir[2], char *argum);
void			run_command_pipe(t_all *all, t_cmd *cmd);
int				redir_execute(t_all *all, t_cmd *lst, char redir,
					int *redir_type);
int				redirections(t_all *all, t_cmd *lst, int *fd, char redir);
int				redir_pipe(t_all *all, t_cmd **lst, int *fdin, int *fdout);
void			pipe_wait_process(t_all *all, int pipes_len);

/*
** Signals implementing functions
*/

void			init_signals(t_all *all, char c);
void			mute_signals(void);
void			catch_signals(t_all *all);
void			implement_signals(t_all *all);

#endif
