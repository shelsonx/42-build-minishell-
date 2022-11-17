#include "../../includes/minishell.h"

void    exit_program(t_data *data)
{
    ft_close_fds(data->fds);
	ft_free_tab(data->pipeline);
	ft_free_fds(data->fds);
}