# include "../minishell.h"

int	ft_cd(char **args, char ***envp)
{
	char *env_var[3];
	char	prev_dir;
	char	*cur_dir;

	prev_dir = 0;
	if (!args[0])
	{
		args[0] = ft_get_env_value("$HOME", (*envp));
	}
	else if (args[1])
	{
		//error
		FT_PUTSTR_ERR("bash : cd : TOO MANY ARGUMENT\n");
		return (1);
	}
	if ((prev_dir = !ft_strcmp(args[0], "-")))
	{
		if (!(args[0] = ft_get_env_value("$OLDPWD", (*envp))))
		{
			FT_PUTSTR_ERR("bash : cd : OLDPWD not SET : ERROR \n");
			return (1);
		}
	}
	if (args[0][0] == '~')
	{
		if (!(args[0] = ft_strjoin(ft_get_env_value("$HOME", (*envp)), &args[0][1])))
		{
			FT_PUTSTR_ERR("bash : cd : HOME not set : ERROR \n");
			return (1);
		}
	}
	if (chdir(args[0]) < 0)
	{
		FT_PUTSTR("bash : cd : No such file or directory\n");
		return (1);
	}
	cur_dir = ft_getcwd();
	if (prev_dir)
	{
		FT_PUTSTR(cur_dir);
		FT_PUTCHAR('\n');
	}
	env_var[0] = ft_strjoin("OLDPWD=", ft_get_env_value("$PWD", (*envp)));
	env_var[1] = ft_strjoin("PWD=", cur_dir);
	env_var[2] = NULL;
	ft_export(env_var, envp);
	return (0);
}
