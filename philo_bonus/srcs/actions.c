/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/20 17:49:49 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	taking_forks(t_table *table, t_philo *philos)
{
	sem_wait(philos->meal_lock);
	long long	since_lastmeal = gettime_ms() - table->start_time - philos->last_mealtime;
	sem_post(philos->meal_lock);
	if (philos->last_mealtime > 0 && since_lastmeal < (table->time_to_die) / 2)
	{
		long long sleep_time = table->time_to_die / 4; 
		//if (since_lastmeal + sleep_time > table->time_to_die)
		//{
		//    sleep_time = table->time_to_die - since_lastmeal;
		//}
		//printf("\t\tsleep\n");
		precise_sleep(sleep_time);
	}
	if (philos->philo_id % 2 == 0)
	{
		if (sem_wait(table->forks) < 0)
			return (1);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
		if (sem_wait(table->forks) < 0)
			return (1);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
	}
	else
	{
		if (sem_wait(table->forks) < 0)
			return (1);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
		if (sem_wait(table->forks) < 0)
			return (1);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
	}
	return (0);
}

int	eating(t_table *table, t_philo *philos)
{
	if (taking_forks(table, philos) == 1)
		return (1);
	print_state(philos->philo_id,
		"is eating", philos->table);
	precise_sleep(philos->table->time_to_eat);
	philos->table->meal_counter++;
	sem_wait(philos->meal_lock);
	philos->last_mealtime = gettime_ms() - philos->table->start_time;
	sem_post(philos->meal_lock);
	if (sem_post(table->forks) < 0)
		return (1);
	if (sem_post(table->forks) < 0)
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
	precise_sleep(philos->table->time_to_sleep);
}
