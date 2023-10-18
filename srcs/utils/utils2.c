/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:38:41 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:38:43 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../gc/gc.h"
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

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

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

char** copieEnviron(char **environOrig) {
    int i = 0;
    // Compter le nombre de chaînes dans environ
    while (environOrig[i]) {
        i++;
    }

    // Allouer de la mémoire pour le nouveau tableau
    char **copie = (char **)gc_malloc((i + 1) * sizeof(char *));
    if (!copie) {
        perror("Erreur d'allocation mémoire");
        exit(1);
    }

    for (int j = 0; j < i; j++) {
        copie[j] = ft_strdup(environOrig[j]);
        if (!copie[j]) {
            perror("Erreur d'allocation mémoire");
            exit(1);
        }
    }

    copie[i] = NULL; // marqueur de fin du tableau

    return copie;
}


