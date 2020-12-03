/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutahr <aboutahr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:56:12 by aboutahr            #+#    #+#             */
/*   Updated: 2020/10/26 14:04:43 by aboutahr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include "libft.h"
# include "GNL/get_next_line.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>

# define ARRAY_GROWTH 5
# define BUFFER_TO_READ 1000
# define FT_PUTSTR(STR) ft_putstr_fd(STR, 1)
# define FT_PUTSTR_ERR(STR) ft_putstr_fd(STR, 2)
# define FT_PUTCHAR(C) ft_putchar_fd(C, 1)
# define REDIR_WRITE (O_TRUNC | O_CREAT | O_WRONLY)
# define REDIR_APPEND (O_CREAT | O_APPEND | O_WRONLY)
# define THERE_IS_ERROR g_there_is_error
# define ERROR_MSG g_error_msg
# define FREE_EXIT_MODE 1
# define FREE_MODE 0

/*
**--------------------------------*
**struct of commands with params
**--------------------------------*
*/

typedef struct	s_single_command
{
	char					*line;
	char					**params;
	struct s_single_command	*next;
}				t_single_command;

typedef struct	s_piped_cmd
{
	char				*line;
	t_single_command	*single_command;
	struct s_piped_cmd	*next;
}				t_piped_cmd;

typedef	struct	s_cmd
{
	char			*line;
	t_piped_cmd		*cmd;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_mem_alloc
{
	void				*mem;
	struct s_mem_alloc	*next;
}				t_mem_alloc;

typedef	struct	s_arg_manip
{
	int		i;
	int		j;
	int		space;
	int		start;
	char	quote;
}				t_arg_manip;

/*
**------------------------------------------------------**
** Here some global variables for some functions
**------------------------------------------------------**
*/

void			open_stdio(void);
void			close_fd(void);
t_mem_alloc		*g_mem_alloc;
t_mem_alloc		*g_mem_perma;
t_cmd			*g_cmd_list;
int				g_stdio_fd[3];
int				**g_pipes_fd;
char			g_read_from_file;
char			**g_cmd_char;
char			**g_pipe_cmd;
int				g_pipes_count;
int				(*g_builtins[10])(char **args, char ***envp);
int				g_env_available_index;
int				g_env_len;
int				g_status;
char			*g_next_cmd;
char			g_there_is_error;
char			*g_error_msg;
char			g_first_dup_env;
char			g_is_piped;
pid_t			g_pid;
char			**g_envp;
char			*g_line;

/*
**------------------------------------------------------**
** MEMORY MANAGEMENT FUNCTIONS
**------------------------------------------------------**
*/

void			add_mem(void *mem);
void			free_memory(t_mem_alloc **list, int flag);

/*
**-------------------------------------------------**
** FUNCTIONS USED TO MANAGE THE INPUT
**-------------------------------------------------**
*/

void			init(char **envp);
void			treat_line(char *line);
void			treat_list(t_cmd *cmd_list);
void			treat_single_command(t_cmd *cmd_list);
void			print_list(t_cmd *list);
char			**get_arg(char *line, char **envp);
void			treat_cmd(t_cmd *list, char **envp);
void			sort_cmd_for_redirections(
								t_single_command **current,
								t_single_command **next);
void			call_commands(t_cmd *list, char ***envp);
void			set_pipes(void);
int				join_env_var(char **str, int index, char **envp);
int				skip_char(char *line, char c);
char			*shift_char(char *str);
int				is_redirection(char *red, char *line);
void			(*g_cmd_fun[4])(char *arg, char ***envp);
void			shell_loop(char **envp);
char			*shift_char(char *str);
int				skip_char(char *line, char c);
char			*ft_get_env_value(char *key, char **envp);
char			*ft_getcwd(void);

/*
**-------------------------------------------------**
** FUNCTIONS USED TO MANIPULATE THE LINKED LIST
**-------------------------------------------------**
*/

int				list_cmd_size(t_piped_cmd *list);
void			clear_cmd_list(t_cmd **list);
void			create_cmd_list(t_cmd **list, char *line);
void			add_cmd(t_piped_cmd **list, char *line);
void			add_mem_perma(void *mem);
void			add_single_command(t_single_command **list, char *line);

/*
**-------------------------------------------------**
** ERROR HANDLING FUNCTIONS
**-------------------------------------------------**
*/

char			set_error(char *error_msg);
char			check_semicolons(char *line);
char			check_pipes_error(char **line);
int				set_error_print(char *error_msg);
void			print_cmd_with_error(char *cmd, char *error_msg);

/*
**-------------------------------------------------**
** BUILTINS FUNCTIONS
**-------------------------------------------------**
*/

int				ft_echo(char **args, char ***envp);
int				ft_pwd(char **args, char ***envp);
int				ft_input_redir(char **args, char ***envp);
int				ft_output_redir(char **args, char ***envp);
int				ft_append_redir(char **args, char ***envp);
int				ft_env(char **args, char ***envp);
int				ft_export(char **args, char ***envp);
int				ft_unset(char **args, char ***envp);
int				ft_cd(char **args, char ***envp);
int				ft_exit(char **args, char ***envp);

/*
**-------------------------------------------------**
** BUILTINS HELPER FUNCTIONS
**-------------------------------------------------**
*/

int				ft_redirections_helper(char **args, int flags);
char			*ft_get_env_value(char *key, char **envp);
void			env_append(char *str, char ***envp);
void			sort_output_redir(t_cmd *list);
void			sort_output_redir_helper(t_piped_cmd *list);
void			call_single_command(
					t_piped_cmd *parent,
					t_single_command *list,
					char ***envp,
					int *pipe_index);

#endif
