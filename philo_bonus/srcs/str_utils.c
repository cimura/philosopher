/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:47:00 by cimy              #+#    #+#             */
/*   Updated: 2024/12/19 14:49:41 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static ssize_t	ft_strlen(const char *str)
{
	ssize_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}
static int	digit_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n > 0)
	{
		while (n > 0)
		{
			n = n / 10;
			count++;
		}
	}
	else
	{
		while (n < 0)
		{
			n = n / 10;
			count++;
		}
	}
	return (count);
}

static char	*malloc_memory(int n, int digit)
{
	char	*result;

	result = NULL;
	if (n < 0)
	{
		result = (char *)malloc(sizeof(char) * (digit + 2));
		if (result != NULL)
		{
			result[0] = '-';
			result[digit + 1] = '\0';
		}
	}
	else if (n >= 0)
	{
		result = (char *)malloc(sizeof(char) * (digit + 1));
		if (result != NULL)
			result[digit] = '\0';
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		digit;
	char	*result;

	digit = digit_count(n);
	result = malloc_memory(n, digit);
	if (result == NULL)
		return (NULL);
	while (digit > 0)
	{
		if (n >= 0)
			result[--digit] = (n % 10) + '0';
		else
			result[--digit + 1] = -(n % 10) + '0';
		n = n / 10;
	}
	return (result);
}

static void	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == NULL)
		return (NULL);
	ft_strcpy(result, (char *)s1);
	ft_strcpy(result + s1_len, (char *)s2);
	result[s1_len + s2_len] = '\0';
	return (result);
}