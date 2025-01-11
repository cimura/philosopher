/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 17:26:49 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_for_turn(t_philo *philos)
{
	while (!is_end(philos))
	{
		if (call_que_head(philos->table, philos->philo_id) == philos->philo_id)
			break ;
		precise_sleep(philos, 1);
	}
}

static void	taking_forks(t_philo *philos)
{
	if (philos->table->philo_nbr % 2 != 0)
		wait_for_turn(philos);
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
	if (philos->table->philo_nbr % 2 != 0)
	{
		increase_que_head(philos->table);
		enque(philos->table, philos->philo_id);
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
