/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/17 13:51:54 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	taking_forks(t_philo *philos)
{
	if (is_dead(philos))
		return (0);
	if (philos->philo_id % 2 == 0)
	{
		if (sem_wait(philos->table->sem) < 0)
			return (1);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
		if (sem_wait(philos->table->sem) < 0)
			return (1);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
	}
	else
	{
		if (sem_wait(philos->table->sem) < 0)
			return (1);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
		if (sem_wait(philos->table->sem) < 0)
			return (1);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
	}
	return (0);
}

int	eating(t_philo *philos)
{
	taking_forks(philos);
	print_state(philos->philo_id,
		"is eating", philos->table);
	precise_sleep(philos, philos->table->time_to_eat);
	philos->table->meal_counter++;
	philos->last_mealtime = gettime_ms() - philos->table->start_time;
	if (sem_post(philos->table->sem) < 0)
		return (1);
	if (sem_post(philos->table->sem) < 0)
		return (1);
	return (0);
}

void	thinking(t_philo *philos)
{
	print_state(philos->philo_id, "is thinking", philos->table);
}

void	sleeping(t_philo *philos)
{
	print_state(philos->philo_id, "is sleeping", philos->table);
	precise_sleep(philos, philos->table->time_to_sleep);
}
