/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:23 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/08 20:55:55 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	semphore_init(t_table *table)
{
	table->forks.fork = sem_open("/forks", O_CREAT | O_EXCL, 0644, table->philo_nbr);
	if (table->forks.fork == SEM_FAILED)
		return (1);
	sem_unlink("/forks");
	table->forks.lock = sem_open("/lock", O_CREAT | O_EXCL, 0644, 1);
	if (table->forks.lock == SEM_FAILED)
		return (1);
	sem_unlink("/lock");
	table->death = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
	if (table->death == SEM_FAILED)
		return (1);
	sem_unlink("/death");
	table->write_lock = sem_open("/write_lock", O_CREAT | O_EXCL, 0644, 1);
	if (table->write_lock == SEM_FAILED)
		return (1);
	sem_unlink("/write_lock");
	table->start = sem_open("/start", O_CREAT | O_EXCL, 0644, 0);
	if (table->start == SEM_FAILED)
		return (1);
	sem_unlink("/start");
	return (0);
}

static int	semphore_init_meal_lock(t_table *table, t_philo *philos, int i)
{
	char	*uniq_id;
	char	*name1;
	char	*name2;

	uniq_id = ft_itoa(philos->philo_id);
	if (uniq_id == NULL)
		return (table->name_ptr1[i] = NULL, 1);
	name1 = ft_strjoin("/sem_meal", uniq_id);
	if (name1 == NULL)
		return (table->name_ptr1[i] = NULL, free(uniq_id), 1);
	table->name_ptr1[i] = name1;
	philos->_meal.lock = sem_open(name1, O_CREAT | O_EXCL, 0644, 1);
	if (philos->_meal.lock == SEM_FAILED)
		return (free(name1), free(uniq_id), 1);
	sem_unlink(name1);
	name2 = ft_strjoin("/sem_time", uniq_id);
	if (name2 == NULL)
		return (table->name_ptr1[i] = NULL, table->name_ptr2[i] = NULL, free(uniq_id), 1);
	free(uniq_id);
	table->name_ptr2[i] = name2;
	philos->_time.lock = sem_open(name2, O_CREAT | O_EXCL, 0644, 1);
	if (philos->_time.lock == SEM_FAILED)
		return (free(name2), 1);
	sem_unlink(name2);
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
	table->name_ptr1 = malloc(sizeof(char *) * table->philo_nbr + 1);
	if (table->name_ptr1 == NULL)
		return (free(table->philos), 1);
	table->name_ptr2 = malloc(sizeof(char *) * table->philo_nbr + 1);
	if (table->name_ptr2 == NULL)
		return (free(table->name_ptr1), free(table->philos), 1);	
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i]._meal.meal_counter = 0;
		table->philos[i]._time.last_mealtime = 0;
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		if (semphore_init_meal_lock(table, &table->philos[i], i) == 1)
			return (free(table->philos), clean_name(table), 1);
		i++;
	}
	return (0);
}
