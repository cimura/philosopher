/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/09/25 16:20:36 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	assign_bool(t_table *table, bool *dst, bool src)
// {
// 	ft_mutex(&table->write, LOCK);
// 	*dst = src;
// 	ft_mutex(&table->write, UNLOCK);
// }

// static void	assign_value(t_table *table, long *dst, long src)
// {
// 	ft_mutex(&table->write, LOCK);
// 	*dst = src;
// 	ft_mutex(&table->write, UNLOCK);
// }

static bool	check_starvation(t_table *table, long last_meal, t_philo *philos)
{
	long	now;
	bool	dead;

	dead = false;
	now = gettime_ms() - table->start_time;
	if (now - last_meal > table->time_to_die)
	{
		ft_mutex(&table->philos->dead_monitor, LOCK);
		print_state(gettime_ms(), table->philos->philo_id, "died", table);
		// assign_bool(table, &table->philos->is_dead, true);
		philos->is_dead = true;
		dead = true;
		ft_mutex(&table->philos->dead_monitor, UNLOCK);
	}
	return (dead);
}

void	*monitor_philo_life(void *info)
{
	t_table	*table;
	long	last_meal;
	int		id;

	table = (t_table *)info;
	while (1)
	{
		id = 0;
		while (id < table->philo_nbr)
		{
			last_meal = table->philos[id].last_mealtime;
			// printf("last_meal => %lu\n", last_meal);
			if (check_starvation(table, last_meal, &table->philos[id]))
			{
				exit(EXIT_SUCCESS);
			}
			id++;
		}
		precise_sleep(5);
	}
	return (NULL);
}