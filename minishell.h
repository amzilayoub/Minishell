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

# define ARRAY_GROWTH 5
# define BUFFER_TO_READ 1000
# define FT_PUTSTR(STR) ft_putstr_fd(STR, 1)
# define FT_PUTSTR_ERR(STR) ft_putstr_fd(STR, 2)
# define FT_PUTCHAR(C) ft_putchar_fd(C, 1)
# define REDIR_WRITE O_TRUNC | O_CREAT | O_WRONLY
# define REDIR_APPEND O_CREAT | O_APPEND | O_WRONLY
# define THERE_IS_ERROR g_there_is_error
# define ERROR_MSG g_error_msg

/*
**--------------------------------*
**struct of commands with params
**--------------------------------*
*/

typedef struct s_piped_cmd
{
	char	*line;
	char	**params;
	struct s_piped_cmd *next;
}		t_piped_cmd;

typedef	struct	s_cmd
{
	char		*line;
	t_piped_cmd	*cmd;
	struct s_cmd	*next;
}		t_cmd;


/*
**------------------------------------------------------**
** Here some global variables for some functions
**------------------------------------------------------**
*/

//t_piped_cmd	*g_cmd_tmp;
t_cmd		*g_cmd_list;
int		g_stdio_fd[2];
int		**g_pipes_fd;
char		g_read_from_file;
char		**g_cmd_char;
char		**g_pipe_cmd;
int		g_pipes_count;
int		(*g_builtins[10])(char **args, char ***envp);
int		g_env_available_index;
int		g_env_len;
int		g_status;
char		*g_next_cmd;
char		g_there_is_error;
char		*g_error_msg;

/*
**-------------------------------------------------**
** FUNCTIONS USED TO MANAGE THE INPUT
**-------------------------------------------------**
*/

void	(*g_cmd_fun[4])(char *arg, char ***envp);
void	shell_loop(char **envp);
void	clear_cmd_list(t_cmd **list);
void	create_cmd_list(t_cmd **list, char *line);
void	add_cmd(t_piped_cmd **list, char *line);
char	*shift_char(char *str);
int	skip_char(char *line, char c);
int	list_cmd_size(t_piped_cmd *list);
char	*ft_get_env_value(char *key, char **envp);
char	*ft_getcwd(void);


/*
**-------------------------------------------------**
** ERROR HANDLING FUNCTIONS
**-------------------------------------------------**
*/

char	set_error(char *error_msg);
char	check_semicolons(char *line);
char	check_pipes_error(char **line);
int	set_error_print(char *error_msg);

/*
**-------------------------------------------------**
** BUILTINS FUNCTIONS
**-------------------------------------------------**
*/
int	ft_echo(char **args, char ***envp);
int	ft_pwd(char **args, char ***envp);
int	ft_input_redir(char **args, char ***envp);
int	ft_output_redir(char **args, char ***envp);
int	ft_append_redir(char **args, char ***envp);
int	ft_env(char **args, char ***envp);
int	ft_export(char **args, char ***envp);
int	ft_unset(char **args, char ***envp);
int	ft_cd(char **args, char ***envp);
int	ft_exit(char **args, char ***envp);
/*
**-------------------------------------------------**
** BUILTINS HELPER FUNCTIONS
**-------------------------------------------------**
*/
int	ft_redirections_helper(char **args, int flags);

#endif
