#include "minishell.h"

void	init_builtins(void)
{
	g_builtins[0] = &ft_echo;
	g_builtins[1] = &ft_cd;
	g_builtins[2] = &ft_pwd;
	g_builtins[3] = &ft_export;
	g_builtins[4] = &ft_unset;
	g_builtins[5] = &ft_env;
	g_builtins[6] = &ft_exit;
	g_builtins[7] = &ft_append_redir;
	g_builtins[8] = &ft_output_redir;
	g_builtins[9] = &ft_input_redir;
}

void	init_stdio(void)
{
	g_stdio_fd[0] = dup(0);
	g_stdio_fd[1] = dup(1);
}

void	init_env_var(char **envp)
{
	g_env_len = 0;
	while (envp[g_env_len])
		g_env_len++;
	g_env_available_index = g_env_len;
}

void	init(char **envp)
{
	g_cmd_list = NULL;
	g_pipe_cmd = ft_split("| >> > <", ' ');
	g_cmd_char = ft_split("echo cd pwd export unset env exit >> > <", ' ');
	g_read_from_file = 0;
	init_builtins();
	init_stdio();
	init_env_var(envp);
	//g_env_en = 0;
/*	g_escape_char = ft_split("\a \b \e \f \n \r \t \v \\ \' \?", ' ');
	g_escape_char_deci = ft_split("a b e f n r t v \\ ' \"", ' ');
	g_escape_char_hexa = ft_split("7 8 1B C A D 9 B 5C 27 22 3F ", ' ');
*/
}

int	main(int argc, char **argv, char **envp)
{
	init(envp);
	/*while (envp[g_env_len])
		g_env_len++;
	g_env_last_index = g_env_len - 1;
	*/
	shell_loop(envp);
}
