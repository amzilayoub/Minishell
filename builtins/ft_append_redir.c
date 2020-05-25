# include "../minishell.h"

int	ft_append_redir(char **args, char ***envp)
{
	return (ft_redirections_helper(args, REDIR_APPEND));
}
