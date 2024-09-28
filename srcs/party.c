/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:13:24 by sshimura          #+#    #+#             */
/*   Updated: 2024/09/28 13:43:44 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*simulation(void *info)
{
	t_philo	*philos;

	philos = (t_philo *)info;
	while (!is_dead(philos))
	{
		eating(philos);
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}

static void	create_philos(t_table *table)
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

static void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_join(table->death_thread, NULL))
		error_exit("JOIN: death monitor thread failed.");
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			error_exit("JOIN: death monitor thread failed.");
		i++;
	}
}

void	party(t_table *table)
{
	create_philos(table);
	join_threads(table);
}
