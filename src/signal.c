#include "minishell.h"

/*void    handle_sigint(int signal)
{
    
}*/

void singal_default(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}