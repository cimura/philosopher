/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:44 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/17 18:03:25 by sshimura         ###   ########.fr       */
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
	while (gettime_ms() - start < milisec)
		usleep(100);
}

void	print_error(const char *message)
{
	printf(RED"%s\n"RESET, message);
}

void	print_state(int id, const char *state, t_table *table)
{
	long long	timestamp;

	timestamp = gettime_ms() - table->start_time;
	printf("%lld %d %s\n", timestamp, id, state);
}

// void	ft_mutex(pthread_mutex_t *mutex, int flag)
// {
// 	int	mutex_value;

// 	mutex_value = -1;
// 	if (flag == INIT)
// 		mutex_value = pthread_mutex_init(mutex, NULL);
// 	else if (flag == DESTROY)
// 		mutex_value = pthread_mutex_destroy(mutex);
// 	else if (flag == LOCK)
// 		mutex_value = pthread_mutex_lock(mutex);
// 	else if (flag == UNLOCK)
// 		mutex_value = pthread_mutex_unlock(mutex);
// 	if (mutex_value != 0)
// 		print_error("The return value of mutex func is bad...");
// }
