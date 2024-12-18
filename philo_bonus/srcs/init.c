/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/18 10:59:05 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	data_init(t_table *table)
{
	table->meal_counter = 0;
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
	table->meal = sem_open(table->sem_name, O_CREAT, 0644, 0);
	if (table->meal == SEM_FAILED)
		return (1);

	table->last_meal_time = malloc(sizeof(long long) * table->philo_nbr);
	if (table->last_meal_time == NULL)
		return (1);
	int	i = 0;
	while (i < table->philo_nbr)
	{
		table->last_meal_time[i] = table->start_time;
		i++;
	}

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].pid = fork();
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
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
	if (pthread_create(&table->death_detector, NULL,
			monitor_philo_life, &table->philos))
		return (1);
	if (pthread_create(&table->meal_updater, NULL,
			update_meal_time, table))
		return (1);	
	return (0);
}
