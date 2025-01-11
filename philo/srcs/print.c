/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:44 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 10:22:58 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	ssize_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

void	print_error(const char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	print_state(int id, const char *state, t_table *table)
{
	long long	timestamp;

	timestamp = gettime_ms() - table->start_time;
	ft_mutex(&table->write, LOCK);
	if (!is_end(table->philos))
		printf("%lld %d %s\n", timestamp, id, state);
	ft_mutex(&table->write, UNLOCK);
}
