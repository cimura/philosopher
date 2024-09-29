/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:50:01 by sshimura          #+#    #+#             */
/*   Updated: 2024/09/29 13:50:14 by sshimura         ###   ########.fr       */
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

static void	valid_input(const char *str)
{
	int	len;

	len = 0;
	while (is_whitespace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Input should be positive!");
	if (!is_digit(*str))
		error_exit("Input should be number");
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (*str != '\0' && !is_whitespace(*str))
		error_exit("Input contains invalid characters!");
	if (len > 10)
		error_exit("Input is too big!");
}

static	long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("Input is too large!");
	return (num);
}

void	parse_input(t_table *table, char *argv[])
{
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr > 200)
		error_exit("The number of philosophers should be less than 200");
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
	if (table->time_to_die < 6e1
		|| table->time_to_eat < 6e1
		|| table->time_to_sleep < 6e1)
		error_exit("Time input should be over 60ms");
}
