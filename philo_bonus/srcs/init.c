/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/18 17:25:25 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	data_init(t_table *table)
{
	table->meal_counter = 0;
	table->is_dead = false;
	table->start_time = gettime_ms();

	sem_unlink("/forks");
	table->sem_name = "/forks";
	table->forks = sem_open(table->sem_name, O_CREAT, 0644, table->philo_nbr);
	if (table->forks == SEM_FAILED)
		return (1);
	sem_unlink("/death");
	table->sem_name = "/death";
	table->death = sem_open(table->sem_name, O_CREAT, 0644, 0);
	if (table->death == SEM_FAILED)
		return (1);
	sem_unlink("/meal");
	table->sem_name = "/meal";
	int	i = 1;
	while (i <= table->philo_nbr)
	{
		table->meal[i] = sem_open(table->sem_name, O_CREAT, 0644, 0);
		if (table->meal[i] == SEM_FAILED)
			return (1);
		i++;
	}
	sem_unlink("/write_lock");
	table->sem_name = "/write_lock";
	table->write_lock = sem_open(table->sem_name, O_CREAT, 0644, 1);
	if (table->write_lock == SEM_FAILED)
		return (1);

	//table->last_mealtime = malloc(sizeof(long long) * table->philo_nbr + 1);
	//if (table->last_mealtime == NULL)
	//	return (1);
	i = 1;
	while (i <= table->philo_nbr)
	{
		table->last_mealtime[i] = 0;
		i++;
	}

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].last_mealtime = 0;
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (1);
		if (table->philos[i].pid == 0)
		{
			simulation(table, &table->philos[i]);
		}
		else
			i++;
	}
	return (0);
}

int	create_death_detector(t_table *table)
{
	int	i;
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->meal_updater[i], NULL,
				update_meal_time, &table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&table->death_detector, NULL,
			monitor_philo_life, table->philos))
		return (1);
	return (0);
}
