/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:13:24 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/09 18:11:31 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lonely_philo(t_philo *philos)
{
	ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
	print_state(philos->philo_id,
		"has taken a fork", philos->table);
	precise_sleep(philos->table->time_to_eat);
	ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
	while (!is_dead(philos))
		precise_sleep(philos->table->time_to_sleep);
}

static void	*simulation(void *info)
{
	t_philo	*philos;

	philos = (t_philo *)info;
	if (philos->table->philo_nbr == 1)
		lonely_philo(philos);
	if (philos->philo_id % 2 == 0)
		precise_sleep(philos->table->time_to_eat);
	while (!is_dead(philos))
	{
		eating(philos);
		if (is_full(philos))
			return (NULL);
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}

void	create_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				simulation, &table->philos[i]))
			error_exit("CREATION: simulation thread failed.");
		i++;
	}
	if (pthread_create(&table->death_thread, NULL,
			monitor_philo_life, &table->philos))
		error_exit("CREATION: death monitor thread failed.");
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			error_exit("JOIN: philo thread failed.");
		i++;
	}
	pthread_join(table->death_thread, NULL);
}
