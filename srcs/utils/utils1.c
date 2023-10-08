#include "../../include/minishell.h"

static char *construct_path(const char *dir, const char *file)
{
    char *exec_path;
    char *complete_path;

    exec_path = ft_strjoin(dir, "/");
    complete_path = ft_strjoin(exec_path, file);
    if (access(complete_path, X_OK) == 0)
    {
        free(exec_path);
        return complete_path;
    }
    free(complete_path);
    free(exec_path);
    return NULL;
}

static char *get_exec_path_from_env(const char *file)
{
    char **paths;
    char *path;
    char *complete_path;
    int i;

    path = getenv("PATH");
    if (!path)
        return NULL;

    paths = ft_split(path, ':');
    i = 0;
    while (paths[i])
    {
        complete_path = construct_path(paths[i], file);
        if (complete_path)
            return complete_path;

        i++;
    }
    return NULL;
}

int ft_execvp(const char *file, char *const argv[])
{
    char *complete_path;

    if (access(file, X_OK) == 0)
    {
        execve(file, argv, environ);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    complete_path = get_exec_path_from_env(file);
    if (complete_path)
    {
        execve(complete_path, argv, environ);
        free(complete_path);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    perror("ft_execvp");
    return (-1);
}

