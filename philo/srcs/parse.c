/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:50:01 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 17:03:20 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static inline	bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	valid_input(const char *str)
{
	int	len;

	len = 0;
	if (str == NULL || *str == '\0')
		return (ERR_STATUS);
	while (is_whitespace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (ERR_STATUS);
	if (!is_digit(*str))
		return (ERR_STATUS);
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (*str != '\0' && !is_whitespace(*str))
		return (ERR_STATUS);
	if (len > 10)
		return (ERR_STATUS);
	return (0);
}

static	long long	ft_atol(const char *str)
{
	long long	num;

	num = 0;
	if (valid_input(str) == ERR_STATUS)
		return (ERR_STATUS);
	while (is_whitespace(*str))
		str++;
	if (*str == '+')
		str++;
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		return (ERR_STATUS);
	else if (num <= 0)
		return (ERR_STATUS);
	return (num);
}

int	parse_input(t_table *table, char *argv[])
{
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr <= 0 || table->philo_nbr > 200)
		return (PARSE_ERR);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
	{
		table->nbr_limit_meals = ft_atol(argv[5]);
		if (table->nbr_limit_meals <= 0)
			return (PARSE_ERR);
	}
	else
		table->nbr_limit_meals = -1;
	if (table->time_to_die < 60
		|| table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (PARSE_ERR);
	return (0);
}
