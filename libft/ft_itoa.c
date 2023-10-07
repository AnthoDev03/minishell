/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:26:17 by anthrodr          #+#    #+#             */
/*   Updated: 2023/04/14 11:26:21 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_numlen(int n)
{
	size_t	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_itoa_positive(unsigned int num, char *str, size_t len)
{
	while (num)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

static char	*ft_itoa_negative(int n, char *str, size_t len)
{
	unsigned int	num;

	str[0] = '-';
	num = (unsigned int)(-n);
	return (ft_itoa_positive(num, str, len));
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = ft_numlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		return (ft_itoa_negative(n, str, len));
	else
		return (ft_itoa_positive((unsigned int)n, str, len));
}
