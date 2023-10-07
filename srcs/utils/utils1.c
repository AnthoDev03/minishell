#include "../../include/minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2 || !(res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	**ft_split(const char *str, char c)
{
	int		i = 0, j = 0, k;
	char	**tab;

	i = 0, j = 0, k = 0;
	tab = malloc((ft_strlen(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		j = i;
		while (str[j] && str[j] != c)
			j++;
		if (j > i)
		{
			tab[k] = malloc(j - i + 1);
			if (tab[k])
			{
				strncpy(tab[k], str + i, j - i);
				tab[k][j - i] = 0;
				k++;
			}
		}
		i = j;
	}
	tab[k] = NULL;
	return (tab);
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
