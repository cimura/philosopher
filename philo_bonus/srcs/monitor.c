/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/17 15:24:38 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	check_starvation(t_philo *philos, long long last_meal)
{
	long long	now;

	now = gettime_ms() - philos->table->start_time;
	if (now - last_meal > philos->table->time_to_die)
	{
		print_state(philos->philo_id, "died", philos->table);
		// ft_mutex(&philos->meal_monitor, LOCK);
		philos->table->is_end = true;
		// ft_mutex(&philos->meal_monitor, UNLOCK);
		exit(1);
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
			// ft_mutex(&philos->meal_monitor, LOCK);
			last_meal = philos[id].last_mealtime;
			// ft_mutex(&philos->meal_monitor, UNLOCK);
			if (!check_starvation(&philos[id], last_meal))
				return (NULL);
			id++;
		}
		precise_sleep(philos, 1);
	}
	return (NULL);
}

bool	is_dead(t_philo *philos)
{
	bool	dead;
	// ft_mutex(&philos->meal_monitor, LOCK);
	dead = philos->table->is_end;
	if (dead == true)
		printf("dead!!\n");
	// ft_mutex(&philos->meal_monitor, UNLOCK);
	return (dead);
}

bool	check_full(t_philo *philos)
{
	if (philos->table->nbr_limit_meals > 0
		&& philos->table->meal_counter / philos->table->philo_nbr
		>= philos->table->nbr_limit_meals)
	{
		printf("death flag\n");
		// ft_mutex(&philos->meal_monitor, LOCK);
		philos->table->is_end = true;
		// ft_mutex(&philos->meal_monitor, UNLOCK);
		return (true);
	}
	else
		return (false);
}
