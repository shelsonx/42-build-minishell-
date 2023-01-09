#include "../../includes/minishell.h"

void			ft_pwd(t_builtin_vars *builtin_vars)
{
	char		*current_path;

	current_path = get_env_path("PWD", builtin_vars);
		if (!current_path)
		{
			printf("error"); //verificar o que colocar aqui
		}
		else
		{
			ft_putstr_fd(current_path, 1);
			free(current_path);
		}
	ft_putstr_fd("\n", 1);
}
