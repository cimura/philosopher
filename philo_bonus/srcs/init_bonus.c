/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/28 16:28:25 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	semphore_init(t_table *table)
{
	sem_unlink("/forks");
	sem_unlink("/death");
	sem_unlink("/write_lock");
	sem_unlink("/meal_counter_lock");
	table->forks = sem_open("/forks", O_CREAT, 0644, table->philo_nbr);
	if (table->forks == SEM_FAILED)
		return (1);
	table->death = sem_open("/death", O_CREAT, 0644, 0);
	if (table->death == SEM_FAILED)
		return (1);
	table->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
	if (table->write_lock == SEM_FAILED)
		return (1);
	table->meal_counter_lock = sem_open("meal_counter_lock", O_CREAT, 0644, 1);
	if (table->meal_counter_lock == SEM_FAILED)
		return (1);
	return (0);
}

static int	semphore_init_meal_lock(t_table *table, t_philo *philos, int i)
{
	char	*uniq_id;
	char	*name;

	uniq_id = ft_itoa(philos->philo_id);
	if (uniq_id == NULL)
		return (table->name_ptr[i] = NULL, 1);
	name = ft_strjoin("/sem_meal", uniq_id);
	if (name == NULL)
		return (table->name_ptr[i] = NULL, free(uniq_id), 1);
	free(uniq_id);
	sem_unlink(name);
	table->name_ptr[i] = name;
	philos->meal_lock = sem_open(name, O_CREAT, 0644, 1);
	if (philos->meal_lock == SEM_FAILED)
		return (free(name), 1);
	return (0);
}

int	data_init(t_table *table)
{
	int	i;

	if (semphore_init(table) == 1)
		return (1);
	table->start_time = gettime_ms();
	table->philos = malloc(sizeof(t_philo) * (table->philo_nbr));
	if (table->philos == NULL)
		return (1);
	table->name_ptr = malloc(sizeof(char *) * table->philo_nbr + 1);
	if (table->name_ptr == NULL)
		return (free(table->philos), 1);
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].meal_counter = 0;
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].last_mealtime = 0;
		if (semphore_init_meal_lock(table, &table->philos[i], i) == 1)
			return (free(table->philos), clean_name(table), 1);
		i++;
	}
	return (0);
}
