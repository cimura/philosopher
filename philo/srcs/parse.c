/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:50:01 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/09 22:24:38 by cimy             ###   ########.fr       */
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
		return (ERROR_STATUS);
	while (is_whitespace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (ERROR_STATUS);
	if (!is_digit(*str))
		return (ERROR_STATUS);
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (*str != '\0' && !is_whitespace(*str))
		return (ERROR_STATUS);
	if (len > 10)
		return (ERROR_STATUS);
  return (0);
}

static	long long	ft_atol(const char *str)
{
	long long	num;

	num = 0;
	if (valid_input(str) == ERROR_STATUS)
    return (ERROR_STATUS);
	while (is_whitespace(*str))
		str++;
	if (*str == '+')
		str++;
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		return (ERROR_STATUS);
	else if (num <= 0)
		return (ERROR_STATUS);
	return (num);
}

int	parse_input(t_table *table, char *argv[])
{
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr <= 0 || table->philo_nbr > 200)
		return (1);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = ERROR_STATUS;
	if (table->time_to_die < 6e1
		|| table->time_to_eat < 6e1
		|| table->time_to_sleep < 6e1
    || table->nbr_limit_meals <= 0)
		return (1);
  return (0);
}
