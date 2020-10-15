# include "../minishell.h"

int	ft_output_redir(char **args, char ***envp)
{
	return (ft_redirections_helper(args, REDIR_WRITE));
/*	int fd;
	int new_line;
	char *line;
	char *text;
	int i;

	if (!(*args))
		printf("> : ZERO ARG ERROR\n");
	if ((fd = open(args[0], REDIR_WRITE)) < 0)
	{
		write(2, "ERROR \n", ft_strlen("ERROR \n"));
		return ;
	}
	line = (char*)malloc(BUFFER_TO_READ);
	text = "";
	while ((read(0, line, BUFFER_TO_READ)) > 0)
	        text = ft_strjoin(text, line);
	//write(fd, text, ft_strlen(text));
	//write(1, line, ft_strlen(text));
	// print the other parameters
	new_line = 0;
	if (args[1] && (new_line = (text[ft_strlen(text) - 1] == '\n')))
		text[ft_strlen(text) - 1] = '\0';
	i = 0;
	while (args[++i])
	{
		text = ft_strjoin(text, ft_strjoin(" ", args[i]));
	        if (!args[1])
	        {
	                ft_putchar_fd(' ', fd);
	                ft_putstr_fd(args[i], fd);
                }
	        ft_putchar_fd(' ', 1);
	        ft_putstr_fd(args[i], 1);

	}
	if (!g_next_cmd || g_next_cmd[0] != '>')
	{
		ft_putstr_fd(text, fd);
		if (new_line)
                	ft_putchar_fd('\n', fd);
        }
        ft_putstr_fd(text, 1);
        if (new_line)
        	ft_putchar_fd('\n', 1);
	close(fd);
	*/
}
