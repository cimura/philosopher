/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   que.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:23:53 by cimy              #+#    #+#             */
/*   Updated: 2025/01/11 12:59:16 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	que_init(t_table *table)
{
	int	i;

	table->que.head = 0;
	table->que.tail = 0;
	i = 1;
	ft_mutex(&table->que.lock, INIT);
	while (i <= table->philo_nbr / 2)
	{
		enque(table, i * 2);
		i++;
	}
	i = 0;
	while (i <= table->philo_nbr / 2)
	{
		enque(table, i * 2 + 1);
		i++;
	}
}

void	enque(t_table *table, int id)
{
	ft_mutex(&table->que.lock, LOCK);
	table->que.memory[table->que.tail] = id;
	table->que.tail++;
	if (table->que.tail == table->philo_nbr)
		table->que.tail = 0;
	ft_mutex(&table->que.lock, UNLOCK);
}

int	call_que_head(t_table *table, int id)
{
	int	head;

	ft_mutex(&table->que.lock, LOCK);
	head = table->que.memory[table->que.head];
	if (head != id)
	{
		ft_mutex(&table->que.lock, UNLOCK);
		return (-1);
	}
	ft_mutex(&table->que.lock, UNLOCK);
	return (head);
}

void	increase_que_head(t_table *table)
{
	ft_mutex(&table->que.lock, LOCK);
	table->que.head = (table->que.head + 1) % table->philo_nbr;
	ft_mutex(&table->que.lock, UNLOCK);
}
