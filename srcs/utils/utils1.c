#include "../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
int	ft_execvp(const char *file, char *const argv[])
{
	char	**paths;
	char	*path;
	char	*exec_path;
	int		i;
	char	*complete_path;

	path = getenv("PATH");
	i = 0;
	if (!path || access(file, X_OK) == 0)
	{
		execve(file, argv, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	paths = ft_split(path, ':');
	while (paths[i])
	{
		exec_path = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(exec_path, file);
		if (access(complete_path, X_OK) == 0)
		{
			execve(complete_path, argv, environ);
			free(complete_path);
			free(exec_path);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(complete_path);
		free(exec_path);
		i++;
	}
	perror("ft_execvp");
	return (-1);
}
