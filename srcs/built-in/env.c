// env.c
#include "../../include/minishell.h"

void	env_command(void)
{
	char	**env;

	env = environ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
