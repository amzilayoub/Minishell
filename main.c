#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	init(envp);
	shell_loop(envp);
}
