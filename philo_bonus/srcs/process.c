/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:13:24 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/17 15:23:41 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	lonely_philo(t_philo *philos)
{
	print_state(philos->philo_id,
		"has taken a fork", philos->table);
	precise_sleep(philos, philos->table->time_to_eat);
	while (!is_dead(philos))
		precise_sleep(philos, philos->table->time_to_sleep);
}

void	simulation(t_table *table)
{
	t_philo	*philos;

	philos = table->philos;
	if (table->philo_nbr == 1)
		lonely_philo(philos);
	if (philos->philo_id % 2 == 0)
		precise_sleep(philos, table->time_to_eat);
	while (!is_dead(philos))
	{
		eating(philos);
		if (check_full(philos))
			break ;
		sleeping(philos);
		thinking(philos);
	}
	exit(EXIT_SUCCESS);
}

// int	create_philos(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->philo_nbr)
// 	{
// 		if (pthread_create(&table->philos[i].thread, NULL,
// 				simulation, &table->philos[i]))
// 			return (1);
// 		i++;
// 	}
// 	if (pthread_create(&table->death_thread, NULL,
// 			monitor_philo_life, &table->philos))
// 		return (1);
// 	return (0);
// }

int	wait_all_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (waitpid(table->philos[i].pid, NULL, 0) > 0)
			return (0);
		i++;
	}
	if (pthread_join(table->death_thread, NULL))
		return (1);
	return (0);
}
