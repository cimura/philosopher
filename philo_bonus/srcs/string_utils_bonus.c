/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:47:00 by cimy              #+#    #+#             */
/*   Updated: 2025/01/07 18:19:05 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	digit_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int num)
{
	int		digit;
	char	*result;

	digit = digit_count(num);
	result = malloc(sizeof(char) * (digit + 1));
	if (result == NULL)
		return (NULL);
	result[digit] = '\0';
	if (num == 0)
		result[0] = '0';
	while (num != 0)
	{
		digit--;
		result[digit] = (num % 10) + '0';
		num = num / 10;
	}
	return (result);
}

ssize_t	ft_strlen(char *str)
{
	ssize_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		ri;
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	ri = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == NULL)
		return (NULL);
	while (s1[i] != '\0')
		result[ri++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		result[ri++] = s2[i++];
	result[s1_len + s2_len] = '\0';
	return (result);
}
