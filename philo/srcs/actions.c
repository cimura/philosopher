/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/24 08:44:12 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	tune_philo(t_philo *philos)
{
	long long	last;
	long long	eval;

	eval = (philos->table->time_to_die
			- (philos->table->time_to_eat + philos->table->time_to_sleep))
		/ philos->table->philo_nbr;
	ft_mutex(&philos->meal_monitor, LOCK);
	last = gettime_ms() - philos->table->start_time - philos->last_mealtime;
	ft_mutex(&philos->meal_monitor, UNLOCK);
	if (is_dead(philos))
		return (DEAD);
	if (eval < 10)
		return (0);
	if (last > 0 && last < (philos->table->time_to_die) / 2)
		precise_sleep(philos, 1);
	return (0);
}

void	taking_forks(t_philo *philos)
{
	if (tune_philo(philos) == DEAD)
		return ;
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
	philos->table->meal_counter++;
	ft_mutex(&philos->meal_monitor, LOCK);
	philos->last_mealtime = gettime_ms() - philos->table->start_time;
	ft_mutex(&philos->meal_monitor, UNLOCK);
	if (philos->philo_id % 2 == 0)
	{
		ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
		ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
	}
	else
	{
		ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
		ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
	}
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
