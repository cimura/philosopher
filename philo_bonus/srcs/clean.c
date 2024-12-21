/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:25:59 by cimy              #+#    #+#             */
/*   Updated: 2024/12/22 00:37:21 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_name(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		sem_unlink(table->name_ptr[i]);
		free(table->name_ptr[i]);
		i++;
	}
}

void	clean_sem_meal_lock(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philo_nbr)
	{
		sem_close(table->philos[i].meal_lock);
		i++;
	}
	clean_name(table);
	free(table->name_ptr);
}

void	clean(t_table *table)
{
	clean_sem_meal_lock(table);
	sem_close(table->forks);
	sem_close(table->death);
	sem_close(table->write_lock);
	sem_unlink("/forks");
	sem_unlink("/death");
	sem_unlink("/write_lock");
	free(table->philos);
}
