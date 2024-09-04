#include "minishell.h"

static char *replace_keyword(char *str, char *old, char *new)
{
    int len;
    char *res;
    char *find_old;
    char *tmp;

    if (!str || !old || !new)
        return (NULL);
    len = ft_strlen(str) + ft_strlen(new) - ft_strlen(old);
    res = ft_calloc(len + 1, sizeof(char));
    if (!res)
        return (NULL);
    find_old = ft_strnstr(str, old, ft_strlen(str));
    if (!find_old)
        return (NULL);
    tmp = ft_substr(str, 0, (find_old - str));
    ft_strlcat(res, tmp, len + 1);
    ft_strlcat(res, new, len + 1);
    ft_strlcat(res, (find_old + ft_strlen(old)), len + 1);
    ft_free(tmp);
    return (res);
}

static char *find_keyword(char *str)
{
    char *tmp;
    char *keyword;
    int i;

    tmp = ft_strnstr(str, "$", ft_strlen(str));
    if (tmp[1] == '?')
    {
        keyword = ft_strdup("$?");
        return (keyword);
    }
    i = 1;
    while (ft_isalnum(tmp[i]) || tmp[i] == '_')
        i++;
    keyword = ft_substr(tmp, 0, i);
    return (keyword);
}

static void expand_current(t_token *token)
{
    char *keyword;
    char *real_key;
    char *tmp;

    while (ft_strnstr(token->input, "$", ft_strlen(token->input)))
    {
        keyword = find_keyword(token->input);
        if (!ft_strcmp(keyword, "$?")) //???
            real_key = ft_itoa(ms()->exit);
        else
            real_key = get_env(keyword);
        tmp = token->input;
        token->input = replace_keyword(token->input, keyword, real_key);
        ft_free(keyword);
        ft_free(real_key);
        ft_free(tmp);
        
    }
}

void merge(t_list *lexer_tk)
{
    t_token *current;
    t_token *next;
    char *tmp;
    t_list *delete;

    // printf("2\n");
    while (lexer_tk)
    {
        
        current = lexer_tk->content;
        if (!lexer_tk->next)
            return ;
        if (!current->mergeable)
        {
            lexer_tk = lexer_tk->next;
            continue ;
        }
        next = lexer_tk->next->content;
        tmp = current->input;
        current->input = ft_strjoin(current->input, next->input);
        free(tmp);
        if (!next->mergeable)
            current->mergeable = next->mergeable;
        delete = lexer_tk->next;
        lexer_tk->next = lexer_tk->next->next;
        ft_lstdelone(delete, (void *)delete_token);
        
    }
}

void expander(void)
{
    t_list *token;
    t_token *current;

    token = ms()->lexer_tk;
    while (token)
    {
        current = (t_token *)token->content;
        if (current->type == TK_HEREDOC)
            token = token->next;
        else if (current->type == TK_DOUBLE_QT || current->type == TK_KEYWORD)
            expand_current(current);
        token = token->next;
    }
    merge(ms()->lexer_tk);
}