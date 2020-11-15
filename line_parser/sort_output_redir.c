#include "../minishell.h"

int     find_redirection(char *line, int n)
{
    int     i;
    char    quote;

    i = -1;
    quote = 0;
    while (line[++i])
    {
        if (line[i] == '\\' && ++i)
            continue ;
        if ((line[i] == '"' || line[i] == '\'') && !quote)
            quote = line[i];
        else if (line[i] == quote)
            quote = 0;
        else if (!quote && line[i] == '>')
        {
            if (n == 0)
                return (i);
            n--;
        }
    }
    return (-1);
}

int     skip_file_name(char *line)
{
    int     i;
    char    quote;

    quote = 0;
    i = skip_char(line, ' ') - 1;
    while (line[++i])
    {
        if (line[i] == '\\' && ++i)
            continue ;
        if ((line[i] == '"' || line[i] == '\'') && !quote)
            quote = line[i];
        else if (line[i] == quote)
            quote = 0;
        else if (!quote && line[i] == ' ')
            break;
    }
    return (i);
}

void    sort_output_redir_helper(t_piped_cmd *list)
{
    int     start;
    int     end;
    char    *pre;
    char    *suff;
    int     i;
    int     len;

    // i should recode this part
    if (!list)
        return ;
    i = 0;
    while ((start = find_redirection(list->line, i)) != -1)
    {
        end = start + 1 + (list->line[start + 1] == '>');
        end += skip_file_name(list->line + end);
        if (i == 0)
        {
            pre = ft_substr(list->line, 0 , start);
            suff = ft_substr(list->line, end, ft_strlen(list->line));
            add_mem(pre);
            add_mem(suff);
            pre = ft_strjoin(pre, suff);
            len = ft_strlen(pre);
            suff = ft_substr(list->line, start, end - start);
            add_mem(list->line);
            list->line = ft_strjoin(pre, suff);
        }
        else
        {

        }
        
        i++;
    }
    sort_output_redir_helper(list->next);
}

void    sort_output_redir(t_cmd *list)
{
    if (!list)
        return ;
    sort_output_redir_helper(list->cmd);
    sort_output_redir(list->next);
}