#include "minishell.h"

// void expander(void)
// {
//     t_list *token;
//     t_token *current;

//     token = ms()->lexer_tk;
//     while (token)
//     {
//         current = (t_token *)token->content;
//         if (current->type == TK_HEREDOC)
//             token = token->next;
//         else if (current->type = TK_DOUBLE_QT || current->type == TK_KEYWORD)
//             expand_current(current);
//         token = token->next;
//     }
//     merge(ms()->lexer_tk);
// }