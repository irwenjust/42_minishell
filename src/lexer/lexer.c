#include "minishell.h"

bool check_quote(void)
{
    int i;
    char quote;
    bool start_quote;

    i = 0;
    quote = '\"';
    start_quote = false;
    while (ms()->input[i])
    {
        if (!start_quote && ft_strchr("\"\'", ms()->input[i]))
        {
            quote = ms()->input[i];
            start_quote = true;
        }
        else if (start_quote && ms()->input[i] == quote)
            start_quote = false;
        i++;
    }
    if (start_quote)
    {
        ft_putstr_fd("minishell: unclosed quotes.\n", 2);
        return (false);
    }
    return (true);
}

//还没有写道merge token的地方，所以不太理解这个merge的原理，可能回头写到那里能懂啥意思
bool check_mergeable(char *need_match, char *input, int end)
{
    if (!input[end])
        return (false);
    //if need match is special symbol, the end is quote, for quote match quote is ok, for <>|space, why find the quote end???
    if (!ft_strcmp("<>\'\"| ", need_match) && ft_strchr("\"\'", input[end]))
        return (true);
	//when start match is quote, the end+1 is not <>|space, why????????
    if (ft_strchr("\"\'", need_match[0]) && !ft_strchr("<>| ", input[end + 1]))
        return (true);
    return (false);
}

//find the end when meet quote or ?normal string?
int find_match(char *need_match, char *input)
{
    int end;
    char *tk_input;
    bool mergeable;

    end = 0;
    while (input[end] && !ft_strchr(need_match, input[end]))
        end++;
    mergeable = check_mergeable(need_match, input, end);
    tk_input = ft_substr(input, 0, end);
    if (need_match[0] == '"')
        add_token(tk_input, TK_DOUBLE_QT, mergeable);
    else if (need_match[0] == '\'')
        add_token(tk_input, TK_SINGLE_QT, mergeable);
    else
        add_token(tk_input, TK_TERM, mergeable); //?????
    return (end);
}

//lexer function
void lexer(void)
{
    int i;

    i = 0;
    while (ms()->input[i])
    {
        if (ms()->input[i] == ' ')
            i++;
        else if (ms()->input[i] == '|')
            i += add_token(ft_strdup("|"), TK_PIPE, false); //????ft_strdup, can just "|" ">>"?
        else if (!ft_strncmp(&(ms()->input[i]), "<<", 2))
            i += add_token(ft_strdup("<<"), TK_HEREDOC, false);
        else if (!ft_strncmp(&(ms()->input[i]), ">>", 2))
            i += add_token(ft_strdup(">>"), TK_APPEND, false);
        else if (ms()->input[i] == '<')
            i += add_token(ft_strdup("<"), TK_IN_RE, false);
        else if (ms()->input[i] == '>')
            i += add_token(ft_strdup(">"), TK_OUT_RE, false);
        else if (ms()->input[i] == '"')
            i += find_match("\"", &ms()->input[i + 1]) + 2;
        else if (ms()->input[i] == '\'')
            i += find_match("\'", &ms()->input[i + 1]) + 2;
        else
            i += find_match("<>\'\"| ", &ms()->input[i]); //to find the end of cmd?
    }
}

