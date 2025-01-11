/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 10:20:05 by cimy             ###   ########.fr       */
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
		if (!philos->table->_end.is_end)
			printf("%lld %d is "RED"died\n"RESET, now, philos->philo_id);
		else
		{
			ft_mutex(&philos->table->_end.lock, UNLOCK);
			return (false);
		}
		philos->table->_end.is_end = true;
		ft_mutex(&philos->table->_end.lock, UNLOCK);
		return (false);
	}
	return (true);
}

void	*monitor_philo_life(void *info)
{
	t_table		*table;
	int			id;
	long long	last_meal;

	table = (t_table *)info;
	while (1)
	{
		id = 0;
		while (id < table->philo_nbr)
		{
			ft_mutex(&table->philos[id]._time.lock, LOCK);
			last_meal = table->philos[id]._time.last_mealtime;
			ft_mutex(&table->philos[id]._time.lock, UNLOCK);
			if (!check_starvation(&table->philos[id], last_meal))
				break ;
			id++;
		}
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
