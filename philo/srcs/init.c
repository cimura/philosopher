/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/10 12:09:57 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allocate_memory(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * (table->philo_nbr));
	if (table->philos == NULL)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * (table->philo_nbr + 1));
	if (table->forks == NULL)
		return (free(table->philos), 1);
	return (0);
}

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	if (allocate_memory(table) == 1)
		return (1);
	table->_end.is_end = false;
	table->_hunger.hungry_id = -1;
	ft_mutex(&table->write, INIT);
	ft_mutex(&table->_end.lock, INIT);
	ft_mutex(&table->_hunger.lock, INIT);
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i]._meal.meal_counter = 0;
		table->philos[i].philo_id = i + 1;
		table->philos[i]._time.last_mealtime = 0;
		table->philos[i].left_fork_id = table->philos[i].philo_id;
		table->philos[i].right_fork_id
			= (table->philos[i].philo_id) % table->philo_nbr + 1;
		ft_mutex(&table->forks[i + 1], INIT);
		ft_mutex(&table->philos[i]._meal.lock, INIT);
		ft_mutex(&table->philos[i]._time.lock, INIT);
		i++;
	}
	table->start_time = gettime_ms();
	return (0);
}
