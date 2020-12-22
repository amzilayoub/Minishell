# include "minishell.h"


void    push_back(t_shell_env **list, char *var)
{
    if ((*list))
        push_back(&(*list)->next, var);
    else
    {
        (*list) = (t_shell_env*)malloc(sizeof(t_shell_env));
        (*list)->var = var;
        (*list)->next = NULL;
    }
}


void    print_shell_env(t_shell_env *list)
{
    if (!list)
        return ;
    print_single_var(list->var);
    print_shell_env(list->next);
}

void    remove_shell_env(t_shell_env **list, char *key)
{
    t_shell_env *prev;
    t_shell_env *pointer;

    if (ft_strncmp((*list)->var), key)
    {
        prev = (*list)->next;
        free((*list)->var);
        free((*list));
        (*list) = prev;
        return ;
    }
    pointer = (*list);
    prev = NULL;
}