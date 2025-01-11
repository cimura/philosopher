/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 17:19:38 by sshimura         ###   ########.fr       */
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
	if (table->philo_nbr % 2 != 0)
	{
		table->que.memory = malloc(sizeof(int) * (table->philo_nbr + 1));
		if (table->que.memory == NULL)
			return (free(table->philos), free(table->forks), 1);
	}
	return (0);
}

static void	table_init(t_table *table)
{
	int	i;

	table->_end.is_end = false;
	if (table->philo_nbr % 2 != 0)
		que_init(table);
	ft_mutex(&table->write, INIT);
	ft_mutex(&table->_end.lock, INIT);
	i = 0;
	while (i < table->philo_nbr)
	{
		ft_mutex(&table->forks[i + 1], INIT);
		ft_mutex(&table->philos[i]._meal.lock, INIT);
		ft_mutex(&table->philos[i]._time.lock, INIT);
		i++;
	}
	table->start_time = gettime_ms();
}

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	if (allocate_memory(table) == 1)
		return (1);
	table_init(table);
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i]._meal.meal_counter = 0;
		table->philos[i].philo_id = i + 1;
		table->philos[i]._time.last_mealtime = 0;
		table->philos[i].left_fork_id = table->philos[i].philo_id;
		table->philos[i].right_fork_id
			= (table->philos[i].philo_id) % table->philo_nbr + 1;
		i++;
	}
	return (0);
}
