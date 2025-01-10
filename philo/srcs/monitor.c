/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/10 17:13:16 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_starvation(t_philo *philos, long long last_meal)
{
	long long	now;

	now = gettime_ms() - philos->table->start_time;
	if (is_end(philos))
		return (false);
	if (now - last_meal > philos->table->time_to_die)
	{
		ft_mutex(&philos->table->_end.lock, LOCK);
		now = gettime_ms() - philos->table->start_time;
		printf("%lld %d is "RED"died\n"RESET, now, philos->philo_id);
		philos->table->_end.is_end = true;
		ft_mutex(&philos->table->_end.lock, UNLOCK);
		return (false);
	}
	return (true);
}

static int	monitor_loop(t_table *table, int *max_id)
{
	int			id;
	long long	last_meal;
	long long	max_last_mealtime;

	id = 0;
	while (id < table->philo_nbr)
	{
		ft_mutex(&table->philos[id]._time.lock, LOCK);
		if (table->philos[id]._time.last_mealtime > max_last_mealtime)
		{
			max_last_mealtime = table->philos[id]._time.last_mealtime;
			*max_id = id;
		}
		last_meal = table->philos[id]._time.last_mealtime;
		ft_mutex(&table->philos[id]._time.lock, UNLOCK);
		if (!check_starvation(&table->philos[id], last_meal))
			return (STARVATION);
		id++;
	}
	return (0);
}

void	*monitor_philo_life(void *info)
{
	t_table		*table;
	int			max_id;
	int			id;

	table = (t_table *)info;
	max_id = 0;
	while (1)
	{
		id = 0;
		if (monitor_loop(table, &max_id) == STARVATION)
			return (NULL);
		ft_mutex(&table->_hunger.lock, LOCK);
		table->_hunger.hungry_id = max_id;
		ft_mutex(&table->_hunger.lock, UNLOCK);
		precise_sleep(table->philos, 1);
	}
	return (NULL);
}

bool	is_end(t_philo *philos)
{
	bool	dead;

	ft_mutex(&philos->table->_end.lock, LOCK);
	dead = philos->table->_end.is_end;
	ft_mutex(&philos->table->_end.lock, UNLOCK);
	return (dead);
}
