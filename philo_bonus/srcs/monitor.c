/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:50 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/18 11:05:57 by cimy             ###   ########.fr       */
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
		sem_post(philos->table->death);
		send_kill_signal(philos->table);
		return (false);
	}
	return (true);
}

void	*monitor_philo_life(void *arg)
{
	t_philo		*philos;
	int			id;

	philos = (t_philo *)arg;
	while (1)
	{
		id = 0;
		while (id < philos->table->philo_nbr)
		{
			if (!check_starvation(&philos[id], philos->table->last_meal_time[id]))
				return (NULL);
			id++;
		}
		precise_sleep(1);
	}
	return (NULL);
}

void	*update_meal_time(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		sem_wait(table->meal);
		i = 0;
		while (i < table->philo_nbr)
		{
			table->last_meal_time[i] = gettime_ms() - table->start_time;
			i++;
		}
	}
	return (NULL);
}
//bool	check_full(t_philo *philos)
//{
//	if (philos->table->nbr_limit_meals > 0
//		&& philos->table->meal_counter / philos->table->philo_nbr
//		>= philos->table->nbr_limit_meals)
//	{
//		return (true);
//	}
//	else
//		return (false);
//}

void	send_kill_signal(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		kill(table->philos[i].pid, SIGKILL);
		i++;
	}
}
