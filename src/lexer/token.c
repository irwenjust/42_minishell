#include "minishell.h"

t_token *token_new(char *input, t_token_type type, bool merge)
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

    token = token_new(input, type, merge);
    if (!token || !input)
        return (0);
    ft_lstadd_back(&ms()->lexer_tk, ft_lstnew(token));
    return(ft_strlen(input));
}