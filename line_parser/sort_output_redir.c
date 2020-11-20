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
        else if (!quote && (line[i] == '>' || line[i] == '<'))
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
    int     where_to_cut;
    int     filename;
    int     len;
    int     tmpLen;

    // i should recode this part
    if (!list)
        return ;
    where_to_cut = -1;
    i = 0;
    where_to_cut = find_redirection(list->line, i);
    while ((start = find_redirection(list->line, i)) != -1)
    {
        if (i == 0)
            add_mem(list->line);
        filename = start + 1 + (list->line[start + 1] == '>');
        filename += skip_file_name(list->line + filename);
        if ((end = find_redirection(list->line, i + 1)) == -1)
            end = ft_strlen(list->line);
        // joining the command with the argument
        pre = ft_substr(list->line, 0, where_to_cut);
        suff = ft_substr(list->line, filename, abs(filename - end));
        add_mem(pre);
        add_mem(suff);
        pre = ft_strjoin(pre, suff);
        tmpLen = ft_strlen(pre);
        // joining the redirection with the command
        suff = ft_substr(list->line, where_to_cut, filename - where_to_cut);
        pre = ft_strjoin(pre, suff);
        add_mem(pre);
        add_mem(suff);
        // suff = ft_substr(list->line, filename + abs(filename - end), ft_strlen(list->line));
        // joining the last of the line, with the command and redirection
        list->line = ft_strjoin(pre, list->line + filename + abs(filename - end));
        where_to_cut = tmpLen;
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