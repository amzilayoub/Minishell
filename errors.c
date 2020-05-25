# include "minishell.h"

char	set_error(char *error_msg)
{
	g_error_msg = error_msg;
	g_there_is_error = 1;
	return (g_there_is_error);
}

int	set_error_print(char *error_msg)
{
	set_error(error_msg);
	FT_PUTSTR_ERR(error_msg);
	return (THERE_IS_ERROR);
}
