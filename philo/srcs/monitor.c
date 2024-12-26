/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/21 20:07:27 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_starvation(t_philo *philos, long long last_meal)
{
	long long	now;

	ft_mutex(&philos->meal_monitor, LOCK);
	now = gettime_ms() - philos->table->start_time;
	ft_mutex(&philos->meal_monitor, UNLOCK);
	if (now - last_meal > philos->table->time_to_die)
	{
		print_state(philos->philo_id, RED"died"RESET, philos->table);
		ft_mutex(&philos->table->end, LOCK);
		philos->table->is_end = true;
		ft_mutex(&philos->table->end, UNLOCK);
		return (false);
	}
	return (true);
}

void	*monitor_philo_life(void *info)
{
	t_table		*table;
	long long	last_meal;
	int			id;

	table = (t_table *)info;
	while (1)
	{
		id = 0;
		while (id < table->philo_nbr)
		{
			ft_mutex(&table->philos[id].meal_monitor, LOCK);
			last_meal = table->philos[id].last_mealtime;
			ft_mutex(&table->philos[id].meal_monitor, UNLOCK);
			if (!check_starvation(&table->philos[id], last_meal))
				return (NULL);
			id++;
		}
		precise_sleep(table->philos, 1);
	}
	return (NULL);
}

bool	is_dead(t_philo *philos)
{
	bool	dead;

	ft_mutex(&philos->table->end, LOCK);
	dead = philos->table->is_end;
	ft_mutex(&philos->table->end, UNLOCK);
	return (dead);
}

bool	check_full(t_philo *philos)
{
	ft_mutex(&philos->table->meal_counter_lock, LOCK);
	if (philos->table->nbr_limit_meals > 0
		&& philos->table->meal_counter >= philos->table->nbr_limit_meals)
		return (ft_mutex(&philos->table->meal_counter_lock, UNLOCK), true);
	else
		return (ft_mutex(&philos->table->meal_counter_lock, UNLOCK), false);
}
