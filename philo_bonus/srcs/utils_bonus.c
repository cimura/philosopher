/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:44 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 17:24:36 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	gettime_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(long long milisec)
{
	long long	start;

	start = gettime_ms();
	while ((gettime_ms() - start) < milisec)
		usleep(1000);
}

void	print_error(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	print_state(int id, const char *state, t_table *table)
{
	long long	timestamp;

	sem_wait(table->write_lock);
	timestamp = gettime_ms() - table->start_time;
	printf("%lld %d %s\n", timestamp, id, state);
	sem_post(table->write_lock);
}
