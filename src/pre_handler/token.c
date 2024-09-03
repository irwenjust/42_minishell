#include "minishell.h"

t_token *new_token(char *input, t_token_type type, bool merge)
{
    t_token *token;

    //malloc token
    token = ft_calloc(1, sizeof(t_token));
    if (!token)
        return (NULL);
    //init token
    token->input = input;
    token->type = type;
    token->merge = merge;
    return (token);
}

int add_token(char *input, t_token_type type, bool merge)
{
    t_token *token;

    token = new_token(input, type, merge);
    if (!token || !input)
        return (0);
    ft_lstadd_back(&ms()->lexer_tk, ft_lstnew(token));
    return(ft_strlen(input));
}

void delete_token(t_token *token)
{
    if (!token)
        return ;
    ft_free(token->input);
    ft_free(token);
}

t_token *token_manager(t_manager mg)
{
    static t_list *current = NULL;

    if (mg == RESET)
        current = ms()->lexer_tk;
    else if (mg == CURRENT && current)
        return (current->content);
    else if (mg == NEXT)
        current = current->next;
    else if (mg == PREVIEW && current->next)
        return (current->next->content);
    return (NULL);
}