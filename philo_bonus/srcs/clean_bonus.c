/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:25:59 by cimy              #+#    #+#             */
/*   Updated: 2025/01/11 17:13:20 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_sem_meal_lock(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philo_nbr)
	{
		sem_close(table->philos[i]._meal.lock);
		i++;
	}
	clean_name(table);
	free(table->name_ptr1);
	free(table->name_ptr2);
}

void	clean_name(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (table->name_ptr1[i] == NULL)
			return ;
		free(table->name_ptr1[i]);
		i++;
	}
	i = 0;
	while (i < table->philo_nbr)
	{
		if (table->name_ptr2[i] == NULL)
			return ;
		free(table->name_ptr2[i]);
		i++;
	}
}

void	destroy_data(t_table *table)
{
	clean_sem_meal_lock(table);
	sem_close(table->forks.fork);
	sem_close(table->forks.lock);
	sem_close(table->death);
	sem_close(table->write_lock);
	sem_close(table->start);
	free(table->philos);
}

int	clean(t_table *table, char *message, void (*func)(t_table *))
{
	if (message != NULL)
		print_error(message);
	if (func != NULL)
		func(table);
	return (EXIT_FAILURE);
}
