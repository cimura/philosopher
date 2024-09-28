/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2024/09/28 13:43:11 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philos)
{
	if (is_dead(philos))
		return ;
	if (philos->philo_id % 2 == 0)
	{
		ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
		print_state(gettime_ms(), philos->philo_id,
			"has taken a fork", philos->table);
		ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
		print_state(gettime_ms(), philos->philo_id,
			"has taken a fork", philos->table);
	}
	else
	{
		ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
		print_state(gettime_ms(), philos->philo_id,
			"has taken a fork", philos->table);
		ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
		print_state(gettime_ms(), philos->philo_id,
			"has taken a fork", philos->table);
	}
}

void	eating(t_philo *philos)
{
	if (philos->table->nbr_limit_meals * philos->table->philo_nbr
		== philos->table->meal_counter)
		exit(EXIT_SUCCESS);
	taking_forks(philos);
	if (is_dead(philos))
	{
		ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
		ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
		return ;
	}
	print_state(gettime_ms(), philos->philo_id,
		"is eating", philos->table);
	precise_sleep(philos->table->time_to_eat);
	philos->table->meal_counter++;
	ft_mutex(&philos->meal_monitor, LOCK);
	philos->last_mealtime = gettime_ms() - philos->table->start_time;
	ft_mutex(&philos->meal_monitor, UNLOCK);
	ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
	ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
}

void	thinking(t_philo *philos)
{
	print_state(gettime_ms(), philos->philo_id, "is thinking", philos->table);
}

void	sleeping(t_philo *philos)
{
	print_state(gettime_ms(), philos->philo_id, "is sleeping", philos->table);
	precise_sleep(philos->table->time_to_sleep);
}
