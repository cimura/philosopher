/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:13:24 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/10 22:36:32 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lonely_philo(t_philo *philos)
{
	ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
	print_state(philos->philo_id,
		"has taken a fork", philos->table);
	precise_sleep(philos, philos->table->time_to_eat);
	ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
	while (!is_end(philos))
		precise_sleep(philos, philos->table->time_to_sleep);
}

static inline bool	check_full(t_philo *philos)
{
	bool	is_full;

	ft_mutex(&philos->_meal.lock, LOCK);
	if (philos->table->nbr_limit_meals > 0
		&& philos->_meal.meal_counter >= philos->table->nbr_limit_meals)
		is_full = true;
	else
		is_full = false;
	ft_mutex(&philos->_meal.lock, UNLOCK);
	return (is_full);
}

static void	*simulation(void *info)
{
	t_philo	*philos;

	philos = (t_philo *)info;
	if (philos->table->philo_nbr == 1)
		lonely_philo(philos);
	if (philos->philo_id % 2 != 0 && philos->table->philo_nbr % 2 == 0)
		precise_sleep(philos, philos->table->time_to_sleep);
	while (!is_end(philos))
	{
		eating(philos);
		if (check_full(philos))
			break ;
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				simulation, &table->philos[i]))
			return (THREAD_ERR);
		i++;
	}
	if (pthread_create(&table->death_detector, NULL,
			monitor_philo_life, table))
		return (THREAD_ERR);
	return (0);
}

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (JOIN_ERR);
		i++;
	}
	ft_mutex(&table->_end.lock, LOCK);
	table->_end.is_end = true;
	ft_mutex(&table->_end.lock, UNLOCK);
	if (pthread_join(table->death_detector, NULL))
		return (JOIN_ERR);
	return (0);
}
