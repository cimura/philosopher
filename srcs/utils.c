/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:44 by sshimura          #+#    #+#             */
/*   Updated: 2024/09/29 00:47:37 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

long	gettime_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(long milisec)
{
	long	start;
	long	elapsed;
	long	time_left;

	start = gettime_ms();
	while (gettime_ms() - start < milisec)
	{
		elapsed = gettime_ms() - start;
		time_left = milisec - elapsed;
		if (time_left * 2 < milisec)
			usleep(milisec / 4);
		else
		{
			while (gettime_ms() - start < milisec)
			{
			}
		}
	}
}

void	error_exit(const char *message)
{
	printf(RED"%s\n"RESET, message);
	exit(EXIT_FAILURE);
}

void	print_state(int id, const char *state, t_table *table)
{
	long	timestamp;

	timestamp = gettime_ms() - table->start_time;
	ft_mutex(&table->write, LOCK);
	if (!is_dead(table->philos))
		printf("%ld %d %s\n", timestamp, id, state);
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
	else
		error_exit("mutex flag is not good");
	if (mutex_value != 0)
		error_exit("The return value of mutex func is bad...");
}
