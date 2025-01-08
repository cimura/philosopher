/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/08 20:32:24 by cimy             ###   ########.fr       */
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
		sem_wait(philos->_meal.lock);
		elapsed = gettime_ms() - philos->table->start_time;
		if (elapsed - philos->_time.last_mealtime > philos->table->time_to_die)
		{
			sem_post(philos->_meal.lock);
			sem_wait(philos->table->write_lock);
			printf("%lld %d %s\n", elapsed, philos->philo_id, RED"died"RESET);
			sem_post(philos->table->death);
			while (1)
				precise_sleep(100);
		}
		sem_post(philos->_meal.lock);
		precise_sleep(1);
	}
	return (NULL);
}
