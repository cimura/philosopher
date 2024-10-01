/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/01 23:42:53 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_starvation(long long last_meal, t_philo *philos)
{
	long long	now;

	now = gettime_ms() - philos->table->start_time;
	if (now - last_meal > philos->table->time_to_die)
	{
		print_state(philos->philo_id, "died", philos->table);
		ft_mutex(&philos->meal_monitor, LOCK);
		philos->table->is_end = true;
		ft_mutex(&philos->meal_monitor, UNLOCK);
		precise_sleep(4);
		return (false);
	}
	return (true);
}

void	*monitor_philo_life(void *info)
{
	t_philo		*philos;
	long long	last_meal;
	int			id;

	philos = (t_philo *)info;
	while (1)
	{
		id = 0;
		while (id < philos->table->philo_nbr)
		{
			ft_mutex(&philos->meal_monitor, LOCK);
			last_meal = philos[id].last_mealtime;
			ft_mutex(&philos->meal_monitor, UNLOCK);
			if (!check_starvation(last_meal, &philos[id]))
				return (NULL);
			id++;
		}
		precise_sleep(1);
	}
	return (NULL);
}

bool	is_dead(t_philo *philos)
{
	bool	dead;

	ft_mutex(&philos->dead_monitor, LOCK);
	dead = philos->table->is_end;
	ft_mutex(&philos->dead_monitor, UNLOCK);
	return (dead);
}
