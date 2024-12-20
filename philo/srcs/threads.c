/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:13:24 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/20 20:52:34 by cimy             ###   ########.fr       */
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
	while (!is_dead(philos))
		precise_sleep(philos, philos->table->time_to_sleep);
}

static void	*simulation(void *info)
{
	t_philo	*philos;

	philos = (t_philo *)info;
	if (philos->table->philo_nbr == 1)
		lonely_philo(philos);
	if (philos->philo_id % 2 != 0)
		precise_sleep(philos, philos->table->time_to_eat);
	while (!is_dead(philos))
	{
		eating(philos);
		if (check_full(philos))
			break ;
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}

int	create_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				simulation, &table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&table->death_detector, NULL,
			monitor_philo_life, &table->philos))
		return (1);
	return (0);
}

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(table->death_detector, NULL))
		return (1);
	return (0);
}
