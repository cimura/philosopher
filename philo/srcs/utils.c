/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:44 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/10 18:13:41 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

long long	gettime_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(t_philo *philos, long long milisec)
{
	long long	start;

	start = gettime_ms();
	while ((gettime_ms() - start) < milisec && !is_end(philos))
		usleep(500);
}

void	print_error(const char *message)
{
	write(STDERR_FILENO, RED, ft_strlen(RED));
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, RED, ft_strlen(RED));
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

void	ft_mutex(pthread_mutex_t *mutex, int flag)
{
	int	mutex_value;

	mutex_value = -1;
	if (flag == INIT)
		mutex_value = pthread_mutex_init(mutex, NULL);
	else if (flag == DESTROY)
		mutex_value = pthread_mutex_destroy(mutex);
	else if (flag == LOCK)
		mutex_value = pthread_mutex_lock(mutex);
	else if (flag == UNLOCK)
		mutex_value = pthread_mutex_unlock(mutex);
	if (mutex_value != 0)
		print_error("The return value of mutex func is bad...");
}
