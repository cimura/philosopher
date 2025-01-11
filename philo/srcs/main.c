/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:32 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 18:01:53 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	clean(t_table *table, char *message, void (func)(t_table *))
{
	if (message != NULL)
		print_error(message);
	if (func != NULL)
		func(table);
	return (EXIT_FAILURE);
}

static void	destroy_data(t_table *table)
{
	int	i;

	ft_mutex(&table->write, DESTROY);
	ft_mutex(&table->_end.lock, DESTROY);
	i = 0;
	while (i < table->philo_nbr)
	{
		ft_mutex(&table->forks[i + 1], DESTROY);
		ft_mutex(&table->philos[i]._meal.lock, DESTROY);
		ft_mutex(&table->philos[i]._time.lock, DESTROY);
		i++;
	}
	free(table->philos);
	free(table->forks);
	if (table->philo_nbr % 2 != 0)
		free(table->que.memory);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		if (parse_input(&table, argv) == PARSE_ERR)
			return (clean(&table, "parse error", NULL));
		if (data_init(&table) == 1)
			return (clean(&table, "data init error", NULL));
		if (create_threads(&table) == THREAD_ERR)
			return (clean(&table, "thread init error", destroy_data));
		if (join_threads(&table) == JOIN_ERR)
			return (clean(&table, "thread join error", destroy_data));
		clean(&table, NULL, destroy_data);
	}
	else
		print_error(RED"Wrong input:\n"
			GREEN"example) ./philo 5 800 200 200 [5]"RESET);
	return (0);
}
