/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/10 17:46:35 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	tune_philo(t_philo *philos)
{
	long long	sleep_time;

	sleep_time = philos->table->time_to_eat - philos->table->time_to_sleep + 5;
	ft_mutex(&philos->table->_hunger.lock, LOCK);
	if (philos->philo_id != philos->table->_hunger.hungry_id
		&& philos->_time.last_mealtime != 0)
	{
		precise_sleep(philos, sleep_time);
	}
	ft_mutex(&philos->table->_hunger.lock, UNLOCK);
}

void	taking_forks(t_philo *philos)
{
	if (philos->table->philo_nbr % 2 != 0)
		tune_philo(philos);
	if (philos->philo_id % 2 == 0)
	{
		ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
		ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
	}
	else
	{
		ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
		ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
	}
}

void	eating(t_philo *philos)
{
	taking_forks(philos);
	print_state(philos->philo_id,
		"is eating", philos->table);
	precise_sleep(philos, philos->table->time_to_eat);
	ft_mutex(&philos->_meal.lock, LOCK);
	philos->_meal.meal_counter++;
	ft_mutex(&philos->_meal.lock, UNLOCK);
	ft_mutex(&philos->_time.lock, LOCK);
	philos->_time.last_mealtime = gettime_ms() - philos->table->start_time;
	ft_mutex(&philos->_time.lock, UNLOCK);
	if (philos->philo_id % 2 == 0)
	{
		ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
		ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
	}
	else
	{
		ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
		ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
	}
}

void	sleeping(t_philo *philos)
{
	print_state(philos->philo_id, "is sleeping", philos->table);
	precise_sleep(philos, philos->table->time_to_sleep);
}

void	thinking(t_philo *philos)
{
	print_state(philos->philo_id, "is thinking", philos->table);
}
