/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/10 13:05:01 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_starvation(t_philo *philos, long long last_meal)
{
	long long	now;

	now = gettime_ms() - philos->table->start_time;
	if (is_dead(philos))
		return(false);
	if (now - last_meal > philos->table->time_to_die)
	{
		ft_mutex(&philos->table->_end.lock, LOCK);
		printf("%lld %d is "RED"died\n"RESET, gettime_ms() - philos->table->start_time, philos->philo_id);
		philos->table->_end.is_end = true;
		ft_mutex(&philos->table->_end.lock, UNLOCK);
		return (false);
	}
	return (true);
}

void	*monitor_philo_life(void *info)
{
	t_table		*table;
	long long	last_meal;
	long long	max_last_mealtime;
	int			max_id = 0;
	int			id;

	table = (t_table *)info;
	while (1)
	{
		id = 0;
		max_last_mealtime = INT_MIN;
		while (id < table->philo_nbr)
		{
			ft_mutex(&table->philos[id]._time.lock, LOCK);
			if (table->philos[id]._time.last_mealtime > max_last_mealtime)
			{
				max_last_mealtime = table->philos[id]._time.last_mealtime;
				max_id = id;
			}
			ft_mutex(&table->philos[id]._time.lock, UNLOCK);
			set_value(&table->philos[id]._time.lock, &last_meal,table->philos[id]._time.last_mealtime);
			if (!check_starvation(&table->philos[id], last_meal))
				return (NULL);
			id++;
		}
		set_value(&table->_hunger.lock, (long long *)&table->_hunger.hungry_id, max_id);
		//table->_hunger.hungry_id = max_id;
		precise_sleep(table->philos, 1);
	}
	return (NULL);
}

bool	is_dead(t_philo *philos)
{
	bool	dead;

	ft_mutex(&philos->table->_end.lock, LOCK);
	dead = philos->table->_end.is_end;
	ft_mutex(&philos->table->_end.lock, UNLOCK);
	return (dead);
}

bool	check_full(t_philo *philos)
{
	bool	is_full;

	ft_mutex(&philos->_meal.lock, LOCK);
	if (philos->table->nbr_limit_meals > 0
		&& philos->_meal.meal_counter >= philos->table->nbr_limit_meals)
		is_full = true;
	else
		is_full = false;
	ft_mutex(&philos->_meal.lock, UNLOCK);
	return (is_full);
}
