/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 17:15:24 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_philo_life(void *arg)
{
	t_philo		*philos;
	long long	elapsed;

	philos = (t_philo *)arg;
	while (1)
	{
		sem_wait(philos->_time.lock);
		elapsed = gettime_ms() - philos->table->start_time;
		if (elapsed - philos->_time.last_mealtime > philos->table->time_to_die)
		{
			sem_post(philos->_time.lock);
			sem_wait(philos->table->write_lock);
			printf("%lld %d %s\n", elapsed, philos->philo_id, RED"died"RESET);
			sem_post(philos->table->death);
			break ;
		}
		sem_post(philos->_time.lock);
		precise_sleep(1);
	}
	return (NULL);
}
