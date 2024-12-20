/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/21 01:05:01 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * (table->philo_nbr + 1));
	if (table->philos == NULL)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * (table->philo_nbr + 1));
	if (table->forks == NULL)
		return (1);
	table->is_end = false;
	table->meal_counter = 0;
	table->start_time = gettime_ms();
	ft_mutex(&table->write, INIT);
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].last_mealtime = 0;
		table->philos[i].left_fork_id = table->philos[i].philo_id;
		table->philos[i].right_fork_id
			= (table->philos[i].philo_id) % table->philo_nbr + 1;
		ft_mutex(&table->forks[i + 1], INIT);
		ft_mutex(&table->philos[i].meal_monitor, INIT);
		i++;
	}
	return (0);
}
